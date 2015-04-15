# SINOPE OS

This is a simple experimental operating system I created for studying
microkernel based operating systems. Features will be added from time
to time. This is not intended to become anything useful in the future.

In order to compile the system, you are required to use a proper cross
compiling toolchain (gcc, binutils) for one of the supported target
architectures (ix86-elf with x >= 3 only at the moment).

Features included at the moment:
 * well, it boots and prints a message to vga ;)

## Building

In order to build sinope, you have to create a cross compiling
toolchain for a supported target. A script in tools/toolchain may
help you with this.

Copy build.conf.sample to build.conf and edit it to fit your setup.

Type make to start building the kernel.
