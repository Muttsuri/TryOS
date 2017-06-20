#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager
{
    protected:
        struct GateDescriptor
        {
            u16 HandlerAddressLowBits;   //low bits of the Adress
            u16 gdt_codeSegmentSelector; //code segment
            u8 reserved;
            u8 access;                   //access permitions (rings 0 to 3) [kernelspace = 0, userspace = 3]
            u16 HandlerAddressHighBits;   //high bits of the Adress

        } __attribute__((packed));
    
    static GateDescriptor InterruptDescriptorTable[256]; //array of 256 entries

    struct InterruptDescriptorTablePointer
    {
        u16 size; //Size of the entry
        u32 base; //Adress of the entry
    } __attribute__((packed));


    static void SetInterruptDescriptorTableEntry(
        u8 interruptNumber,
        u16 gdt_codeSegmentSelector,
        void (*handler)(), //pointer to the handler
        u8 DescriptorPrivilegeLevel,
        u8 DescriptorType
    ); 
    public:
        InterruptManager(GlobalDescriptorTable gdt);
        ~InterruptManager();

        void Activate();

        static u32 HandleInterrupt(u32 interruptNumber, u32 esp);

        static void IgnoreInterruptRequest();
        static void HandleInterruptResquest0x00(); // Timer
        static void HandleInterruptResquest0x01(); // Keyboard
};

#endif
