#include "ntostr.h"

// string[]数组数字排列方式:string = "123"(即123,最高位在string[0])
uint8 *N8ToStr(uint8 n8, uint8 string[])
{
    if (n8 < 10) //个位数
    {
        string[0] = '0'; 
        string[1] = '0';
        string[2] = '0' + n8;
        string[3] = 0;
        return string;
    }

    string[0] = (n8 / 100) + '0';   //百位
    string[1] = ((n8 % 100) / 10)+ '0';  //十位
    string[2] = (n8 % 10) + '0'; //个位
    string[3] = 0; 
    return string;
}


//转换的数字最大为9999
uint8 *N16ToStr(uint16 n16, uint8 string[])
{
    uint8 tmp;
    if (n16 < 10) //个位数
    {
        string[0] = '0';
        string[1] = '0'; 
        string[2] = '0';
        string[3] = '0' + (uint8)n16;
        string[4] = 0;
        return string;
    }

    string[0] = n16 / 1000 + '0';  //千位
    tmp = n16 % 1000;
    string[1] = tmp / 100 + '0';   //百位
    tmp = tmp % 100;
    string[2] = tmp / 10 + '0';    //十位
    string[3] = tmp % 10 + '0';    //个位
    string[4] = 0;

    return string;
}
