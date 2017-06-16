#include "port.h"


//instanciate a port
Port::Port(u16 portnumber)
{
  this -> portunuber=portnumber;
}

Port::~Port() {} //Instanciate Destructor





      /*8bitPorts*/

Port8Bit::Port8Bit(u16 portnumber): Port(portnumber) //8bit port instanciation
{
  u8 Port(portnumber);
}

Port8Bit::~Port8Bit() {} //8bit Destructor

  /*8bit IO*/
void Port8Bit::Write(u8 data)
{
  __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portunuber));
}
u8 Port8Bit::Read()
{
  u8 result;
  __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portunuber));
  return result;
}
  /*8bit IO end*/

    /*slow*/
Port8BitSlow::Port8BitSlow(u16 portnumber): Port8Bit(portnumber)
{  
  u8 Port8Bit(portnumber);
}

Port8BitSlow::~Port8BitSlow() {}

void Port8BitSlow::Write(u8 data)
{
  __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1" : : "a" (data), "Nd" (portunuber));
}

    /*Slow end*/

      /*8bit end*/


      
      
     
    /*16bit Ports*/
Port16Bit::Port16Bit(u16 portnumber): Port(portnumber) //16bit port instanciation
{
  u16 Port(portnumber);
}
Port16Bit::~Port16Bit() {} //16bit Destructor 
  /*16bit IO*/
void Port16Bit::Write(u16 data)
{
  __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portunuber));
}
u16 Port16Bit::Read()
{
  u8 result;
  __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
  return result;
}

  /*16bit IO end*/

    /*16bit end*/


    
    
    
    /*32bit ports*/
Port32Bit::Port32Bit(u16 portnumber): Port()
{
    u32 Port(portnumber);
}

Port32Bit::~Port32Bit() {}

  /*32bit IO end*/
void Port32Bit::Write(u32 data)
{
  __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portunuber));
}

u32 Port32Bit::Read()
{
  u8 result;
  __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
  return result;
}
  /*32bit IO end*/
    /*32bit end*/