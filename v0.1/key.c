#include "key.h"
#include "config.h"
#include "delay.h"


// 按键引脚与MCU连接的端口
#define KEYPORT P3


uint8 ReadKey(void)
{
    uint8 value;
    unsigned long t=300000;
    while ((value = (KEYPORT & KEY_NOP)) != KEY_NOP)
    {
       delay_ms(10);
       if (--t <=  0) // 设置循环时间，避免死循环
       {
           break;
       }
    }

	return value;
}
