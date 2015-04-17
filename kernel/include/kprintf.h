#ifndef KERNEL_KPRINTF_H
#define KERNEL_KPRINTF_H 1

#include <stddef.h>
#include <stdarg.h>

void kprintf(const char *format, ...);
void kvprintf(const char *format, va_list ap);

#endif /* KERNEL_KPRINTF_H */
