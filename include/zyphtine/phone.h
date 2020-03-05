#ifndef ZYP_PHONE_H
#define ZYP_PHONE_H

/**
 *  @file
 *  This header file define the bopomofo symbol used in this library,
 *  and some related function
 */

#include <stdint.h>

#define ZYP_BOPOMOFO_B      ((uint16_t)1 << 9)  ///< ㄅ
#define ZYP_BOPOMOFO_P      ((uint16_t)2 << 9)  ///< ㄆ
#define ZYP_BOPOMOFO_M      ((uint16_t)3 << 9)  ///< ㄇ
#define ZYP_BOPOMOFO_F      ((uint16_t)4 << 9)  ///< ㄈ
#define ZYP_BOPOMOFO_D      ((uint16_t)5 << 9)  ///< ㄉ
#define ZYP_BOPOMOFO_T      ((uint16_t)6 << 9)  ///< ㄊ
#define ZYP_BOPOMOFO_N      ((uint16_t)7 << 9)  ///< ㄋ
#define ZYP_BOPOMOFO_L      ((uint16_t)8 << 9)  ///< ㄌ
#define ZYP_BOPOMOFO_G      ((uint16_t)9 << 9)  ///< ㄍ
#define ZYP_BOPOMOFO_K      ((uint16_t)10 << 9) ///< ㄎ
#define ZYP_BOPOMOFO_H      ((uint16_t)11 << 9) ///< ㄏ
#define ZYP_BOPOMOFO_J      ((uint16_t)12 << 9) ///< ㄐ
#define ZYP_BOPOMOFO_Q      ((uint16_t)13 << 9) ///< ㄑ
#define ZYP_BOPOMOFO_X      ((uint16_t)14 << 9) ///< ㄒ
#define ZYP_BOPOMOFO_ZH     ((uint16_t)15 << 9) ///< ㄓ
#define ZYP_BOPOMOFO_CH     ((uint16_t)16 << 9) ///< ㄔ
#define ZYP_BOPOMOFO_SH     ((uint16_t)17 << 9) ///< ㄕ
#define ZYP_BOPOMOFO_R      ((uint16_t)18 << 9) ///< ㄖ
#define ZYP_BOPOMOFO_Z      ((uint16_t)19 << 9) ///< ㄗ
#define ZYP_BOPOMOFO_C      ((uint16_t)20 << 9) ///< ㄘ
#define ZYP_BOPOMOFO_S      ((uint16_t)21 << 9) ///< ㄙ

#define ZYP_BOPOMOFO_I      ((uint16_t)1 << 7)  ///< ㄧ
#define ZYP_BOPOMOFO_U      ((uint16_t)2 << 7)  ///< ㄨ
#define ZYP_BOPOMOFO_YU     ((uint16_t)3 << 7)  ///< ㄩ

#define ZYP_BOPOMOFO_A      ((uint16_t)1 << 3)  ///< ㄚ
#define ZYP_BOPOMOFO_O      ((uint16_t)2 << 3)  ///< ㄛ
#define ZYP_BOPOMOFO_E      ((uint16_t)3 << 3)  ///< ㄜ
#define ZYP_BOPOMOFO_EH     ((uint16_t)4 << 3)  ///< ㄝ
#define ZYP_BOPOMOFO_AI     ((uint16_t)5 << 3)  ///< ㄞ
#define ZYP_BOPOMOFO_EI     ((uint16_t)6 << 3)  ///< ㄟ
#define ZYP_BOPOMOFO_AU     ((uint16_t)7 << 3)  ///< ㄠ
#define ZYP_BOPOMOFO_OU     ((uint16_t)8 << 3)  ///< ㄡ
#define ZYP_BOPOMOFO_AN     ((uint16_t)9 << 3)  ///< ㄢ
#define ZYP_BOPOMOFO_EN     ((uint16_t)10 << 3) ///< ㄣ
#define ZYP_BOPOMOFO_ANG    ((uint16_t)11 << 3) ///< ㄤ
#define ZYP_BOPOMOFO_ENG    ((uint16_t)12 << 3) ///< ㄥ
#define ZYP_BOPOMOFO_ER     ((uint16_t)13 << 3) ///< ㄦ

#define ZYP_TONE_1          ((uint16_t)1)       ///< ˉ
#define ZYP_TONE_2          ((uint16_t)2)       ///< ˊ
#define ZYP_TONE_3          ((uint16_t)3)       ///< ˇ
#define ZYP_TONE_4          ((uint16_t)4)       ///< ˋ
#define ZYP_TONE_5          ((uint16_t)5)       ///< ˙

#endif
