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

#include <stdarg.h>

#include <kernel/kprintf.h>
#include <kernel/string.h>
#include <kernel/tty.h>

void __kprintf_print_int(int i, unsigned int base)
{
#define MAX_INT_DIGITS 64
    int pos = 0;
    char buf[MAX_INT_DIGITS];

    if (i == 0) {
        tty_putc('0');
        return;
    }

    if (i < 0) {
        i *= -1;
        tty_putc('-');
    }

    if (base == 16)
        tty_puts("0x");

    if (base == 8)
        tty_puts("0");

    if (base == 0)
        base = 10;

    while (i > 0 && pos < MAX_INT_DIGITS)
    {
        buf[pos++] = i % base;
        i /= base;
    }

    for (--pos; pos >= 0; --pos)
    {
        if (buf[pos] > 9) {
            tty_putc('a' + (buf[pos] % 10));
        } else {
            tty_putc('0' + buf[pos]);
        }
    }
}

void kprintf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    kvprintf(format, ap);
    va_end(ap);
}

void kvprintf(const char *format, va_list ap)
{
    while (*format)
    {
        if (*format == '%')
        {
            ++format;
            switch (*format)
            {
                case '\0':
                    break;
                case '%':
                    tty_putc('%');
                    break;
                case 's':
                    tty_puts(va_arg(ap, char*));
                    break;
                case 'i':
                    __kprintf_print_int(va_arg(ap, int), 10);
                    break;
                case 'x':
                    __kprintf_print_int(va_arg(ap, int), 16);
                    break;
                default:
                    tty_puts("<invalid kprintf format modifier: ");
                    tty_putc(*format);
                    tty_puts(">");
            }
        } else {
            tty_putc(*format);
        }

        ++format;
    }
}
