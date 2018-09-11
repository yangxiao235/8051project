#ifndef LCD1602_H
#define LCD1602_H

#define uint8    unsigned char
#define uint16   unsigned int

bit  IsLCDBusy();
void WriteLCDCmd(uint8 cmd);
void WriteLCDData(uint8 dat);
void SetLCDPos(uint8 pos);
void InitLCD();
void WriteLCDStr(uint8 pos, uint8 *str);



#endif 

