#include "key.h"
#include "config.h"
#include "delay.h"


// ����������MCU���ӵĶ˿�
#define KEYPORT P3


uint8 ReadKey(void)
{
    uint8 value;
    unsigned long t=300000;
    while ((value = (KEYPORT & KEY_NOP)) != KEY_NOP)
    {
       delay_ms(10);
       if (--t <=  0) // ����ѭ��ʱ�䣬������ѭ��
       {
           break;
       }
    }

	return value;
}
