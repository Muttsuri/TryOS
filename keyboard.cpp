#include "keyboard.h"

void printf(const char* str);

KeyboardDriver::KeyboardDriver(InterruptManager* intmgr): InterruptHandler(intmgr, 0x21), DataPort(0x60), CmdPort(0x64)
{
  //Wait for key release
  while(CmdPort.Read() & 0x1)
  {
    DataPort.Read();  
  }
  CmdPort.Write(0xAE); //Activate Keyboard Interrupts / tell keyboard to comunicate with interrupts
  CmdPort.Write(0x20); //Get Current state
  u8 status = (DataPort.Read() | 1) & ~0x10; //set rightmost bit to 1 as new state and clear 5th bit
  CmdPort.Write(0x60); //Tell PIC/Keyboard to change current state
  DataPort.Write(status); //Write new state to Keyboard/PIC
  
  DataPort.Write(0xF4); //Activate Keyboard
  
}

KeyboardDriver::~KeyboardDriver() {}

u32 KeyboardDriver::HandleInterrupt(u32 esp)
{
  u8 key = DataPort.Read();
  
      char* foo = "KEYBOARD 0x00";
      char* hex = "0123456789ABCDEF";
      foo[22] = hex[(key >> 4) & 0x0F];
      foo[23] = hex[key & 0x0F];
      printf(foo);
  
  return esp;
}

