void printf(char* str) //we have to code a printf becuase as we are building an os we have no linker to add the library stdio.h which has the printf function.
{
    unsigned short* VideoMemory = (unsigned short*)0xb8000; //video memory starts at 0xb8000
    for(int i = 0; str[i] !='\0'; i++)
    {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i]; //This copies to video memory the value each character in the string
                                                             //but it also copies the high byte of the video memory so that the characters remain white
                                                             //this is the default of the video memory
                                                             //after copying the high byte it combines it with the character to make the white charctet
                                                             //high byte defines the colour of the character and the second defines the value to be presented.
    }
}
//extern "C" -> avoid C++ alternative naming conventions, use C naming conventions
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber) //void pointer to accept the multiboot data passed from loader, also accepts the magic number
{
    printf("I have booted");
    
    while (1); //prevent kernel from stoping
}