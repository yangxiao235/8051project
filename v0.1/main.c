/*
*
*�ļ���:main.c
*ժҪ:���ļ������˵�Ƭ���Ĳ����ܹ�.
*
*����:Ф��, <email: planck_constant@foxmail.com>
*�汾:0.1
*�������:2015.12.
*
*/



#include"config.h"
#include"STC15Fxxxx.h"

//����
#include  "key.h"       //����ģ��
#include  "lcd1602.h"   
#include  "EEPROM.h"   
#include  "ADC.h"     
#include  "buzzer.h" 
#include  "timer.h" 
#include  "delay.h"
#include  "ntostr.h"

#define uint8     unsigned char
#define uint16    unsigned int

//����ģʽ����
#define MEASURE_MODE   0  //����ģʽ
#define SET_MODE       1  //����ģʽ(���ñ���ֵ)


//����Ĭ�ϵı���ֵ�ʹ����õı���ֵ�ʹ����ַ 
#define MAX_FORCE  10          //��ʼ����ֵΪ 10g
#define ADDR_MAX_FORCE  0x0010  

//��������������ֲ�ͬ������ֵ. continus������������discontinus��ϵ����� 
#define CONTINU 0
#define DISCONTINU 1

/* AD���� */
ADC_InitTypeDef ADC_Struct={ ADC_P10,    	//����A/D
           ADC_540T,ENABLE, ADC_RES_H2L8,PolityHigh, ENABLE };

/* ��ʱ������ 
   16-bit�Զ�����, ��ʱ��i��ֵ=0,
   δ�����ж�, ��ʼʱδ����        */
TIM_InitTypeDef Timer0_Struct={
                   	 TIM_16BitAutoReload,
					 PolityHigh,
					 DISABLE,
					 TIM_CLOCK_12T,
					 DISABLE,
					 63488,     //��ʱ����ʼֵ=0
					 DISABLE };

uint8 flag = MEASURE_MODE;  //����MCU����ģʽ�ı�־
uint16 NumOfVoltConvert = 0; // �����ѹ��A/Dת�����ֵ

#define EnableTimer0IRQ()   (ET0 = 1)
#define DisableTimer0IRQ()  (ET0 = 0)

int main(void)
{
  uint16 force_g; // ��λΪ g ����
  uint16 maxForce, deltaForce;
  uint8 key;
  uint8 string[10]; //�����ַ���
  while (1)
  {
    //��ʼ��A/D, ��ʱ��0
    InitLCD();
    ADC_Inilize(&ADC_Struct);
    Timer_Inilize(Timer0, &Timer0_Struct);

     switch (flag)
     {
        // ����ģʽ
	case MEASURE_MODE:     
		/*
		 * ��һЩ��ʼ��:
		 * ��ʼ��lcd������eerpom�����ֵ,����A/D
		 */
        InitLCD();
        WriteLCDStr(0x0a, "Normal");
        WriteLCDStr(0x43, "00  g");
        EEPROM_read_n(ADDR_MAX_FORCE, string, 2);  
		maxForce = string[0] + 256 * string[1];
          delay_ms(10);  //�ӳ� 10 ms, �ȴ�����
          while (1) 
          {
            /* �������״̬�� ֱ������MODE���˳� */
             force_g = (100UL * NumOfVoltConvert / 266) - 10UL;
             WriteLCDStr(0x43, N16ToStr(force_g, string) );
	     
	     if (force_g >= maxForce)
             { 
	         if (force_g >= (maxForce+2))  //��ϵ����������û����ܽӽ�Ԥ���ֵ�ˣ�
		 {			       //���������������û����е��ҪСһ��
		     
	             DisableTimer0IRQ(); //�ض�ʱ��0�ж�
		     OpenBuzzer(CONTINU); //��������
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

	     //����ɨ��
	     if ( (key=ReadKey()) == KEY_MODE )
	     {
	        ADC_PowerControl(DISABLE);
		flag++;
		break;
	     }              
	  }           //����ģʽ����
			     
        //����ģʽ			     
	case SET_MODE:
		/*
		 * ��һЩ����ģʽ�µĳ�ʼ��:
		 * ��ʼ��lcd, ��ȡeeprom��maxForceֵ������ʾ��
		 * Ȼ��ȴ�����
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
     } //switch�ڴ˽���

     if (flag>=2)
     {
        flag=0;
     }

   } //���while�ڴ˽���

}

void ADC_InterruptService(void) interrupt 5
{
   /* A/D 10-bitģʽ,ADC_RESL ��8λ��
      ADC_RES ��2λ			*/
   NumOfVoltConvert = (ADC_RES * 256) + ADC_RESL; 
   ADC_CONTR &= (~ADC_FLAG);
   ADC_PowerControl(ENABLE);
}


void Timer0_InterruptService(void) interrupt 1 
{
  OpenBuzzer(DISCONTINU);
  EnableTimer0IRQ();
}   


