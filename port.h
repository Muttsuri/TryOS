#ifndef __PORT_H 
#define __PORT_H 

#include "types.h"


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
};


class Port8BitSlow:public Port8Bit //8bit slow port inherits Port8
{
public:
  Port8BitSlow(u16 portnumber);
  ~Port8BitSlow();
  virtual void Write(u8 data);
  //inherits read from Port8Bit so no need to declare it
};


class Port16Bit:public Port //16bit port inherits Port
{
public:
  Port16Bit(u16 portnumber);
  ~Port16Bit();
  virtual void Write(u16 data);
  virtual u16 Read();
};


class Port32Bit:public Port //32bit port inherits Port
{
public:
  Port32Bit(u16 portnumber);
  ~Port32Bit();
  virtual void Write(u32 data);
  virtual u32 Read();
};



#endif
