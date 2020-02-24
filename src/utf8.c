#include <stddef.h>

char *utf8_prevchr(const char *p)
{
    if (!p) {
        return NULL;
    }

    while ((*p & 0xC0) == 0x80) {
        p--;
    }
    return p;
}

char *utf8_nextchr(const char *p)
{
    if (!p) {
        return NULL;
    }
    unsigned char cp = *p;
    if (cp < 0x80) {
        return (char *)(p + 1);
    } else if (cp >= 0xF0) {
        return (char *)(p + 4);
    } else if (cp >= 0xE0) {
        return (char *)(p + 3);
    } else {
        return (char *)(p + 2);
    }
}

size_t utf8_strlen(const char *str)
{
    if (!str) {
        return NULL;
    }

    size_t len = 0;
    while (*str) {
        str = utf8_nextchr(str);
        len++;
    }
    return len;
}
