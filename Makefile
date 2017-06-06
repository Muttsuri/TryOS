CPPPARAMS = -m32 #Compile C++ for 32 bit

ASMPARAMS = --32 #Compile Assembly for 32bit

LDPARAMS = -melf_i386 #Target architecture

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
