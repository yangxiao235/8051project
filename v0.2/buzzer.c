#include "config.h"
#include "buzzer.h"

//蜂鸣器引脚
sbit buzzer=P2^0;

/*
*功能：0, 表示使蜂鸣器发出连续的声音
*      1, 表示使蜂鸣器发出间断的声音(和定时器配合)
*参数: 0(CONTINUE), 1(DISCONTINUE) 
*返回值:无
*/

void  OpenBuzzer(uint8 status) 
{
    if ( 1 == status ) // 1=间断声音选项
    {
        buzzer =  ~buzzer;
    }
    else              // 0=连续声音选项
    {
        buzzer = 1;
    }
}
       



/*
*功能:关闭蜂鸣器
*参数:无
*返回值:无
*/
void CloseBuzzer()
{ 
    buzzer = 0;   
}

