/**
  ******************************************************************************
  * @file    interfaces_conf.h
  * @author  MCD Application Team
  * @brief   Contains Interfaces configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INTERFACES_CONF_H
#define INTERFACES_CONF_H

#define MEMORIES_SUPPORTED                7U

/* ------------------------- Definitions for USART -------------------------- */

#define USARTx                            USART1

#define USARTx_TX_PIN                     GPIO_PIN_6
#define USARTx_TX_GPIO_PORT               GPIOB
#define USARTx_TX_ALTERNATE               GPIO_AF0_USART1

#define USARTx_RX_PIN                     GPIO_PIN_7
#define USARTx_RX_GPIO_PORT               GPIOB
#define USARTx_RX_ALTERNATE               GPIO_AF0_USART1

#define USARTx_DE_PIN                     GPIO_PIN_3
#define USARTx_DE_GPIO_PORT               GPIOB
#define USARTx_DE_ALTERNATE               GPIO_AF4_USART1

#define USARTx_CLK_ENABLE() do {  \
  __HAL_RCC_USART1_CLK_ENABLE();  \
  __HAL_RCC_GPIOB_CLK_ENABLE();   \
} while (0)

#endif /* INTERFACES_CONF_H */
