void printf(char* str) //we have to code a printf becuase as we are building an os we have no linker to add the library stdio.h which has the printf function.
{
    unsigned short* VideoMemory = (unsigned short*)0xb8000; //video memory starts at 0xb8000
    for(int i = 0; str[i] !='\0'; i++)
    {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i]; /*This copies to video memory the value each character in the string
                                                               but it also copies the high byte of the video memory so that the characters remain white
                                                               this is the default of the video memory
                                                               after copying the high byte it combines it with the character to make the white charctet
                                                               high byte defines the colour of the character and the second defines the value to be presented.*/
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
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber) //void pointer to accept the multiboot data passed from loader, also accepts the magic number
{
    printf("I have booted");
    
    while (1); //prevent kernel from stoping
}