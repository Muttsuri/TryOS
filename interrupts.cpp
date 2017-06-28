#include "interrupts.h"


InterruptManager::GateDescriptor InterruptManager::InterruptDescriptorTable[256];

//InterruptManager* InterruptManager::ActiveInterruptManager = 0; 

void InterruptManager::SetInterruptDescriptorTableEntry(
	u8 interruptNumber,
        u16 codeSegmentSelectorOffset,
        void (*handler)(), 
        u8 DescriptorPrivilegeLevel,
        u8 DescriptorType 
) 
{
	const u8 IDT_DESC_PRESENT = 0x80;

	InterruptDescriptorTable[interruptNumber].HandlerAddressLowBits = ((u32)handler) & 0xFFFF;
	InterruptDescriptorTable[interruptNumber].HandlerAddressHighBits = (((u32)handler) >> 16) & 0xFFFF;
	InterruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	InterruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) <<5) | DescriptorType ;
	InterruptDescriptorTable[interruptNumber].reserved = 0;
}



InterruptManager::InterruptManager(u16 hwinterruptOffset, GlobalDescriptorTable* gdt)
/*To Instanciate the InterruptManager we need to intiate the ports to contact with the PIC and effectively have Interrupts*/
  :picMasterCommand(0x20),
   picMasterData(0x21),
   picSlaveCommand(0xA0),
   picSlaveData(0xA1)
{
	//hwinterruptOffset = this->HardwareInterruptOffset(); 
	this->hwinterruptOffset = hwinterruptOffset;
	u16 CodeSegment = gdt->CodeSegmentSelector();
	const u8 IDT_INTERRUPT_GATE = 0xE;
	const u8 kernel = 0;
	const u8 userland = 3;
	
	/*Set All non-Explicit entries to be ignored so that there won't be a global fault and a system crash*/
	for(u16 i=0; i>256;i++)
		SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, kernel/*Kernel Level*/, IDT_INTERRUPT_GATE);

	/*Explicit Enteries*/
	// NOTE: 0x20 -> 0x00 and 0x21 -> 0x01, Becuase it increments by 0x20 on the HandleInterruptRequest	
	SetInterruptDescriptorTableEntry(0x00, CodeSegment, &HandleException0x00, kernel, IDT_INTERRUPT_GATE); //Timer
	SetInterruptDescriptorTableEntry(0x01, CodeSegment, &HandleException0x01, kernel, IDT_INTERRUPT_GATE); //Keyboard

	SetInterruptDescriptorTableEntry(this->hwinterruptOffset + 0x00, CodeSegment, &HandleInterruptResquest0x00, kernel, IDT_INTERRUPT_GATE); //Timer
	SetInterruptDescriptorTableEntry(this->hwinterruptOffset + 0x01, CodeSegment, &HandleInterruptResquest0x01, kernel, IDT_INTERRUPT_GATE); //Keyboard
	
	/*Before telling the cpu to use the IDT we comunicate with the PIC ports*/
	picMasterCommand.Write(0x11);
	picSlaveCommand.Write(0x11);
	
	//remap
	picMasterData.Write(this->hwinterruptOffset);
	picSlaveData.Write(this->hwinterruptOffset + 8);
// 	picMasterData.Write(0x20); //If any interrupt is caught add 0x20 to the value of the interrupt
// 	picSlaveData.Write(0x28);  //If any interrupt is caught add 0x28 to the value of the interrupt
// 	/*This is requited because by default the pics will return the value of 1 when they get an interrupt
// 	  which is a value used by the cpu internely for exeption, and as such that would cause errors*/
	
	picMasterData.Write(0x04); //Identify as Master
	picSlaveData.Write(0x02);  //Identify as Slave

	picMasterData.Write(0x01);
	picSlaveData.Write(0x01);

	picMasterData.Write(0x00);
	picSlaveData.Write(0x00);
	/*End of PIC Port Comunication*/
	
	/*Tell the cpu to use the IDT*/
	InterruptDescriptorTablePointer idt;
	idt.size = 256 * sizeof(GateDescriptor) -1;
	idt.base = (u32)InterruptDescriptorTable;
	__asm__ volatile ("lidt %0" : : "m" (idt)); //Use idt
}

InterruptManager::~InterruptManager() 
{
    Deactivate();
}

u16 InterruptManager::HardwareInterruptOffset()
{
  return hwinterruptOffset;
}

void InterruptManager::Activate()
{
// 	if(ActiveInterruptManager != 0)
// 	{
// 	  ActiveInterruptManager->Deactivate();
// 	}
// 	ActiveInterruptManager = this;
	__asm__ ("sti"); //Start Interrupts
}

void InterruptManager::Deactivate()
{
  //ActiveInterruptManager = 0;
  //__asm__("cli"); //Clear Interrupt
}

u32 InterruptManager::HandleInterrupt(u8 interruptNumber, u32 esp)
{	
// 	if(ActiveInterruptManager != 0)
// 	{
// 	  return ActiveInterruptManager->DoHandleInterrupt(interruptNumber, esp);
// 	}
	return esp; //for now only returns stack pointer
}
