/**
  @page OpenBootloader Open Bootloader IAP application
 
  @verbatim
  ******************************************************************************
  * @file    OpenBootloader/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the consumer example.
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
  @endverbatim

@par Application Description

This application exploits OpenBootloader Middleware to demonstrate how to develop an IAP application
and how use it.

Porting note:
- This project originated from the STM32CubeG0 OpenBootloader example for STM32G0C1.
- It has been ported to target STM32G031G8 (STM32G031xx).

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 64 MHz.

Then, these protocols and memories interfaces are configured
  - USART1
  - FLASH interface
  - Option bytes interface
  - Engi bytes interface
  - OTP interface
  - System memory interface

Then, the OpenBootloader application will wait for incoming communication on one of the supported protocols.

Once a communication is established through one of the supported protocols,
the OpenBootloader application will wait for commands sent by the host.

@note In case of Mass Erase operation, the OpenBootloader FLASH area must be protected otherwise the OpenBootloader
      will be erased.

@par Keywords

OpenBootloader, USART, FDCAN, I2C, USB

@par Directory contents
     - Core/Src/main.c                                    Main program file
     - Core/Src/stm32g0xx_hal_msp.c                       MSP Initialization file
     - Core/Src/stm32g0xx_it.c                            Interrupt handlers file
     - Core/Src/system_stm32g0xx.c                        STM32G0xx system clock configuration file
     - Core/Inc/main.h                                    Main program header file
     - Core/Inc/stm32g0xx_hal_conf.h                      HAL Library Configuration file
     - Core/Inc/stm32g0xx_it.h                            Interrupt handlers header file
     - OpenBootloader/App/app_openbootloader.c            OpenBootloader application entry point
     - OpenBootloader/App/app_openbootloader.h            Header for OpenBootloader application entry file
     - OpenBootloader/Target/common_interface.c           Contains common functions used by different interfaces
     - OpenBootloader/Target/common_interface.h           Header for common functions file
     - OpenBootloader/Target/engibytes_interface.c        Contains ENGI Bytes interface
     - OpenBootloader/Target/engibytes_interface.h        Header of ENGI Bytes interface file
     - OpenBootloader/Target/flash_interface.c            Contains FLASH interface
     - OpenBootloader/Target/flash_interface.h            Header of FLASH interface file
     
     - OpenBootloader/Target/interfaces_conf.h            Contains Interfaces configuration
     - OpenBootloader/Target/iwdg_interface.c             Contains IWDG interface
     - OpenBootloader/Target/iwdg_interface.h             Header of IWDG interface file
     - OpenBootloader/Target/openbootloader_conf.h        Header file that contains OpenBootloader HW dependent configuration
     - OpenBootloader/Target/optionbytes_interface.c      Contains OptionBytes interface
     - OpenBootloader/Target/optionbytes_interface.h      Header of OptionBytes interface file
     - OpenBootloader/Target/otp_interface.c              Contains OTP interface
     - OpenBootloader/Target/otp_interface.h              Header of OTP interface file
     - OpenBootloader/Target/platform.h	                  Header for patterns
     
     - OpenBootloader/Target/systemmemory_interface.c     Contains system memory interface
     - OpenBootloader/Target/systemmemory_interface.h     Header of system memory interface file
     - OpenBootloader/Target/usart_interface.c            Contains USART interface
     - OpenBootloader/Target/usart_interface.h            Header of USART interface file
     

@par Hardware and Software environment

  - This project targets STM32G031G8Ux (STM32G031xx) devices.

  - USART set-up:
    - To use the USART1 for communication you have to connect:
      - Tx pin of your host adapter to PA10
      - Rx pin of your host adapter to PA9

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
 - Run STM32CubeProgrammer (or stm32flash) and connect to OpenBootloader using USART1


 */
