# Constant Declaration

.set MAGIC, 0x1BADB002 # Word MAGIC is replaced at compile time for the value 0x1BADB002 which is a "magic" number 
                       # For it is the number that the bootloader will be searching for to identify the kernel
                       # declared at the multiboot specification -> https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields

.set ALIGN, 1<<0   			# Align the loaded modules in relation with the page boundaries
.set MEMINFO, 1<<1 			# provides memory map
.set FLAGS, ALIGN | MEMINFO   		# Flags for the bootloader 
.set CHECKSUM, -(MAGIC + FLAGS) 	# Prove that this program is the kernel

# Constant Declaration End.

# Multiboot header

.section .multiboot 	# declares the multiboot header for the bootloader to recognise the program as a kernel
    .align 4  		# Forces the position of header
    .long MAGIC
    .long FLAGS
    .long CHECKSUM
    
# Multiboot header End.


# Stack Space Alocation
# NOTE: Stack pointer register -> %esp, seting up the pointer is up to the OS (This linker is part of the OS)

.section .bss 		# stack of the OS for the stack location and pointer is not defined by the bootloader
    .align 16 		# stack on x86 (32bit) must bue 16-byte aligned acording to the System V ABI standart (System V is a unix system), falure to comply with this standard could lead to unexpected behaviour
    stack_bottom: 	# start stack symbol the bottom of the stack
    .skip 16384 	# space of 16KiB
    stack_top:		# end stack symbol the top of the stack

  # Stack is defined from bottom to top becasue in ELF type executables like this kernel
  # The stack grown upwards.

# Stack Space Alocation End
    
#### STOPED HERE ####

.section .text
.extern kernelMain 		# tell assembler that there will be a function named kernelMain (assmebler just assumes kernel is there with this)
.extern CallConstructors 	# Tell assembler that there is a function named CallConstructors
.global loader 			# program entery pointer

loader:
    mov $stack_top, %esp 	# atribute the value of %esp to the pointer of the kernel fucntion
				# this kernel stack pointer should be far for the kernel so it does
				# not ovveride the kernel

    push %eax 		# multiboot RAM size data locaiton pointer pass as argument to kernel. The data is created by the bootloader
    push %ebx 		# magic number that the bootloader copies to %ebx, pass the magic number as an argument for the kernel
    call kernelMain 	# calls the kernel itself

_stop:		# infinite loop in case kernel stops
    cli
    hlt
    jmp _stop