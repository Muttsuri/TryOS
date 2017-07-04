
#ifndef __INTERRUPTMANAGER_H
#define __INTERRUPTMANAGER_H

  #include "../../types.h"
  #include "../port.h"
  #include "../../GDT/gdt.h"

class InterruptManager;
class InterruptHandler
{
    protected:
	    
        static InterruptManager* ActiveInterruptManager;
	u8 interruptNumber;
	InterruptManager* intmgr;
	InterruptHandler(InterruptManager* intmgr, u8 interruptNumber);
	~InterruptHandler();
    public:
	virtual u32 HandleInterrupt(u32 esp);
};

class InterruptManager
{
	friend class InterruptHandler;
protected:
	static InterruptManager* ActiveInterruptManager; //To allow just one Interrupt Manager at any one time
	/*Theoreticly there could be more than one Manager however because the Sytem/CPU only has 1 IDT
	  As such it only makes sence to have one Interrupt Manager*/
	
	/*IDT but at a higher level*/
	InterruptHandler* handlers[256];
	
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

	u16 hwinterruptOffset;
	
	static void SetInterruptDescriptorTableEntry(
	  u8 interruptNumber,
	  u16 gdt_codeSegmentSelector,
	  void (*handler)(), //pointer to the handler
	  u8 DescriptorPrivilegeLevel,
	  u8 DescriptorType
	); 
	

	static void IgnoreInterruptRequest();
	
	static void HandleInterruptResquest0x00(); //0x00 (Interrupt Timer)
	static void HandleInterruptResquest0x01(); //0x01 (Keyboard)
	
	static void HandleException0x00();
	static void HandleException0x01();

    	static u32 HandleInterrupt(u8 interruptNumber, u32 esp/*Current Stack Pointer*/);
	u32 DoHandleInterrupt(u32 interruptNumber, u32 esp/*Current Stack Pointer*/);
	
	/*Ports to comunicate with the Programable Interface Controler
	  NOTE: There are 4 Types of PIC's but they are refered in bulk
		Threre is a Master and Slave Pic, both have Command and Data Types*/
	Port8BitSlow picMasterCommand;
	Port8BitSlow picMasterData;
	Port8BitSlow picSlaveCommand;
	Port8BitSlow picSlaveData;

	/*This is the device that passes the interrupt to the cpu and in x86 it incorporated into the Motherboard's SouthBridge*/
	

    public:
        /*Constructor and Destructor of the Interupt Manager Class*/
        InterruptManager(u16 hwinterruptOffset, GlobalDescriptorTable* gdt); //get pointer to GDT
        ~InterruptManager();
	
	u16 HardwareInterruptOffset();
	
        void Activate();
	void Deactivate();
};


#endif
