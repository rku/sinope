# Makefile for the sinope operating system
# See README for detailed information on how to build sinope.

include build.config

.PHONY: kernel iso qemu-run clean

# build sinope
sinope: kernel

# build the kernel
kernel:
	make -C $(ROOTDIR)/kernel

install: install-kernel

install-kernel: kernel
	make -C $(ROOTDIR)/kernel install

# generate iso (requires xorriso)
iso: $(ISOFILE)

$(ISOFILE): sinope install
	mkdir -p $(BUILDDIR)/iso/boot/grub
	cp $(BUILDDIR)/sysroot/boot/$(KERNEL_FILE) $(BUILDDIR)/iso/boot/kernel
	cp misc/iso/grub.cfg $(BUILDDIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISOFILE) $(BUILDDIR)/iso

# run in qemu
qemu-run: iso
	$(QEMU) -cdrom $(ISOFILE)

# clean up source tree
clean:
	rm -rf $(BUILDDIR)
	rm -rf $(ISOFILE)
