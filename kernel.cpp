#include "types.h" //search for the file is extended from the standard comiler include bath to them plus the current source directory (if no path to another folder is pointed)
#include "gdt.h"
#include "interrupts.h"

void printf(const char* str)
{  
    static u16* VideoMemory = (u16*)0xb8000;//video memory starts at 0xb8000
    static u8 x=0, y=0; //initiate x and u cursor variables NOTE: Screen is by defautl 80 characters long and 25
    
    for(int i = 0; str[i] !='\0'; i++)
    {
	switch(str[i])
	{
	  case '\n': //line break
	    y++;
	    x=-1;

	  default:
	    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i]; /*This copies to video memory the value each character in the string
									      but it also copies the high byte of the video memory so that the characters remain white
									      this is the default of the video memory
									      after copying the high byte it combines it with the character to make the white charctet
									      high byte defines the colour of the character and the second defines the value to be presented.
									      
									      80*y+x -> computes the memory location that the character needs to be written to.*/
	    x++;
	}

	if (x>=80) //if cursor reaches the right edge of the screen move the cursor 1 line down
	{
	  y++;
	  x=0;
	}
	if (y > 25) //if cursor reaches the bottom of the screen, clear screen
	{
	  for(y=0; y<25; y++)
	  {
	     for(x=0; x<80; x++)
	     {
	       VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
	     }
	  }   
	   x=0;
	   y=0;
  
	}	  
    }
}

void clear()
{
    static u16* VideoMemory = (u16*)0xb8000;
    static u8 x=0, y=0;
    
    for(y=0; y<25; y++)
    {
	     for(x=0; x<80; x++)
	     {
	       VideoMemory[80*y+x] = (VideoMemory[80*y+x]) ;
	       //VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
	     }
	   x=0;
	   y=0;
    }
}

/*
  Constructor for global objects
At this level without the constructor we would run into problems with:
   * Global Ojects
   * Static Objects in classes
   * Composite Objects (Class and Structure Instances)
If we would work with a pointes to those data types we would run into that problem
Becuse pointers are a primitive datatype
*/

//Tl;Dr This constructor allows more complex data types
typedef void (*constructor)(); //define constructor as a pointer to a function
extern "C" constructor start_ctors; //pointer to start_ctors data constructor 
extern "C" constructor end_ctors;  //pointer to end_ctors data constructor

extern "C" void CallConstructors() 
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
     (*i)(); 
}
/*Constructor for global objects*/

//extern "C" -> avoid C++ alternative naming conventions, use C naming conventions
extern "C" void kernelMain(const void* multiboot_structure, u32 magicnumber) //void pointer to accept the multiboot data passed from loader, also accepts the magic number
{
 	GlobalDescriptorTable gdt; //Instanciate Global Descripter Table
 	printf("Testing Interrupt Declaration:\n");
	InterruptManager interr(0x20, &gdt); //Instanciate Interrupts (This is causing errors)
	interr.Activate(); //Actiave Interupt Handling

	//clear(); //commented for INTERRUPT testing, it will be uncomented to test clear()s
	printf("TryOS booted\n");

	
}
