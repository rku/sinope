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

#ifndef KERNEL_KPRINTF_H
#define KERNEL_KPRINTF_H 1

#include <stddef.h>
#include <stdarg.h>

void kprintf(const char *format, ...);
void kvprintf(const char *format, va_list ap);

#endif /* KERNEL_KPRINTF_H */
