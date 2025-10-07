/**
  ******************************************************************************
  * @file    timeout_interface.c
  * @brief   Bootloader inactivity timeout using TIM14 one-pulse
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "timeout_interface.h"

/* Private variables ---------------------------------------------------------*/
static TIM_HandleTypeDef s_openblTimeoutTim;

/* Private functions ---------------------------------------------------------*/
static void OPENBL_TIMEOUT_MspInit(void)
{
  __HAL_RCC_TIM14_CLK_ENABLE();

  /* TIM14 interrupt Init */
  HAL_NVIC_SetPriority(TIM14_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(TIM14_IRQn);
}

void OPENBL_TIMEOUT_Init(void)
{
  uint32_t timclk_hz;
  uint32_t prescaler;
  uint32_t period;

  OPENBL_TIMEOUT_MspInit();

  /* Compute prescaler and period for ~10s one-pulse at current APB clock */
  /* Choose 1 kHz timer tick (1 ms) for easy ms period computation */
  timclk_hz = HAL_RCC_GetPCLK1Freq();
  if (timclk_hz == 0U)
  {
    timclk_hz = 16000000U;
  }

  prescaler = (timclk_hz / 1000U) - 1U; /* 1 kHz */
  period = OPENBL_INACTIVITY_TIMEOUT_MS - 1U; /* ms */

  s_openblTimeoutTim.Instance = TIM14;
  s_openblTimeoutTim.Init.Prescaler = (uint16_t)prescaler;
  s_openblTimeoutTim.Init.CounterMode = TIM_COUNTERMODE_UP;
  s_openblTimeoutTim.Init.Period = (uint16_t)period;
  s_openblTimeoutTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  s_openblTimeoutTim.Init.RepetitionCounter = 0;
  s_openblTimeoutTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  HAL_TIM_Base_Init(&s_openblTimeoutTim);

  /* One-pulse mode: generate update event once, then stop */
  __HAL_TIM_CLEAR_FLAG(&s_openblTimeoutTim, TIM_FLAG_UPDATE);
  __HAL_TIM_ENABLE_IT(&s_openblTimeoutTim, TIM_IT_UPDATE);

  OPENBL_TIMEOUT_Restart();
}

void OPENBL_TIMEOUT_Restart(void)
{
  HAL_TIM_Base_Stop_IT(&s_openblTimeoutTim);
  __HAL_TIM_SET_COUNTER(&s_openblTimeoutTim, 0);
  __HAL_TIM_CLEAR_FLAG(&s_openblTimeoutTim, TIM_FLAG_UPDATE);
  HAL_TIM_Base_Start_IT(&s_openblTimeoutTim);
}

/* Interrupts & Callbacks -----------------------------------------------------*/

void TIM14_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&s_openblTimeoutTim);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM14)
  {
    /* No activity detected within the configured timeout -> reset MCU */
    NVIC_SystemReset();
  }
}
