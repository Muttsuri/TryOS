#Compile C++ for 32 bit (-m32)
#Don't use OS's memory management (-fno-use-cxa-atexit)
#No libC (-nostdlib)
#
#No Runtime Type Identification (-fno-rtti)
#No exeption handeling (-fno-exeptions)
#Prevents the naming of the kernel starting with undsersocre, if this was not we would have to call _kernelMain in loader.asm instead of kernelMain
CPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore 

#Compile Assembly for 32bit
ASMPARAMS = --32 

#Target architecture
LDPARAMS = -melf_i386 

objs = loader.o kernel.o

#Make object file for the c++ file, compiled with g++, output for output file ($@) and input from input file ($<)
%.o: %.cpp
		g++ $(CPPPARAMS) -o $@ -c $<

#Make object file from the assemby file, "compiled" with as, output for output file ($@) and input from input file ($<)
%.o: %.asm 
		as $(ASMPARAMS) -o $@  $<

#links the objects $< (input) = linker.ld,  $@ target
trykernel.bin: linker.ld $(objs)
		ld $(LDPARAMS) -T $< -o $@ $(objs)

#coppy kernel to /boot/ (to test)
install: trykernel.bin
		sudo cp $< /boot/trykernel.bin