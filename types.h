/*Prevents multiple insatnsiations of this code for each time it is called*/
#ifndef __TYPES_H //if the code hasn't been instansiated
#define __TYPES_H //instansiate it

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

typedef signed char s8; //8 bit signed integer (1 byte)
typedef unsigned char u8; //8 bit unsigned integer (1 byte)

typedef signed short s16; //16 bit integer (2 byte)
typedef unsigned short u16; //16 bit unsigned integer (2 byte)

typedef signed long s32; //32 bit integer (4bytes)
typedef unsigned long u32; //32 bit unsigned integer (4bytes)

typedef signed long long int s64; //64 bit integer (8bytes)
typedef unsigned long long int u64; //64bit unsigned integer (8bytes)

/*
 Syntax gotten from Linux Kernel Development page 385
 Data types size acording with: http://www.learncpp.com/cpp-tutorial/23-variable-sizes-and-the-sizeof-operator/
 */
#endif //else skip the instansiation of the code (this allows correct compilation)
