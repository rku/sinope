
#include <kernel/string.h>

size_t strlen(const char *s)
{
    size_t len = 0;

    while (*s++) ++len;

    return len;
}

char *strchr(const char *s, int c)
{
    char *p = (char*)s;

    for (; *p && *p != c; ++p);

    if (!*p) {
        return NULL;
    }

    return p;
}
