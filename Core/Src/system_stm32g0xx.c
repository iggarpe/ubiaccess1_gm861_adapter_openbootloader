/**
  ******************************************************************************
  * @file    system_stm32g0xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32g0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the HSI (8 MHz then 16 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32g0xx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                    | HSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 16000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 16000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        HSI Division factor                    | 1
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 1
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_R                                  | 2
  *-----------------------------------------------------------------------------
  *        Require 48MHz for RNG                  | Disabled
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018-2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32g0xx_system
  * @{
  */

/** @addtogroup STM32G0xx_System_Private_Includes
  * @{
  */

#include "stm32g0xx.h"

#if !defined  (HSE_VALUE)
#define HSE_VALUE    (8000000UL)    /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE  (16000000UL)   /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE   (32000UL)     /*!< Value of LSI in Hz*/
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE  (32768UL)      /*!< Value of LSE in Hz*/
#endif /* LSE_VALUE */

/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_Defines
  * @{
  */

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0U /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x100. */
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_Variables
  * @{
  */
/* The SystemCoreClock variable is updated in three ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) by calling HAL API function HAL_RCC_GetHCLKFreq()
    3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
       Note: If you use this function to configure the system clock; then there
             is no need to call the 2 first functions listed above, since SystemCoreClock
             variable is updated automatically.
*/
uint32_t SystemCoreClock = 16000000UL;

const uint32_t AHBPrescTable[16UL] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL, 6UL, 7UL, 8UL, 9UL};
const uint32_t APBPrescTable[8UL] =  {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32G0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

#define WATCHDOG_TIMEOUT 10
#define BOOTFLAG_REG TAMP->BKP4R
#define BOOTFLAG_BLDR (('B' << 0) | ('O' << 8) | ('O' << 16) | ('T' << 24))
#define BOOTFLAG_MAIN (('M' << 0) | ('A' << 8) | ('I' << 16) | ('N' << 24))

extern const uint32_t g_pfnVectors[];
extern const uint32_t __main_start[];

void SystemInit(void)
{
  /* Configure the Vector Table location to the actual .isr_vector address ----*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = (uint32_t)&g_pfnVectors;     /* Vector Table set to linker-placed address in FLASH */
#endif

  /* Enable watchdog right away */
  IWDG->KR = IWDG_KEY_ENABLE;
  IWDG->KR = IWDG_KEY_WRITE_ACCESS_ENABLE;
  IWDG->PR = IWDG_PRESCALER_256;
  IWDG->RLR = (WATCHDOG_TIMEOUT * LSI_VALUE) / 256 - 1;
  while (IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU | IWDG_SR_WVU));
  IWDG->KR = IWDG_KEY_RELOAD;

#if 0
  /* Read reset cause and reset flags */
  uint32_t reset_cause = RCC->CSR;
  RCC->CSR |= RCC_CSR_RMVF;

  /* Example: store or branch based on reset_cause if needed */
  /*
    if (reset_cause & RCC_CSR_LPWRRSTF) { // Low-power reset }
    if (reset_cause & RCC_CSR_WWDGRSTF) { // Window watchdog reset }
    if (reset_cause & RCC_CSR_IWDGRSTF) { // Independent watchdog reset }
    if (reset_cause & RCC_CSR_SFTRSTF)  { // Software reset }
    if (reset_cause & RCC_CSR_PORRSTF)  { // POR/PDR reset }
    if (reset_cause & RCC_CSR_PINRSTF)  { // NRST pin reset }
    if (reset_cause & RCC_CSR_OBLRSTF)  { // Option byte loader reset }
    if (reset_cause & RCC_CSR_FWRSTF)   { // Firewall reset }
  */
#endif

  /* Enable clocks to power and RTC */
  RCC->APBENR1 |= RCC_APBENR1_PWREN | RCC_APBENR1_RTCAPBEN;

  /* If reset was from bootloader jump to main application */
  if (BOOTFLAG_REG == BOOTFLAG_BLDR) {

    /* Disable write protection, set new state and reenable it */
    PWR->CR1 |= PWR_CR1_DBP;
    BOOTFLAG_REG= BOOTFLAG_MAIN;
    PWR->CR1 &= ~PWR_CR1_DBP;

    /* Jump to main application */
    const uint32_t sp  = __main_start[0];
    const uint32_t pc  = __main_start[1];

    __set_MSP(sp);
    ((void (*)(void))pc)();
  }

  /* Disable write protection, set new state and reenable it */
  PWR->CR1 |= PWR_CR1_DBP;
  BOOTFLAG_REG = BOOTFLAG_BLDR;
  PWR->CR1 &= ~PWR_CR1_DBP;
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**) / HSI division factor
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is LSI, SystemCoreClock will contain the LSI_VALUE
  *
  *           - If SYSCLK source is LSE, SystemCoreClock will contain the LSE_VALUE
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(***)
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (**) HSI_VALUE is a constant defined in stm32g0xx_hal_conf.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32g0xx_hal_conf.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp;
  uint32_t pllvco;
  uint32_t pllr;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t hsidiv;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_CFGR_SWS_0:                /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;

    case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* LSI used as system clock */
      SystemCoreClock = LSI_VALUE;
      break;

    case RCC_CFGR_SWS_2:                /* LSE used as system clock */
      SystemCoreClock = LSE_VALUE;
      break;

    case RCC_CFGR_SWS_1:  /* PLL used as system clock */
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLR
         */
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
      pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1UL;

      if (pllsource == 0x03UL)          /* HSE used as PLL clock source */
      {
        pllvco = (HSE_VALUE / pllm);
      }
      else                              /* HSI used as PLL clock source */
      {
        pllvco = (HSI_VALUE / pllm);
      }
      pllvco = pllvco * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos);
      pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1UL);

      SystemCoreClock = pllvco / pllr;
      break;

    case 0x00000000U:                   /* HSI used as system clock */
    default:                            /* HSI used as system clock */
      hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos));
      SystemCoreClock = (HSI_VALUE / hsidiv);
      break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
