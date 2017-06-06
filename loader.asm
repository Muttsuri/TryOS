.set MAGIC, 0x1dabd002 # Word MAGIC is replaced at compile time for the value 0x1dadb002 which is a "magic" number
                       # For it is the number that the bootloader will be searching for to identify the kernel

.set FLAGS, (1<<0 | 1<<1) # Flags for the bootloader
.set CHECKSUM, -(MAGIC + FLAGS) # Confirm if everything is ok

.section .multiboot # contains the variables that are created by the bootloader on the bootloader struct
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain # tell assembler that there will be a function named kernelMain (assmebler just assumes kernel is there with this)
.global loader # program entery pointer

loader:
    mov $kernel_stack, %esp # atribute the value of %esp to the pointer of the kernelfucntion
                            # this kernel stack pointer should be far for the kernel so it does
                            # not ovveride the kernel
    
    push %eax # multiiboot RAM size data locaiton pointer pass as argument to kernel. The data is created by the bootloader
    push %ebx # magic number that the bootloader copies to %ebx, pass the magic number as an argument for the kernel
    call kernelMain # calls the kernel itself

_stop:             # infinite loop in case kernel stops
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024 # 2Mb empty padding
kernel_stack:
