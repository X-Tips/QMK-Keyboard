// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define HAL_USE_PWM TRUE
#define HAL_USE_SERIAL TRUE

// 启用 USART 单线模式支持
#define SERIAL_USART_CONFIG_WITH_SINGLE_WIRE TRUE

#include_next <halconf.h>