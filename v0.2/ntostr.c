#include "ntostr.h"

// string[]�����������з�ʽ:string = "123"(��123,���λ��string[0])
uint8 *N8ToStr(uint8 n8, uint8 string[])
{
    if (n8 < 10) //��λ��
    {
        string[0] = '0'; 
        string[1] = '0';
        string[2] = '0' + n8;
        string[3] = 0;
        return string;
    }

    string[0] = (n8 / 100) + '0';   //��λ
    string[1] = ((n8 % 100) / 10)+ '0';  //ʮλ
    string[2] = (n8 % 10) + '0'; //��λ
    string[3] = 0; 
    return string;
}


//ת�����������Ϊ9999
uint8 *N16ToStr(uint16 n16, uint8 string[])
{
    uint8 tmp;
    if (n16 < 10) //��λ��
    {
        string[0] = '0';
        string[1] = '0'; 
        string[2] = '0';
        string[3] = '0' + (uint8)n16;
        string[4] = 0;
        return string;
    }

    string[0] = n16 / 1000 + '0';  //ǧλ
    tmp = n16 % 1000;
    string[1] = tmp / 100 + '0';   //��λ
    tmp = tmp % 100;
    string[2] = tmp / 10 + '0';    //ʮλ
    string[3] = tmp % 10 + '0';    //��λ
    string[4] = 0;

    return string;
}
