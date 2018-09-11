/*
*
*文件名:main.c
*摘要:本文件定义了单片机的操作架构.
*
*作者:肖阳, <email: planck_constant@foxmail.com>
*版本:0.1
*完成日期:2015.12.
*
*/



#include"config.h"
#include"STC15Fxxxx.h"

//外设
#include  "key.h"       //按键模块
#include  "lcd1602.h"   
#include  "EEPROM.h"   
#include  "ADC.h"     
#include  "buzzer.h" 
#include  "timer.h" 
#include  "delay.h"
#include  "ntostr.h"

#define uint8     unsigned char
#define uint16    unsigned int

//操作模式定义
#define MEASURE_MODE   0  //测量模式
#define SET_MODE       1  //设置模式(设置报警值)


//定义默认的报警值和待设置的报警值和储存地址 
#define MAX_FORCE  10          //初始报警值为 10g
#define ADDR_MAX_FORCE  0x0010  

//代表蜂鸣器的两种不同声音的值. continus连续的声音，discontinus间断的声音 
#define CONTINU 0
#define DISCONTINU 1

/* AD配置 */
ADC_InitTypeDef ADC_Struct={ ADC_P10,    	//配置A/D
           ADC_540T,ENABLE, ADC_RES_H2L8,PolityHigh, ENABLE };

/* 定时器配置 
   16-bit自动重载, 定时器i初值=0,
   未设置中断, 初始时未运行        */
TIM_InitTypeDef Timer0_Struct={
                   	 TIM_16BitAutoReload,
					 PolityHigh,
					 DISABLE,
					 TIM_CLOCK_12T,
					 DISABLE,
					 63488,     //定时器初始值=0
					 DISABLE };

uint8 flag = MEASURE_MODE;  //决定MCU工作模式的标志
uint16 NumOfVoltConvert = 0; // 输入电压经A/D转换后的值

#define EnableTimer0IRQ()   (ET0 = 1)
#define DisableTimer0IRQ()  (ET0 = 0)

int main(void)
{
  uint16 force_g; // 单位为 g 的力
  uint16 maxForce, deltaForce;
  uint8 key;
  uint8 string[10]; //储存字符串
  while (1)
  {
    //初始化A/D, 定时器0
    InitLCD();
    ADC_Inilize(&ADC_Struct);
    Timer_Inilize(Timer0, &Timer0_Struct);

     switch (flag)
     {
        // 测量模式
	case MEASURE_MODE:     
		/*
		 * 做一些初始化:
		 * 初始化lcd，读入eerpom储存的值,启动A/D
		 */
        InitLCD();
        WriteLCDStr(0x0a, "Normal");
        WriteLCDStr(0x43, "00  g");
        EEPROM_read_n(ADDR_MAX_FORCE, string, 2);  
		maxForce = string[0] + 256 * string[1];
          delay_ms(10);  //延迟 10 ms, 等待测量
          while (1) 
          {
            /* 进入测量状态， 直到按下MODE键退出 */
             force_g = (100UL * NumOfVoltConvert / 266) - 10UL;
             WriteLCDStr(0x43, N16ToStr(force_g, string) );
	     
	     if (force_g >= maxForce)
             { 
	         if (force_g >= (maxForce+2))  //间断的声音提醒用户力很接近预设的值了，
		 {			       //连续的声音提醒用户力有点大，要小一点
		     
	             DisableTimer0IRQ(); //关定时器0中断
		     OpenBuzzer(CONTINU); //连续声音
                 }
		 else
		 {
		     EnableTimer0IRQ();
		 }
             }
	     else
	     {
 	        DisableTimer0IRQ();
		CloseBuzzer();
	     }

	     //按键扫描
	     if ( (key=ReadKey()) == KEY_MODE )
	     {
	        ADC_PowerControl(DISABLE);
		flag++;
		break;
	     }              
	  }           //测量模式结束
			     
        //设置模式			     
	case SET_MODE:
		/*
		 * 做一些设置模式下的初始化:
		 * 初始化lcd, 读取eeprom的maxForce值，并显示它
		 * 然后等待按键
		 */
        InitLCD();
        WriteLCDStr(0x0b, "Set");
        EEPROM_read_n(ADDR_MAX_FORCE, string, 1);
		maxForce = 256 * string[1] + string[0];
        WriteLCDStr(0x45, "     g");
        WriteLCDStr(0x45, N16ToStr(maxForce, string)); 
	  		
	  while (1)
	  {
	    if ( (key=ReadKey()) == KEY_MODE )
	    {
	       flag++;
	       EEPROM_SectorErase(ADDR_MAX_FORCE);
		   string[0] = maxForce % 256;
		   string[1] = maxForce / 256;
	       EEPROM_write_n(ADDR_MAX_FORCE, string, 2);
	       break;
            }

	    if ( key == KEY_10g )
	    {
               if ( deltaForce == 1)
	       {
	          deltaForce = 10;
	       }
	    }

	    if ( key == KEY_ADD )
	    {
	       maxForce += deltaForce;
	       WriteLCDStr(0x45, N8ToStr(maxForce, string) );
            }

	    if ( key == KEY_DEC )
	    { 
               if ( (maxForce -= deltaForce) <=0)    
               {
	          maxForce = 0;
	       }
	       WriteLCDStr(0x45, N8ToStr(maxForce, string) );
	    }
         }

      default: break;
     } //switch在此结束

     if (flag>=2)
     {
        flag=0;
     }

   } //外层while在此结束

}

void ADC_InterruptService(void) interrupt 5
{
   /* A/D 10-bit模式,ADC_RESL 低8位，
      ADC_RES 高2位			*/
   NumOfVoltConvert = (ADC_RES * 256) + ADC_RESL; 
   ADC_CONTR &= (~ADC_FLAG);
   ADC_PowerControl(ENABLE);
}


void Timer0_InterruptService(void) interrupt 1 
{
  OpenBuzzer(DISCONTINU);
  EnableTimer0IRQ();
}   


