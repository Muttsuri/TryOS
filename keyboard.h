#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "keyboard.h"

class KeyboardDriver : public InterruptHandler
{
  Port8Bit DataPort;
  Port8Bit CmdPort;
public:
  KeyboardDriver(InterruptManager* intmgr/*, u8 interruptNumber*/);
  ~KeyboardDriver();
  virtual u32 HandleInterrupt(u32 esp);
};

#endif