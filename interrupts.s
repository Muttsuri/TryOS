 .set IRQ_BASE, 0x20

.section .text
	/*_ZN16 = u16 || InteruptHandler (class) || 15 (id) || HandleInterrupt (function) || Ehm (has parameters) */
.extern _ZN16InterruptManager15HandleInterruptEmm 

# .global _ZN16InterruptHandler22IgnoreInterruptRequestEv -> declaed and called bellow, uncesessary ?



/*Handler code*/
.macro HandleException num
		/*He said it should be 19 but he worte 16*/
.global _ZN16InterruptManager19HandleInterruptRequest\num\()Ev # define to the outside the jump lable
	# _ZN16InterruptManager22handleInterruptRequestEv -> Alternative Auto defined by C++
	/*_ZN16 = u16 | InterruptManager (class) | 16 (id) | HandleInterruptRequest (function) | \num\ sends number as paramenter | ()Ev (no parameters) */

_ZN16InterruptManager19HandleInterruptRequest\num\()Ev: # code of the fucntion
	movb $\num, (interruptnumber)
	jmp int_bottom
.endm


/*For exeptions*/
.macro HandleInterruptRequest num
.global _ZN16InterruptManager27HandleInterruptRequest\num\()Ev # define to the outside the jump lable
	# _ZN16InterruptManager22handleInterruptRequestEv -> Alternative Auto defined by C++
	/*_ZN16 = u16 | InterruptManager (class) | 25 (id) | HandleInterruptRequest (function) | \num\ sends number as paramenter | ()Ev (no parameters) */
	
_ZN16InterruptManager27HandleInterruptRequest\num\()Ev: # code of the fucntion
	movb $\num + IRQ_BASE, (interruptnumber)
	jmp int_bottom
.endm
/*Handler code*/



/*Implementation of Interrupt Handlers declared @ interrupts.h*/
HandleInterruptRequest 0x00 # Timer
HandleInterruptRequest 0x01 # Keyboard
/*Implementation of Interrupt Handlers declared @ interrupts.h*/



/* This int_bottom jumps to the interrupt handler Function */
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
call _ZN16InterruptHandler15handleInterruptEmm # call function
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
.global _ZN16InterruptHandler22IgnoreInterruptRequestEv
_ZN16InterruptHandler22IgnoreInterruptRequestEv:

iret # return CPU to normal operation -> done with handeling the interrupt


/*Initialise the variable interruptnumber as 0*/
.data
	interruptnumber: .byte 0