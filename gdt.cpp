#include "gdt.h" 
#include "types.h"

/*This constructs the Global Descriptor Table*/

GlobalDescriptorTable::GlobalDescriptorTable() //Construct a segment
/*Initiate the Segment Selectors*/
: nullSegmentSelector(0,0,0),
    unusedSegmentSelector(0,0,0),
    codeSegmentSelector(0,64*1024*1024,0x9A),
    dataSegmentSelector(0,64*1024*1024,0x92)
  {
    /*Tell the processor to use the created table
      NOTE: The CPU expects 6 bytes in a row of information*/
    
    u64 i[2]; //8bytes (I think it's 4 by types.h)
    i[0] = sizeof(GlobalDescriptorTable) << 16; //Size of the Table (<< 16, shitft to the left [high bites big endian])
    i[1] = (u32)this; //adress of the table
    
    /*Assembly to tell the cpu to use the table*/
   __asm__ volatile("lgdt (%0)": :"p"(((u8 *)i)+2)); //Load Global Descriptor Table (lgdt)
  } 
  
GlobalDescriptorTable::~GlobalDescriptorTable()
{
	/*Does nothing for now
	 *it should unload the GDT*/
}


u16 GlobalDescriptorTable::DataSegmentSelector()
{
	return (u8 *)&dataSegmentSelector - (u8 *)this; //return: get address of the Data Segment Selector (&dataSegmentSelector) and subtracting the segment of the table
}

u16 GlobalDescriptorTable::CodeSegmentSelector()
{
	return (u8 *)&codeSegmentSelector - (u8 *)this; //return: get address of the Code Segment Selector (&dataSegmentSelector) and subtracting the segment of the table
}


/*Set the enteries*/
GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(u32 base, u32 limit, u8 type)
{
  u8* target = (u8*)this;
  if (limit <= 65536) //if 16bit limit
  {
    target[6] = 0x40; //16 bit entry
    /*For a 16bit Address Space*/
  }
  else //aka for a 32 bit Address Space
  {
    if(limit & 0xFFF) //if the last 12 bits of the limit are not all " 1 "
    {
      limit = (limit >> 12)-1; //set the limti to the limit shifted by 12 and then subtracted by 1
    }
    else
    {
      limit = limit >>12; //set it to the limit shift it by 12
    }
    target[6] = 0xC0; //set 6th bite to 0xC0
  }
  
  /*Define the position of the limit
    NOTE: the bytes of the GDT entery are counted from "right to left" (little endian?) 
	  as in, byte[0] is the last one and bite [7] the first one (last and 1st byte respectively)*/
  
  /*Set of Limit*/
  target[0] = limit & 0xFF; //last 8 bits (last byte) = less significant bytes of the limit
  target[1] = (limit >> 8) & 0xFF; //Next 8 bits
  //Last 2 bytes done
  target[6] = (limit >> 16) & 0xF;
  
  /*Pointer/Base Destibution*/
  target[2] = base  & 0xFF;
  target[3] = (base >> 8) & 0xFF;
  target[4] = (base >> 16) & 0xFF;
  target[7] = (base >> 24) & 0xFF;
  
  /*Type/Flag Setting*/
  target[5] = type;
  
}



u32 GlobalDescriptorTable::SegmentDescriptor::Base()
{
  //Base preserves all the 4 bites to it's easy
  u8* target = (u8*)this;
  u32 result = target[7]; //take 7th bite
  result = (result << 8) + target[4]; //shift to the left and add the value of target [4]
  result = (result << 8) + target[3]; //shift to the left and add the value of target [3]
  result = (result << 8) + target[2]; //shift to the left and add the value of target [2]
  return result;
}

u32 GlobalDescriptorTable::SegmentDescriptor::Limit()
{
  //Harder as the limit is more destributed through the entry
  //take the first 4 bits of the shared byte 6 and then to as in Base()
  u8* target = (u8*)this; 
  u32 result = target[6] & 0xF; //take the first 4 bits of the shared byte 6
  result = (result << 8) + target[1];
  result = (result << 8) + target[0];
  
  //only necessart if target[6] was set to 0xC0
  if ((target[6] & 0xC0) == 0xC0)
  result = (result <<12) | 0xFFF;
  
  return result;
}
