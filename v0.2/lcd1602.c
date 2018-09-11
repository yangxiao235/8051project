#include "lcd1602.h"
#include "delay.h"
#include "config.h"

sbit LCD_RS = P2^5;
sbit LCD_RW = P2^6;
sbit LCD_EN = P2^7;

#define LCD_DATA_PORT P0


/*
*
* ����: ���lcd��æ״̬
* ����: ��
* ���: bit 0��1
*
*/
bit IsLCDBusy()
{                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delay_us(4);     //�ӳ� 4 us
    result = (bit)(LCD_DATA_PORT & 0x80);
    LCD_EN = 0;
    return(result); 
}
 

/*
*
* ����: ��LCD 1602д�뵥������
* ����: ���� cmd
* ����: ��
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
* ����: ��LCD 1602д 1 �ֽ�����
* ����: һ�ֽ����� dat
* ����: ��
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
* ����: �趨LCD 1602д���ַ�������ĸ����Ļ��λ��
* ����: λ�ô� 0x80��ʼ
* ����: ��
*
*/
void SetLCDPos(uint8 pos)
{                          
  WriteLCDCmd(pos | 0x80); 
}


/*
*
* ����: ��ʼ��LCD 1602
* ����: ��
* ���: ��
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
* ����: ��LCDд���ַ���
* ����: ��ַpos, �ַ����׵�ַ str
* ����: �ַ����׵�ַ str
*
*/
void WriteLCDStr(uint8 pos, uint8 *str)
{
    uint8 i=0;
    SetLCDPos(pos);

    while (str[i] != 0)
        WriteLCDData(str[i++]);
}

