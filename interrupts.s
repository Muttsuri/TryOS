 .set IRQ_BASE, 0x20

.section .text
	/*_ZN16 = u16 || InteruptHandler (class) || 15 (id) || handleInterrupt (function) || Ehm (has parameters) */
.extern _ZN16InterruptManager15HandleInterruptEhm 

.global _ZN16InterruptHandler22IgnoreInterruptRequestEv


.macro HandleException num
		/*He said it should be 19 but he worte 16*/
.global _ZN16InterruptManager16HandleInterruptRequest\num\()Ev # define to the outside the jump lable
	# _ZN16InterruptManager22handleInterruptRequestEv -> Alternative Auto defined by C++
_ZN16InterruptManager16HandleInterruptRequest\num\()Ev:
	movb $\num, (interruptnumber)
.endm

/*For exeptions*/
.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev # define to the outside the jump lable
	# _ZN16InterruptManager22handleInterruptRequestEv -> Alternative Auto defined by C++
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptnumber)
.endm

/*Implementation of Interrupt Handlers*/
HandleInterruptRequest 0x00 # Timer
HandleInterruptRequest 0x01 # Keyboard
/*More Interrupts would be added here*/


int_bottom: # interrupt code
	
	/*Push/Save registers to stack*/
	pusha # push all registers
	pushl %ds # push data segments
	pushl %es 
	pushl %fs
	pushl %gs
	/*Registers Stored*/
	
	
push %esp	
push (interruptnumber)	
call _ZN16InterruptHandler15handleInterruptEhm # call function	
# addl $5, %esp -> this would clean the stack pointer, but as the fucntion returns the stack pointer itselft there is no point in doing this	
movl %eax, %esp # Instead we do this
	
	
	/*Return/Load registers from stack*/	
	popl %gs	
	popl %fs
	popl %es	
	popl %ds
	
	popa	
	/*Registers Loded*/
	
_ZN16InterruptHandler22IgnoreInterruptRequestEv:
	
iret # return CPU to normal operation -> done with handeling the interrupt

.data
	interruptnumber: .byte 0