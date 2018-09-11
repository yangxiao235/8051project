#ifndef    KEY_H
#define    KEY_H

#define uint8    unsigned char
#define uint16   unsigned int

// É¨ÃèÂë
#define KEY_MODE   0x1c   //Ä£Ê½Ñ¡Ôñ¼üÉ¨ÃèÂë
#define KEY_ADD    0x2c   // + ¼üÉ¨ÃèÂë
#define KEY_DEC    0x34   // - ¼üÉ¨ÃèÂë
#define KEY_10g    0x38   // 10g/1g ÇĞ»»¼üÉ¨ÃèÂë
#define KEY_NOP    0x3c   //ÎŞ¼ü°´ÏÂÊ±µÄÉ¨ÃèÂë   

uint8 ReadKey(void);

#endif
