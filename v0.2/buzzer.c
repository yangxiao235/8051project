#include "config.h"
#include "buzzer.h"

//����������
sbit buzzer=P2^0;

/*
*���ܣ�0, ��ʾʹ��������������������
*      1, ��ʾʹ������������ϵ�����(�Ͷ�ʱ�����)
*����: 0(CONTINUE), 1(DISCONTINUE) 
*����ֵ:��
*/

void  OpenBuzzer(uint8 status) 
{
    if ( 1 == status ) // 1=�������ѡ��
    {
        buzzer =  ~buzzer;
    }
    else              // 0=��������ѡ��
    {
        buzzer = 1;
    }
}
       



/*
*����:�رշ�����
*����:��
*����ֵ:��
*/
void CloseBuzzer()
{ 
    buzzer = 0;   
}

