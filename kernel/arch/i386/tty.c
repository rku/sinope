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

#include <stddef.h>
#include <stdint.h>

#include <vga.h>

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_clear(void);
void tty_putc_xy(char, uint8_t, size_t, size_t);

void tty_init(void)
{
    tty_row = 0;
    tty_column = 0;
    tty_color = 15; /* white on black for now */
    tty_buffer = VGA_MEMORY;

    tty_clear();
}

void tty_clear(void)
{
    size_t x, y;

    for(y = 0; y < VGA_HEIGHT; y++) {
        for(x = 0; x < VGA_WIDTH; x++) {
            tty_putc_xy(' ', tty_color, x, y);
        }
    }
}

inline void tty_putc_xy(char c, uint8_t color, size_t x, size_t y)
{
    tty_buffer[y * VGA_WIDTH + x] = c | color << 8;
}

void tty_putc(char c)
{
    tty_putc_xy(c, tty_color, tty_column, tty_row);

    if(++tty_column == VGA_WIDTH) {
        tty_column = 0;

        if(++tty_row == VGA_HEIGHT) {
            tty_row = 0;
        }
    }
}

void tty_write(const char *data, size_t size)
{
    size_t i;

    for(i = 0; i < size; ++i) {
        tty_putc(data[i]);
    }
}
