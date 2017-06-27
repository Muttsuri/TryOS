/*Prevents multiple insatnsiations of this code for each time it is called*/
#ifndef __GDT_H //if the code hasn't been instansiated
#define __GDT_H //instansiate it

#include "types.h" //type defenition inclusion

/*Class that defines the enteries of the Global Descriptor Table*/

class GlobalDescriptorTable
{
  public:
    class SegmentDescriptor
    {
      private:
	u16 limit_lo;
	u16 base_lo;
	u8 base_hi;
	u8 type;
	u8 limit_hi;
	u8 base_vhi;
      public:
	SegmentDescriptor(u32 base,u32 limit, u8 type);
	u32 Base(); //Pointer to Memeory Block
	u32 Limit(); //Size of the Memory Block
    } __attribute__((packed)); //for byte perfect comuntication

    
    SegmentDescriptor nullSegmentSelector; //Defines memory speace as empty
    SegmentDescriptor unusedSegmentSelector; //Defines mempru space as unused
    SegmentDescriptor codeSegmentSelector; //Defines memory space as code
    SegmentDescriptor dataSegmentSelector; //Defines memory space as datas
    
    public:
      GlobalDescriptorTable(); //Constructor
      ~GlobalDescriptorTable(); //Destructor
      
      u16 CodeSegmentSelector(); 
      u16 DataSegmentSelector();
};

#endif //else skip the instansiation of the code (this allows correct compilation)