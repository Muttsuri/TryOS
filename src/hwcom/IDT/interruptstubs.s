.set IRQ_BASE, 0x20

.section .text # main program section


	/*_ZN16 = u16 || InteruptHandler (class) || 15 (id) || HandleInterrupt (function) || Ehm (has parameters) */
.extern _ZN16InterruptManager15HandleInterruptEhm


/*For exeptions*/
.macro HandleException num
.global	_ZN16InterruptManager19HandleException\num\()Ev
	/*_ZN16 = u16 | InterruptManager (class) | 16 (id) | HandleInterruptRequest (function) | \num\ sends number as paramenter | ()Ev (no parameters) */
# _ZN16InterruptManager19HandleInterruptRequest\num\()Ev: # code of the fucntion
_ZN16InterruptManager19HandleException\num\()Ev:
	movb $\num , (interruptNumber)
	jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN16InterruptManager27HandleInterruptResquest\num\()Ev # define to the outside the jump lable
	/*_ZN16 = u16 | InterruptManager (class) | 25 (id) | HandleInterruptRequest (function) | \num\ sends number as paramenter | ()Ev (no parameters) */
	
_ZN16InterruptManager27HandleInterruptResquest\num\()Ev: # code of the fucntion
	movb $\num + IRQ_BASE , (interruptNumber)
	jmp int_bottom
.endm
/*Handler code*/

HandleException 0x00
HandleException 0x01

/*Implementation of Interrupt Handlers declared @ interrupts.h*/
HandleInterruptRequest 0x00 # Timer
HandleInterruptRequest 0x01 # Keyboard
/*Implementation of Interrupt Handlers declared @ interrupts.h*/
/*Handler code*/


/* This int_bottom jumps to the interrupt handler Function */
int_bottom: # interrupt code

	/*Push/Save registers to stack*/
	pusha 		# push all registers
	pushl %ds 	# push data segments
	pushl %es 
	pushl %fs
	pushl %gs
	/*Registers Stored*/
	
	/*Load ring 0 segment registers*/
	# cld
	# mov $0x10, %eax
	# mov %eax, %edx
	# mov %eax, %esp


	push %esp
	push (interruptNumber)
	call _ZN16InterruptManager15HandleInterruptEhm # call function
	add %esp, 6
	# addl $5, %esp -> this would clean the stack pointer, but as the fucntion returns the stack pointer it self there is no point in doing this
	movl %eax, %esp # Instead we do this


	/*Return/Load registers from stack*/	
	popl %gs	
	popl %fs
	popl %es	
	popl %ds
	popa	
	/*Registers Loded*/

/*If the interrupt is to be ignored it will skip the handeling of the interupt*/
.global _ZN16InterruptManager22IgnoreInterruptRequestEv
_ZN16InterruptManager22IgnoreInterruptRequestEv:

iret # return CPU to normal operation -> done with handeling the interrupt


/*Initialise the variable interruptNumber as 0*/
.data
	interruptNumber: .byte 0
