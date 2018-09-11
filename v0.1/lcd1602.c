#include "lcd1602.h"
#include "delay.h"
#include "config.h"

sbit LCD_RS = P2^5;
sbit LCD_RW = P2^6;
sbit LCD_EN = P2^7;

#define LCD_DATA_PORT P0


/*
*
* 功能: 检查lcd的忙状态
* 输入: 无
* 输出: bit 0或1
*
*/
bit IsLCDBusy()
{                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delay_us(4);     //延迟 4 us
    result = (bit)(LCD_DATA_PORT & 0x80);
    LCD_EN = 0;
    return(result); 
}
 

/*
*
* 功能: 向LCD 1602写入单个命令
* 输入: 命令 cmd
* 返回: 无
*
*/
void WriteLCDCmd(uint8 cmd)
{                          
    while(IsLCDBusy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DATA_PORT = cmd;
              
    LCD_EN = 0;   
    delay_us(4);
    LCD_EN = 1; 
    delay_us(4);  
    LCD_EN=0;
    delay_us(4);
}  


/*
*
* 功能: 向LCD 1602写 1 字节数据
* 输入: 一字节数据 dat
* 返回: 无
*
*/
void WriteLCDData(uint8 dat)
{                          
    while(IsLCDBusy());
    LCD_RS = 1;
    LCD_RW = 0;
    delay_us(4);
    LCD_DATA_PORT = dat;
    LCD_EN = 0;
    delay_us(4); 
    LCD_EN = 1; 
    delay_us(4);
    LCD_EN=0;
    delay_us(4);
}


/*
*
* 功能: 设定LCD 1602写入字符串首字母在屏幕的位置
* 输入: 位置从 0x80开始
* 返回: 无
*
*/
void SetLCDPos(uint8 pos)
{                          
  WriteLCDCmd(pos | 0x80); 
}


/*
*
* 功能: 初始化LCD 1602
* 输入: 无
* 输出: 无
*
*/
void InitLCD()
{ 

    WriteLCDCmd(0x38);
    delay_ms(1);       
    WriteLCDCmd(0x08);
    delay_ms(1);       
    WriteLCDCmd(0x01);
    delay_ms(1);      
    WriteLCDCmd(0x06);
    delay_ms(1);       
    WriteLCDCmd(0x0c);
    delay_ms(1);      
}


/*
*
* 功能: 向LCD写入字符串
* 输入: 地址pos, 字符串首地址 str
* 返回: 字符串首地址 str
*
*/
void WriteLCDStr(uint8 pos, uint8 *str)
{
    uint8 i=0;
    SetLCDPos(pos);

    while (str[i] != 0)
        WriteLCDData(str[i++]);
}

