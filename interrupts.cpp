#include "interrupts.h"

/*Foward defenition of printf*/
void printf(const char* str);

InterruptManager::GateDescriptor InterruptManager::InterruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
	    u8 interruptNumber,
        u16 gdt_codeSegmentSelector,
        void (*handler)(), 
        u8 DescriptorPrivilegeLevel,
        u8 DescriptorType
) 
{
	const u8 IDT_DESC_PRESENT = 0x80;

	InterruptDescriptorTable[interruptNumber].HandlerAddressLowBits = ((u32)handler) & 0xFFFF;
	InterruptDescriptorTable[interruptNumber].HandlerAddressHighBits = (((u32)handler) >> 16) & 0xFFFF;
	InterruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	InterruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel&3) <<5) ;
	InterruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GlobalDescriptorTable gdt)
{
	u16 CodeSegment = gdt->CodeSegmentSelector();
	const u8 IDT_INTERRUPT_GATE = 0xE;

	/*Set All non-Explicit entries to be ignored so that there won't be a global fault and a system crash*/
	for(u16 i=0; i<256;i++)
		SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0/*Kernel Level*/, IDT_INTERRUPT_GATE);

	/*Explicit Enteries*/
	// NOTE: 0x20 -> 0x00 and 0x21 -> 0x01, Becuase it increments by 0x20 on the HandleInterruptRequest	
	SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptResquest0x00, 0, IDT_INTERRUPT_GATE); //Timer
	SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptResquest0x01, 0, IDT_INTERRUPT_GATE); //Keyboard

	/*Tell the cpu to use the IDT*/
	InterruptDescriptorTablePointer idt;
	idt.size = 256 * sizeof(GateDescriptor) -1;
	idt.base = (u32)InterruptDescriptorTable;
	__asm__ volatile ("lidt %0" : : "m" (idt)); //Use idt
};

InterruptManager::~InterruptManager() {};

void InterruptManager::Activate()
{
	__asm__ ("sti"); //Start Interrupts
}


u32 InterruptManager::HandleInterrupt(u32 interruptNumber, u32 esp)
{
	printf("Interrupt"); //reason for foward of printf
	return esp; //for now only returns stack pointer
}