#ifndef _ZYP_ZYPHTINE_H
#define _ZYP_ZYPHTINE_H

#include <stdint.h>

/**
 * Charactor data in preedit buffer
 */
struct preedit_char {
    /** @brief Zhuyin syllable of the charactor
        If this field is zero, it means that the selected charactor
        is not a Chinese charactor. */
    uint16_t zhuyin_syll;
    /** @brief The currently selected charactor */
    uint32_t selected_char;
    /** @brief The charactor is selected by user
        @todo The content is still undefined in current development process */
    uint8_t user_selected;
    /** @brief Flag of segmentor
        @todo The content is still undefined in current development process */
    uint8_t seg_point;
};

/**
 * @brief The main context object in this library
 * @todo The context is not completed
 */
struct zyphtine_ctx {

};

#endif
