# Compile for 32bit
# Don't use OS's memory management (-fno-use-cxa-atexit)
# No libC (-nostdlib)
#
# No Runtime Type Identification (-fno-rtti)
# No exeption handeling (-fno-exeptions)
# Prevents the naming of the kernel starting with undsersocre, if this was not we would have to call _kernelMain in loader.asm instead of kernelMain
CPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore

# Compile Assembly for 32bit
ASMPARAMS = --32

# Target architecture
LDPARAMS = -melf_i386 

objs = loader.o gdt.o port.o interruptstubs.o interrupts.o kernel.o

# Make object file for the c++ file, compiled with g++, output for output file ($@) and input from input file ($<)
%.o: %.cpp
	g++ $(CPPPARAMS) -o $@ -c $<

# Make object file from the assemby file, "compiled" with as, output for output file ($@) and input from input file ($<)
%.o: %.s
	as $(ASMPARAMS) -o $@  $<

# links the objects $< (input) = linker.ld,  $@ target
trykernel.bin: linker.ld $(objs)
	ld $(LDPARAMS) -T $< -o $@ $(objs)

#Exists for the purpouse of coding within a Vm an testing with the VM copy kernel to /boot/ (to test)
install: trykernel.bin
	sudo cp $< /boot/trykernel.bin
	rm -fr *.bin *.o
#

# Create a bootable ISO image.
TryOS.iso: trykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "TryOS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/trykernel.bin ' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -fr iso *.bin *.o

