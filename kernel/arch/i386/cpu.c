/**
 *  sinope
 *  Copyright (c) 2015 René Küttner <rene@spaceshore.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <kernel/cpu.h>
#include <kernel/klog.h>

struct _cpu_info {
    char vendor_id[12];
    unsigned int ncores;
};
static struct _cpu_info cpu_info;

/**
 * Call cpuid and return the content of related registers (eax, ebc, ecx,
 * edx). Arguments to cpuid must be passed via the eax or ecx flags.
 */
static inline void __cpuid(unsigned int *eax, unsigned int *ebx,
        unsigned int *ecx, unsigned int *edx)
{
    __asm__ volatile(
            "cpuid"
            :
            "=a" (*eax),
            "=b" (*ebx),
            "=c" (*ecx),
            "=d" (*edx)
            :
            "0"  (*eax),
            "2"  (*ecx)
            :
            "memory"
        );
}

/**
 * Check for the availability of cpuid. Returns 0 if cpuid is not
 * available or 1 if it is available.
 */
unsigned int __has_cpuid(void)
{
    __asm__ goto (
            "pushf\n\t"
            "pop %%eax\n\t"
            "mov %%eax, %%ebx\n\t"
            "xor $0x200000, %%eax\n\t"
            "push %%eax\n\t"
            "popf\n\t"
            "pushf\n\t"
            "pop %%eax\n\t"
            "cmp %%ebx, %%eax\n\t"
            "jnz %l0\n\t"
            : /* no output */
            : /* no input */
            : /* no clobbers */
            : __cpuid_found
        );

    return 0;
__cpuid_found:
    return 1;
}

void __cpu_get_info(void)
{
    unsigned int eax, *eaxp, *ebxp, ecx, *ecxp, *edxp; 

    /* vendor id */
    ebxp = (unsigned int*)&(cpu_info.vendor_id);
    edxp = (unsigned int*)&(cpu_info.vendor_id[4]);
    ecxp = (unsigned int*)&(cpu_info.vendor_id[8]);
    eax = *ecxp = 0;
    __cpuid(&eax, ebxp, ecxp, edxp);

    /* number of cores */
    cpu_info.ncores = eax;
}

void cpu_init(void)
{
    if(__has_cpuid()) {
        klog("CPUID available");
    }

    __cpu_get_info();
    klog("Found %i cores", cpu_info.ncores);
}
