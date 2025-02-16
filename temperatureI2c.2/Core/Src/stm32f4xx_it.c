/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>	//c standard library for the print function
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
bool provjeraPrvi = false;
bool provjeraDrugi = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim3;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 2 interrupt.
  */
void EXTI2_IRQHandler(void)//prekidna rutina koja se poziva kada se dogodi eksterni prekid na pin 2 (EXTI2)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */
	printf("EXTI2\n"); //Ispisuje "EXTI2" u konzolu za debagiranje, što pomaže u praćenju kada se prekid dogodi
		HAL_NVIC_DisableIRQ(EXTI2_IRQn);
provjeraPrvi = true; //Postavlja varijablu provjeraPrvi na true. Ovo je signalna varijabla koja pokazuje da je prekid EXTI2 obradio nešto važno
		//HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK) // Pali interrupt (Timer kreće proitzvoditi interrupt), interrupt svaku sekundu ispisuje temp neovisno o poslu u glavnoj petlji
	    {
	      /* Starting Error */
	      Error_Handler();//pomaže da precizno mjerimo temp, na taj nacin sam postigao da ne izgubim ni jedno ocitanje temperature
	    }

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(start_Pin); //Poziva se funkcija HAL biblioteke za obradu prekida na start_Pin (koji je povezan s EXTI2). Ovo osigurava da su svi unutarnji zastavice i statusi prekida pravilno obrađeni.
  /* USER CODE BEGIN EXTI2_IRQn 1 */

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void) // prekidna rutina koja se poziva kada se dogodi prekid tajmera TIM2
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2); //  funkcija obrađuje prekid za tajmer TIM2 koristeći HAL biblioteku. Ona upravlja svim potrebnim internim operacijama za tajmer (resetiranje zastavica, pozivanje callback funkcija itd.)
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	printf("TIM3\n"); //Ispisuje "TIM3" za debagiranje, što pomaže u praćenju kada se prekid dogodi
	if (HAL_TIM_Base_Stop_IT(&htim3) != HAL_OK) // Pali interrupt (Timer kreće proitzvoditi interrupt), interrupt svaku sekundu ispisuje temp neovisno o poslu u glavnoj petlji
		    {
		      /* Starting Error */
		      Error_Handler();//pomaže da precizno mjerimo temp, na taj nacin sam postigao da ne izgubim ni jedno ocitanje temperature
		    }
	if(provjeraPrvi && (HAL_GPIO_ReadPin(GPIOB, 2) == GPIO_PIN_RESET)){
		mjerenjeOmoguceno = true;
// Ako je provjeraPrvi postavljen na true i pin GPIOB, pin 2 je u niskom stanju (GPIO_PIN_RESET), omogućava se mjerenje postavljanjem mjerenjeOmoguceno na true i ispisuje "EnableM"
		printf("EnableM\n");
	}
	if(provjeraDrugi && (HAL_GPIO_ReadPin(GPIOB, 10) == GPIO_PIN_RESET)){
			mjerenjeOmoguceno = false;
			s.temperature = 0.0;
					printf("DisableM\n");
// Ako je provjeraDrugi postavljen na true i pin GPIOB, pin 10 je u niskom stanju (GPIO_PIN_RESET), mjerenje se onemogućava postavljanjem mjerenjeOmoguceno na false, postavlja se temperatura na 0.0 i ispisuje "DisableM"
		}
	if(mjerenjeOmoguceno){
		printf("mjerenjeOmoguceno \n");
		HAL_NVIC_ClearPendingIRQ (EXTI15_10_IRQn); //cisti zastavicu i omogucava prekid EXTI15_10
				HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	}else{
		HAL_NVIC_ClearPendingIRQ (EXTI2_IRQn);// cisti zastavicu i omogucava prekid EXTI2
					HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	}
	provjeraPrvi = false;
	provjeraDrugi = false;// postavljane pocetnih stanja
  /* USER CODE END TIM3_IRQn 0 */

  HAL_TIM_IRQHandler(&htim3); // Obradjuje prekid za tajmer TIM3 koristeći HAL biblioteku
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	printf("EXTI10\n");
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); //Onemogućava prekid EXTI15_10 kako bi se spriječilo ponovno izazivanje prekida dok se trenutni prekid obrađuje
	provjeraDrugi = true;
			//HAL_NVIC_EnableIRQ(EXTI2_IRQn);
			if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK) // Pali interrupt (Timer kreće proitzvoditi interrupt), interrupt svaku sekundu ispisuje temp neovisno o poslu u glavnoj petlji
				    {
// Pokreće osnovni tajmer TIM3 s prekidima. Ako pokretanje nije uspješno, poziva Error_Handler() za rješavanje greške
				      /* Starting Error */
				      Error_Handler();//pomaže da precizno mjerimo temp, na taj nacin sam postigao da ne izgubim ni jedno ocitanje temperature
				    }
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(stop_Pin);
  //HAL_GPIO_EXTI_IRQHandler(B1_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}
