#include "ADC.h"
#include "EEPROM.h"
#include "timer.h"
#include "ntostr.h"
#include "lcd1602.h"

//����Ĭ�ϵı���ֵ�ʹ����õı���ֵ�ʹ����ַ 
#define MAX_FORCE  10          //��ʼ����ֵΪ 10g
#define ADDR_MAX_FORCE  0x0010  

#define uint16  unsigned int

void Init(ADC_InitTypeDef *ADC_Struct, 	
          unsigned char Timerx, 
		  TIM_InitTypeDef *Timerx_Struct)
{
    InitLCD();
    ADC_Inilize(&ADC_Struct);
    Timer_Inilize(Timerx, &Timerx_Struct);
}

void InitMeasureMode(uint16 maxForce)
{
    InitLCD();
    WriteLCDStr(0x0a, "Normal");
    WriteLCDStr(0x43, "00  g");
    EEPROM_read_n(ADDR_MAX_FORCE, &maxForce, 1);
}    

void InitSetMode(void)
{
    uint16 maxForceTemp;
    InitLCD();
    WriteLCDStr(0x0b, "Set");
    EEPROM_read_n(ADDR_MAX_FORCE, &maxForceTemp, 1);
    WriteLCDStr(0x45, "     g");
    WriteLCDStr(0x45, N16ToStr(maxForceTemp));
}


