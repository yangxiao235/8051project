#ifndef    KEY_H
#define    KEY_H

#define uint8    unsigned char
#define uint16   unsigned int

// ɨ����
#define KEY_MODE   0x1c   //ģʽѡ���ɨ����
#define KEY_ADD    0x2c   // + ��ɨ����
#define KEY_DEC    0x34   // - ��ɨ����
#define KEY_10g    0x38   // 10g/1g �л���ɨ����
#define KEY_NOP    0x3c   //�޼�����ʱ��ɨ����   

uint8 ReadKey(void);

#endif
