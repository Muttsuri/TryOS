
#ifndef __INTERUPTS_H
#define __INTERUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager
{
    protected:
        struct GateDescriptor
        {
	    /*Address of the handler is split*/
            u16 HandlerAddressLowBits;   //low bits of the Adress
            u16 gdt_codeSegmentSelector; //offset of the GDT Code Segment
            u8 reserved;		 //1 reserved byte
            u8 access;                   //access permitions (rings 0 to 3) [kernelspace = 0, userspace = 3]
            u16 HandlerAddressHighBits;  //high bits of the Adress

        } __attribute__((packed)); //for byte perfect comuntication;
    
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
        /*Constructor and Destructor of the Interupt Manager Class*/
        InterruptManager(GlobalDescriptorTable gdt); //get pointer to GDT
        ~InterruptManager();

        void Activate();

        static u32 HandleInterrupt(u32 interruptNumber, u32 esp/*Current Stack Pointer*/);

        static void IgnoreInterruptRequest();
        static void HandleInterruptResquest0x00(); //0x00 (Interrupt Timer)
        static void HandleInterruptResquest0x01(); //0x01 (Keyboard)
};

#endif
