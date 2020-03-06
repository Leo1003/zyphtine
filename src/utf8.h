#ifndef _ZYP_UTF8_H
#define _ZYP_UTF8_H
/**
 * @file
 * Provide functions for UTF-8 encoded strings
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Return the string length in charactors
 *
 * @param str valid UTF-8 string
 * @return total charactors in the string
 */
size_t utf8_strlen(const char *str);

/**
 * Return the size in bytes of the first charactor
 * @note if the next charactor is `NUL` (null charactor),
 * this function would return 0!
 *
 * @param str valid UTF-8 string
 * @return size in bytes
 */
static inline size_t utf8_nextchrsize(const char *str)
{
    unsigned char cp = *str;
    if (cp == '\0') {
        return 0;
    }
    if (cp < 0x80) {
        return 1;
    } else if (cp >= 0xF0) {
        return 4;
    } else if (cp >= 0xE0) {
        return 3;
    } else {
        return 2;
    }
}

/**
 * Return the size in bytes in the given `[start, end)` charactor range
 *
 * @param str valid UTF-8 string
 * @param start the start position in charactors
 * @param end the end position in charactors
 * @return total bytes in the range
 */
size_t utf8_rangesize(const char *str, size_t start, size_t end);

/**
 * Copy the provided string, but for a given number of charactors
 * @note The buffer should have at least `4 * len + 1` bytes
 *
 * @param dest buffer to be filled
 * @param src valid UTF-8 string to be copied
 * @param len number of charactors to be copied
 * @return copy destination
 */
char *utf8_strncpy(char *dest, const char *src, size_t len);

/**
 * Get the position of the previous charactor in the string
 *
 * @param p a valid and non-first position in UTF-8 string
 * @return position to the previous charactor
 */
char *utf8_prevchr(const char *p);

/**
 * Get the position of the next charactor in the string
 *
 * @param p a valid position in UTF-8 string
 * @return position to the next charactor
 */
char *utf8_nextchr(const char *p);

/**
 * Get the position of the nth charactor in the string
 *
 * @param p a valid position in UTF-8 string
 * @return position to the next charactor
 */
char *utf8_nthchr(const char *p, size_t n);

/**
 * Copy a substring of the given string in the `[start, end)` range bound
 *
 * @param str valid UTF-8 string
 * @return copied substring
 * @note The returned string is allocated, should call `free()` on it to
 * release the resource.
 */
char *utf8_substr(const char *str, size_t start, size_t end);

/**
 * Reverse the charactors in the string
 *
 * @param str valid UTF-8 string
 * @return the allocated reversed string
 * @note The returned string is allocated, should call `free()` on it to
 * release the resource.
 */
char *utf8_reverse(char *str);

/**
 * Validate the given sequence to check if it is a valid UTF-8 string
 *
 * @param str a bytes sequence to be verified
 * @return if all the bytes are valid UTF-8 sequence
 */
bool utf8_check(const char *str);

/**
 * Check and replace invalid charactors with `�(U+FFFD)`. If the string is valid,
 * it will return a copy of it.
 *
 * @param str a bytes sequence to be verified
 * @return The corrected UTF-8 string
 * @note The returned string is allocated, should call `free()` on it to
 * release the resource.
 */
char *utf8_correct(const char *str);

/**
 * Get the UTF-8 charactor(4 bytes) of the current position
 *
 * @param str pointer to a valid position in UTF-8 string
 * @return UTF-8 charactor
 */
uint32_t utf8_getchr(const char *str);

/**
 * Get the size of the UTF-8 charactor
 * @todo unimplemented
 *
 * @param chr A UTF-8 charactor
 * @return size in bytes of the charactor
 */
size_t utf8_chrsize(uint32_t chr);

#endif
