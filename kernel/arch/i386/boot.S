#
# sinope
# Copyright (c) 2015 René Küttner <rene@spaceshore.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Create the multiboot header.
.set MAGIC, 0x1BADB002
.set FLAGS, 1 | 1<<1    # align and request memory map
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long -(MAGIC + FLAGS)  # checksum must satisfy MAGIC+FLAGS+CHECKSUM=0

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    call kernel_early
    call kernel_main

    # Halt if the kernel returns.
    cli
    hlt
.eternity:
    jmp .eternity

.size _start, . - _start
