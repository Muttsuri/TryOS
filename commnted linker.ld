ENTRY(loader) /*entery point of the program*/
OUTPUT_FORMAT(elf32-i386) /*32bit ELF type executable*/
OUTPUT_ARCH(i386:i386) /*32bit output*/

SECTIONS.
{
    . =0x0100000; //defines the output pointer to 0x100000

    .text : /*code of the program goes here*/
    {
        *(.multiboot)
        *(.text*)
        *(.rodata)
    }
    .data :
    {
        start_ctors =.; /*allow initaisation of global variables, Pointer of where it starts (this is known to other .o files)*/
        KEEP(*(.init_array )); /*data constructors*/
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.*))) //data constructors*/
        end_ctors =.; /*end seting of global variables, Pointer of where it ends (this is known to other .o files)*/

        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
     /DISCARD/ : 
    {
        *(.fini_array*)
        *(.comment) /*tell it to ignore comments*/
    }
}
