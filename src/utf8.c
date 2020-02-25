#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "utf8.h"

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
    return (char *)(p + utf8_nextchrsize(p));
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

size_t utf8_rangesize(const char *str, size_t start, size_t end)
{
    if (!str || (start > end)) {
        return 0;
    }

    size_t sz = 0, len = end - start;
    for (size_t i = 0; i < start; i++) {
        str = utf8_nextchr(str);
    }
    for (size_t i = 0; i < len; i++) {
        sz += utf8_nextchrsize(str);
        str = utf8_nextchr(str);
    }
    return sz;
}

char *utf8_strncpy(char *dest, const char *src, size_t len)
{
    if (!src || !dest) {
        return NULL;
    }

    size_t sz = utf8_rangesize(src, 0, len);
    strncpy(dest, src, sz);
    dest[sz] = '\0';
    return dest;
}

char *utf8_substr(const char *str, size_t start, size_t end)
{
    if (!str || (start > end)) {
        return NULL;
    }

    size_t sz = utf8_rangesize(str, start, end);
    char *buf = (char *)malloc(sz + 1);
    if (!buf) {
        return NULL;
    }

    for (size_t i = 0; i < start; i++) {
        str = utf8_nextchr(str);
    }
    strncpy(buf, str, sz);
    buf[sz] = '\0';
    return buf;
}