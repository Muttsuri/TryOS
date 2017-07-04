#include "port.h"

/*
  Ports is the name given to specific adresses of the x86 (32bit) IO Bus (identified by a range represented by the portnumber value)
  Information Source: http://wiki.osdev.org/I/O_Ports
  Source Code From Video
  Unfortunatly the video does not go into detail about what each of the code parts do.
 */

//instanciate a port
Port::Port(u16 portnumber)
{
  this->portnumber=portnumber;
}

Port::~Port() {} //Instanciate Destructor


      /*8bitPorts*/

Port8Bit::Port8Bit(u16 portnumber): Port(portnumber) {}//8bit port instanciation

Port8Bit::~Port8Bit() {} //8bit Destructor

void Port8Bit::Write(u8 data)
{
  Write8(portnumber, data);
}

u8 Port8Bit::Read()
{
  return Read8(portnumber);
}



    /*slow*/
Port8BitSlow::Port8BitSlow(u16 portnumber): Port8Bit(portnumber) {}

Port8BitSlow::~Port8BitSlow() {}

void Port8BitSlow::Write(u8 data)
{
 Write8Slow(portnumber, data);
}

    /*Slow end*/

      /*8bit end*/

      
      
     
    /*16bit Ports*/
Port16Bit::Port16Bit(u16 portnumber): Port(portnumber) {} //16bit port instanciation

Port16Bit::~Port16Bit() {} //16bit Destructor 
  /*16bit IO*/
void Port16Bit::Write(u16 data)
{
  Write16(portnumber, data);
}

u16 Port16Bit::Read()
{
  return Read16(portnumber);
}
  /*16bit IO end*/

    /*16bit end*/


    
    
    
    /*32bit ports*/
Port32Bit::Port32Bit(u16 portnumber): Port(portnumber) {}

Port32Bit::~Port32Bit() {}

  /*32bit IO end*/
void Port32Bit::Write(u32 data)
{
  Write32(portnumber, data);
}

u32 Port32Bit::Read()
{
  return Read32(portnumber);
}
  /*32bit IO end*/
    /*32bit end*/
