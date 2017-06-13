#ifndef __TYPES_H
#define __TYPES_H

/*
 This is used to make sure that all the data transfers are bite perfect due to the fact that:
 1 -> We are working directly on the hardware
 2 -> Assebly always retuns 4 bytes of data
 
 Due to these it is requited that data sypes are specified to make sure that all comunication is byte perfect
 As an example a sound card might have a 32bit register on which a 32bit value and exactly a 32bit needs to be passed
 or a network packet with 16bits.
 
 On the case of comunticaton with assebly (which I belive that it will be minimal) if requited you can send only the first half of an
 8bite value and recive and half and desregard the rest (I supouse it has to do with hight and low bites as in hight being the frst half
 and the lower being the last half, this dicotomy is reverced for little endian [This has copious ammounts of assumsion])
 */

typedef signed char s8_t; //8 bit signed integer (byte)
typedef unsigned char u8_t; //8 bit unsigned integer (byte)

typedef signed short s16_t; //16 bit integer
typedef unsigned short u16_t; //16 bii unsigned integer

typedef signed int s32_t; //32 bit integer
typedef unsigned int u32_t; //32 bit unsigned integer

typedef signed long s64_t; //64 bit integer
typedef unsigned long u64_t; //64bit unsigned integer

/*
 Syntax gotten from Linux Kernel Development page 385
 */
#endif
