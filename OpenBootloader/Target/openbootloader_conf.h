/**
  ******************************************************************************
  * @file    openbootloader_conf.h
  * @author  MCD Application Team
  * @brief   Contains Open Bootloader configuration
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
#ifndef OPENBOOTLOADER_CONF_H
#define OPENBOOTLOADER_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* -------------------------------- Device ID ------------------------------- */
/* STM32G031xx is 0x0466 according to the reference manual */
#define DEVICE_ID_MSB                     0x04              /* MSB byte of device ID */
#define DEVICE_ID_LSB                     0x66              /* LSB byte of device ID */

/* -------------------------- Definitions for Memories ---------------------- */
extern const uint8_t __main_start;
extern const uint8_t __main_end;

#define FLASH_START_ADDRESS               ((uint32_t)&__main_start)
#define FLASH_END_ADDRESS                 ((uint32_t)&__main_end)

#define OB_START_ADDRESS                  0x1FFF7800U       /* Option bytes registers address */
#define OB_END_ADDRESS                    0x1FFF787FU       /* Option bytes end address (128 bytes) */

#define OTP_START_ADDRESS                 0x1FFF7000U       /* OTP registers address */
#define OTP_END_ADDRESS                   0x1FFF73FFU       /* OTP end address (1024 bytes) */

#define ICP1_START_ADDRESS                0x1FFF0000U       /* System memory registers address */
#define ICP1_END_ADDRESS                  0x1FFF1FFFU       /* System memory registers end address */

#define EB_START_ADDRESS                  0x1FFF7500U       /* Engi bytes start address */
#define EB_END_ADDRESS                    0x1FFF77FFU       /* Engi bytes end address  */

#define RDP_LEVEL_0                       OB_RDP_LEVEL_0
#define RDP_LEVEL_1                       OB_RDP_LEVEL_1
#define RDP_LEVEL_2                       OB_RDP_LEVEL_2

#define AREA_ERROR                        0x0U              /* Error Address Area */
#define FLASH_AREA                        0x1U              /* Flash Address Area */
#define RAM_AREA                          0x2U              /* RAM Address area */
#define OB_AREA                           0x3U              /* Option bytes Address area */
#define OTP_AREA                          0x4U              /* OTP Address area */
#define ICP1_AREA                         0x5U              /* System memory area */
#define EB_AREA                           0x7U              /* Engi bytes Address area */

#define FLASH_MASS_ERASE                  0xFFFF
#define FLASH_BANK1_ERASE                 0xFFFE
#define FLASH_BANK2_ERASE                 0xFFFD

#define INTERFACES_SUPPORTED              1U

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* OPENBOOTLOADER_CONF_H */
