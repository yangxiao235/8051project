/*
*
* 文件名:init.h
* 功能: 在每种模式开始之前，做一些初始化的工作。
*
*/

#ifndef INIT_H
#define INIT_H

void Init(ADC_InitTypeDef *ADC_Struct, 	
          unsigned char Timerx, 
		  TIM_InitTypeDef *Timerx_Struct);  //初始化LCD、ADC、定时器0
void InitMeasureMode(void);   //初始化测量模式
void InitSetMode(void);   //初始化设置模式

#endif
