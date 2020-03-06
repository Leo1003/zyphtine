#include <zyphtine/syllable.h>
#include "utf8.h"

#include <stddef.h>

static const char *const INITIAL_BOPOMOFOS =
    "\xE3\x84\x85\xE3\x84\x86\xE3\x84\x87\xE3\x84\x88"  // ㄅㄆㄇㄈ
    "\xE3\x84\x89\xE3\x84\x8A\xE3\x84\x8B\xE3\x84\x8C"  // ㄉㄊㄋㄌ
    "\xE3\x84\x8D\xE3\x84\x8E\xE3\x84\x8F"              // ㄍㄎㄏ
    "\xE3\x84\x90\xE3\x84\x91\xE3\x84\x92"              // ㄐㄑㄒ
    "\xE3\x84\x93\xE3\x84\x94\xE3\x84\x95\xE3\x84\x96"  // ㄓㄔㄕㄖ
    "\xE3\x84\x97\xE3\x84\x98\xE3\x84\x99";             // ㄗㄘㄙ

static const char *const MEDIAL_BOPOMOFOS =
    "\xE3\x84\xA7\xE3\x84\xA8\xE3\x84\xA9";             // ㄧㄨㄩ

static const char *const RHYME_BOPOMOFOS =
    "\xE3\x84\x9A\xE3\x84\x9B\xE3\x84\x9C\xE3\x84\x9D"  // ㄚㄛㄜㄝ
    "\xE3\x84\x9E\xE3\x84\x9F\xE3\x84\xA0\xE3\x84\xA1"  // ㄞㄟㄠㄡ
    "\xE3\x84\xA2\xE3\x84\xA3\xE3\x84\xA4\xE3\x84\xA5"  // ㄢㄣㄤㄥ
    "\xE3\x84\xA6";                                     // ㄦ

static const char *const TONE_BOPOMOFOS =
    "\xCB\x89\xCB\x99\xCB\x8A\xCB\x87\xCB\x8B";         // ˉˊˇˋ˙

bool zyp_syllable_check(uint16_t syll)
{
    return !(syll & 0xC000)
        && (ZYP_SYLLABLE_INITIAL(syll) <= ZYP_BOPOMOFO_S)
        && (ZYP_SYLLABLE_MEDIAL(syll) <= ZYP_BOPOMOFO_YU)
        && (ZYP_SYLLABLE_RHYME(syll) <= ZYP_BOPOMOFO_ER)
        && (ZYP_SYLLABLE_TONE(syll) <= ZYP_TONE_5)
        ;
}

bool zyp_syllable_is_single(uint16_t syll)
{
    return zyp_syllable_is_initials(syll)
        || zyp_syllable_is_medials(syll)
        || zyp_syllable_is_rhymes(syll)
        || zyp_syllable_is_tones(syll)
        ;
}

bool zyp_syllable_is_initials(uint16_t syll)
{
    return (ZYP_SYLLABLE_INITIAL(syll))
        && !(ZYP_SYLLABLE_MEDIAL(syll))
        && !(ZYP_SYLLABLE_RHYME(syll))
        && !(ZYP_SYLLABLE_TONE(syll))
        ;
}

bool zyp_syllable_is_medials(uint16_t syll)
{
    return !(ZYP_SYLLABLE_INITIAL(syll))
        && (ZYP_SYLLABLE_MEDIAL(syll))
        && !(ZYP_SYLLABLE_RHYME(syll))
        && !(ZYP_SYLLABLE_TONE(syll))
        ;
}

bool zyp_syllable_is_rhymes(uint16_t syll)
{
    return !(ZYP_SYLLABLE_INITIAL(syll))
        && !(ZYP_SYLLABLE_MEDIAL(syll))
        && (ZYP_SYLLABLE_RHYME(syll))
        && !(ZYP_SYLLABLE_TONE(syll))
        ;
}

bool zyp_syllable_is_tones(uint16_t syll)
{
    return !(ZYP_SYLLABLE_INITIAL(syll))
        && !(ZYP_SYLLABLE_MEDIAL(syll))
        && !(ZYP_SYLLABLE_RHYME(syll))
        && (ZYP_SYLLABLE_TONE(syll))
        ;
}

char *zyp_syllable_print(char *dest, uint16_t syll)
{
    if (!zyp_syllable_check(syll)) {
        return NULL;
    }

    char *s = dest;
    uint16_t init, med, rhy, tone;
    if ((init = ZYP_SYLLABLE_INITIAL(syll))) {
        init = (init >> 9) - 1;
        const char *chr = utf8_nthchr(INITIAL_BOPOMOFOS, init);
        utf8_strncpy(s, chr, 1);
        s = utf8_nextchr(s);
    }

    if ((med = ZYP_SYLLABLE_MEDIAL(syll))) {
        med = (med >> 7) - 1;
        const char *chr = utf8_nthchr(MEDIAL_BOPOMOFOS, med);
        utf8_strncpy(s, chr, 1);
        s = utf8_nextchr(s);
    }

    if ((rhy = ZYP_SYLLABLE_RHYME(syll))) {
        rhy = (rhy >> 3) - 1;
        const char *chr = utf8_nthchr(RHYME_BOPOMOFOS, rhy);
        utf8_strncpy(s, chr, 1);
        s = utf8_nextchr(s);
    }

    if ((tone = ZYP_SYLLABLE_TONE(syll))) {
        tone = tone - 1;
        const char *chr = utf8_nthchr(TONE_BOPOMOFOS, tone);
        utf8_strncpy(s, chr, 1);
        s = utf8_nextchr(s);
    }

    return dest;
}
