/*
*
* �ļ���:init.h
* ����: ��ÿ��ģʽ��ʼ֮ǰ����һЩ��ʼ���Ĺ�����
*
*/

#ifndef INIT_H
#define INIT_H

void Init(ADC_InitTypeDef *ADC_Struct, 	
          unsigned char Timerx, 
		  TIM_InitTypeDef *Timerx_Struct);  //��ʼ��LCD��ADC����ʱ��0
void InitMeasureMode(void);   //��ʼ������ģʽ
void InitSetMode(void);   //��ʼ������ģʽ

#endif
