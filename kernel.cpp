void printf(char* str) //we have to code a printf becuase as we are building an os we have no linker to add the library stdio.h which has the printf function.
{
    (unsigned short*) VideoMemory = (unsigned short*)0xb8000;
    for(int i = 0; str[i] !='\0'; i++)
    {
        VideoMemory[i] = str[i];
    }
}

void kernelMain(void* multiboot_structure, unsigned int magicnumber) //void pointer to accept the multiboot data passed from loader, also accepts the magic number
{
    printf("I have booted");


    while (1); //prevent kernel from stoping
}