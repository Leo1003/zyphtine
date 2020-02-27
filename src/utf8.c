#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "utf8.h"

#define BITMASK_EQU(b, mask, exp) ((b & mask) == exp)
#define UTF8_IS_CONTIN(b) (BITMASK_EQU(b, 0xC0, 0x80))
#define UTF8_REPLACEMENT "\xEF\xBF\xBD"

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

char *utf8_reverse(char *str)
{
    if (!str) {
        return NULL;
    }

    size_t sz = strlen(str);
    char *buf = (char *)malloc(sz + 1);
    if (!buf) {
        return NULL;
    }

    char *p = buf + sz;
    const char *s = str;
    while (*s) {
        size_t chrsz = utf8_nextchrsize(s);
        p -= chrsz;
        memcpy(p, s, chrsz);
        s = utf8_nextchr(s);
    }
    buf[sz] = '\0';

    return buf;
}

// Following RFC 3629 -- Section 4
static inline int utf8_check_nextchar(const unsigned char *s)
{
    if (BITMASK_EQU(*s, 0x80, 0x00)) {
        /* UTF8-1 (0xxxxxxx) */
        return 1;
    } else if (BITMASK_EQU(*s, 0xE0, 0xC0)) {
        /* UTF8-2 (110xxxxx) */
        if (BITMASK_EQU(*s, 0xFE, 0xC0)) {
            /* Overlong encoding (1100000x) */
            return 0;
        } else {
            return 2;
        }
    } else if (BITMASK_EQU(*s, 0xF0, 0xE0)) {
        /* UTF8-3 (1110xxxx) */
        if (*s == 0xE0) {
            /* (101xxxxx) */
            if (!BITMASK_EQU(*(s + 1), 0xE0, 0xA0)) {
                /* Overlong encoding / Invalid continuation byte */
                return 0;
            }
        } else if (*s == 0xED) {
            /* (100xxxxx) */
            if (!BITMASK_EQU(*(s + 1), 0xE0, 0x80)) {
                /* Surrogates / Invalid continuation byte */
                return 0;
            }
        } else {
            if (!UTF8_IS_CONTIN(*(s + 1))) {
                /* Invalid continuation byte */
                return 0;
            }
        }
        if (!UTF8_IS_CONTIN(*(s + 2))) {
            /* Invalid continuation byte */
            return 0;
        }
        return 3;
    } else if (BITMASK_EQU(*s, 0xF8, 0xF0)) {
        /* UTF8-4 (11110xxx) */
        if (*s < 0xF5) {
            if (*s == 0xF0) {
                if (!UTF8_IS_CONTIN(*(s + 1))) {
                    /* Invalid continuation byte */
                    return 0;
                }
                if (*(s + 1) < 0x90) {
                    /* Overlong encoding */
                    return 0;
                }
            } else if (*s == 0xF4) {
                if (!BITMASK_EQU(*(s + 1), 0xF0, 0x80)) {
                    /* Out of range / Invalid continuation byte */
                    return 0;
                }
            } else {
                if (!UTF8_IS_CONTIN(*(s + 1))) {
                    /* Invalid continuation byte */
                    return 0;
                }
            }
            if (!UTF8_IS_CONTIN(*(s + 2))) {
                /* Invalid continuation byte */
                return 0;
            }
            if (!UTF8_IS_CONTIN(*(s + 3))) {
                /* Invalid continuation byte */
                return 0;
            }
            return 4;
        } else {
            /* Out of range */
            return 0;
        }
    }
}

bool utf8_check(const char *str)
{
    if (!str) {
        return false;
    }

    const char *s = str;
    while (*s) {
        int offset = utf8_check_nextchar(s);
        if (!offset) {
            return false;
        }
        s += offset;
    }
    return true;
}
