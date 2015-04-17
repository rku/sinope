# sinope kernel Makefile

include ../build.config

ARCHDIR:=arch/$(ARCH)

include $(ARCHDIR)/make.config
include lib/make.config

CFLAGS+=-ffreestanding -fbuiltin -Wall -Wextra -I$(ROOTDIR) -Iinclude/
CFLAGS+=$(KERNEL_ARCH_CFLAGS)
LDFLAGS+=$(KERNEL_ARCH_LDFLAGS)
LIBS+=-nostdlib -lgcc
LIBS+=$(KERNEL_ARCH_LIBS)

OBJS:=\
	$(KERNEL_ARCH_OBJS) \
	$(KERNEL_LIB_OBJS) \
	kernel/start.o

kernel: $(BUILDDIR)/kernel/$(KERNEL_FILE)

$(BUILDDIR)/kernel/$(KERNEL_FILE): $(OBJS) $(ARCHDIR)/linker.ld
	mkdir -p $(BUILDDIR)/kernel
	$(CC) -T $(ARCHDIR)/linker.ld -o $(BUILDDIR)/kernel/$(KERNEL_FILE) $(CFLAGS) \
		$(addprefix $(BUILDDIR)/kernel/,$(OBJS)) $(LDFLAGS) $(LIBS)

%.o: %.c
	mkdir -p $(BUILDDIR)/kernel/$(shell dirname $@)
	$(CC) -c $< -o $(BUILDDIR)/kernel/$@ -std=gnu11 $(CFLAGS)

%.o: %.S
	mkdir -p $(BUILDDIR)/kernel/$(shell dirname $@)
	$(CC) -c $< -o $(BUILDDIR)/kernel/$@ $(CFLAGS)

clean:
	rm -f $(BUILDDIR)/kernel/$(KERNEL_FILE)
	rm -f $(addprefix $(BUILDDIR)/kernel/, $(OBJS))

install: install-headers install-kernel

install-headers:
	mkdir -p $(SYSROOTDIR)$(INCLUDEDIR)
	cp -RTv include $(SYSROOTDIR)$(INCLUDEDIR)

install-kernel: $(BUILDDIR)/kernel/$(KERNEL_FILE)
	mkdir -p $(SYSROOTDIR)$(BOOTDIR)
	cp $(BUILDDIR)/kernel/$(KERNEL_FILE) $(SYSROOTDIR)$(BOOTDIR)
