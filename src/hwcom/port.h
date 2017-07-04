#ifndef __PORT_H 
#define __PORT_H 

#include "../types.h"
/*
  Declaration of the types of ports and fucntions that the ports must have.
  Source Code From Video
  Unfortunatly the video does not go into detail about what each of the code parts do.
  */

class Port //Define things equal to all ports
{
protected: //protected so it can't be instanciated (it's a purely virtual class)
	u16 portnumber; //port number is always 16bit
	Port(u16 portnumber); //Constructor
	// these should be virtual but they are not becuse the kernel does not have memory manangement yet
	~Port(); //Destructor
};


class Port8Bit:public Port //8bit port inherits Port
{
public:
	Port8Bit(u16 portnumber);
	~Port8Bit();
	virtual void Write(u8 data);
	virtual u8 Read();
protected:
	/*8bit IO*/
	static inline void Write8(u16 portnumber,u8 data)
	{
	__asm__ volatile("out %0, %1" : : "a" (data), "Nd" (portnumber));
	}
	static inline u8 Read8(u16 portnumber)
	{
	u8 result;
	__asm__ volatile("in %1, %0" : "=a" (result) : "Nd" (portnumber));
	return result;
	}
	/*8bit IO end*/
};


class Port8BitSlow:public Port8Bit //8bit slow port inherits Port8
{
public:
	Port8BitSlow(u16 portnumber);
	~Port8BitSlow();
	virtual void Write(u8 data);
protected:
	static inline void Write8Slow(u16 portnumber,u8 data)
	{
	__asm__ volatile("out %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (portnumber)); //\njmp 1f\n1: jmp 1f\n1:-> just a few jumps to slow down sligly the writing of data to the port
	}
	//inherits read from Port8Bit so no need to declare it
};


class Port16Bit:public Port //16bit port inherits Port
{
public:
	Port16Bit(u16 portnumber);
	~Port16Bit();
	virtual void Write(u16 data);
	virtual u16 Read();
  protected:
	/*16bit IO*/
	static inline void Write16(u16 portnumber,u16 data)
	{
	__asm__ volatile("out %0, %1" : : "a" (data), "Nd" (portnumber));
	}
	static inline u8 Read16(u16 portnumber)
	{
	u16 result;
	__asm__ volatile("in %1, %0" : "=a" (result) : "Nd" (portnumber));
	return result;
	}
	/*16bit IO end*/
};


class Port32Bit:public Port //32bit port inherits Port
{
public:
	Port32Bit(u16 portnumber);
	~Port32Bit();
	virtual void Write(u32 data);
	virtual u32 Read();
protected:
	/*32bit IO*/
	static inline void Write32(u16 portnumber,u32 data)
	{
	__asm__ volatile("out %0, %1" : : "a" (data), "Nd" (portnumber));
	}
	static inline u8 Read32(u16 portnumber)
	{
	u32 result;
	__asm__ volatile("in %1, %0" : "=a" (result) : "Nd" (portnumber));
	return result;
	}
	/*32bit IO end*/
};



#endif
