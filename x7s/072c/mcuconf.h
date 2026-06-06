// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

/* PWM 配置 - 使用 TIM3 */
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

/* USART 配置 - 启用 USART1 */
#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

/* USART1 重映射配置 - 允许使用 PB6/PB7 */
#undef STM32_USART1_USE_ALTERNATE_PINS
#define STM32_USART1_USE_ALTERNATE_PINS TRUE

/* 关闭不需要的外设 */
#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 FALSE

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 FALSE