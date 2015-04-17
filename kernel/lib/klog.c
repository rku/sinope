
#include <stdarg.h>

#include <kernel/klog.h>
#include <kernel/kprintf.h>
#include <kernel/tty.h>

/**
 * At the moment, the log is simply a printf to the console with a
 * timestamp prepended.
 */
void klog(const char *msg, ...)
{
    unsigned int timestamp = -123;
    va_list ap;

    kprintf("[%x] ", timestamp);

    va_start(ap, msg);
    kvprintf(msg, ap);
    va_end(ap);

    tty_putc('\n');
}
