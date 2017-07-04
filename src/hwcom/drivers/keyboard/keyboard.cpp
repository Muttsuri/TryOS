#include "keyboard.h"

void printf(const char* str);

KeyboardDriver::KeyboardDriver(InterruptManager* intmgr): InterruptHandler(intmgr, 0x21), DataPort(0x60), CmdPort(0x64)
{
  //Wait for key release
  while(CmdPort.Read() & 0x1)
  {
    DataPort.Read();  
  }
  CmdPort.Write(0xAE); 				//Activate Keyboard Interrupts / tell keyboard to comunicate with interrupts
  CmdPort.Write(0x20); 				//Get Current state
  u8 status = (DataPort.Read() | 1) & ~0x10; 	//set rightmost bit to 1 as new state and clear 5th bit
  CmdPort.Write(0x60); 				//Tell PIC/Keyboard to change current state
  DataPort.Write(status); 			//Write new state to Keyboard/PIC
  
  DataPort.Write(0xF4); 			//Activate Keyboard
  
}

KeyboardDriver::~KeyboardDriver() {}

u32 KeyboardDriver::HandleInterrupt(u32 esp)
{
  u8 key = DataPort.Read();
  if (key < 0x80)
  {
    switch(key)
    {
      case 0xFA:
	break;
      case 0x45:
      case 0xC5:
	break;

      //control chracters
      case 0x39 : printf(" ");break;
      case 0x1C : printf("\n");break;
      case 0x01 : printf("ESC");break;
//       case 0x1E : printf("LSHIFT");break;
//       case 0x1E : printf("RSHIFT");break;
//       case 0x1E : printf("CTL");break;
//       case 0x1E : printf("ALT");break;
      case 0x0E : printf("\b");break;
      case 0x35 : printf("-");break;
      
  
      
      //Normal Characters
      case 0x1E : printf("a");break;
      case 0x30 : printf("b");break;
      case 0x2E : printf("c");break;
      case 0x20 : printf("d");break;
      case 0x12 : printf("e");break;
      case 0x21 : printf("f");break;
      case 0x22 : printf("g");break;
      case 0x23 : printf("h");break;
      case 0x17 : printf("i");break;
      case 0x24 : printf("j");break;
      case 0x25 : printf("k");break;
      case 0x26 : printf("l");break;
      case 0x32 : printf("m");break;
      case 0x31 : printf("n");break;
      case 0x18 : printf("o");break;
      case 0x19 : printf("p");break;
      case 0x10 : printf("q");break;
      case 0x13 : printf("r");break;
      case 0x1F : printf("s");break;
      case 0x14 : printf("t");break;
      case 0x16 : printf("u");break;
      case 0x2F : printf("v");break;
      case 0x2D : printf("x");break;
      case 0x11 : printf("w");break;
      case 0x15 : printf("y");break;
      case 0x2C : printf("z");break;
	
      //Numbers (no numpad)
      case 0x02 : printf("1");break;
      case 0x03 : printf("2");break;
      case 0x04 : printf("3");break;
      case 0x05 : printf("4");break;
      case 0x06 : printf("5");break;
      case 0x07 : printf("6");break;
      case 0x08 : printf("7");break;
      case 0x09 : printf("8");break;
      case 0x0A : printf("9");break;
      case 0x0B : printf("0");break;
      
      
	
      default:
	char* foo = "KEYBOARD 0x00 ";
	char* hex = "0123456789ABCDEF";
	foo[11] = hex[(key >> 4) & 0x0F];
	foo[12] = hex[key & 0x0F];
	printf(foo);
    }
  } 
  return esp;
}

