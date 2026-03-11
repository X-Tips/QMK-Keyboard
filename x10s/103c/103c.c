// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP | AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}
