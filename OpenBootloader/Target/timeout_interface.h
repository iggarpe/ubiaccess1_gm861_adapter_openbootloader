/**
  ******************************************************************************
  * @file    timeout_interface.h
  * @brief   Bootloader inactivity timeout using TIM14
  ******************************************************************************
  */

#ifndef TIMEOUT_INTERFACE_H
#define TIMEOUT_INTERFACE_H

/* Configure inactivity timeout in milliseconds */
#ifndef OPENBL_INACTIVITY_TIMEOUT_MS
#define OPENBL_INACTIVITY_TIMEOUT_MS 10000U
#endif

/* Exported functions ------------------------------------------------------- */
void OPENBL_TIMEOUT_Init(void);
void OPENBL_TIMEOUT_Restart(void);

#endif /* TIMEOUT_INTERFACE_H */


