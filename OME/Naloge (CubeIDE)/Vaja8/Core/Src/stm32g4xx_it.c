/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

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
  * @brief This function handles Prefetch fault, memory access fault.
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
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART3 global interrupt / USART3 wake-up interrupt through EXTI line 28.
  */

///////////	 KODA IZ VAJE 8	 //////////////////////////////////////////////////////////////////////

// -------- Prekinitvam je potrebno dodati sistemsko funkcionalnost SCI vmesnika:

// Znotraj prekinitvene rutine USART3_IRQHandler() moramo biti sposobni poklicati,
// t.i. "callback" funkcije za sprejemanje novega podatka oziroma po??iljanje novega
// podatka preko serijskega vmesnika SCI. Te "callback" funkcije so pravzaprav del sistema,
// ki se odziva na prekinitve na strojnem nivoju. Vidite lahko, da tokrat pa
// ni??je-nivojski strojni nivo (tj. USART enota) potrebuje storitve
// vi??jega sistemskega nivoja (tj. medpomnilnikov SCI vmesnika):
//		- ob sprejemu ??elimo sprejeti podatek shraniti v sistemski SCI RX medpomnilnik
//		- pri po??iljanju podatkov ??elimo podatke jemati iz sistemskega SCI TX medpomnilnika


	// 	DOPOLNI #include ...
#include "stm32g4xx_it.h"

// ----------- Implementirati je potrebno t. i. "IRQ handler" funkcijo za prekinitve v zvezi z USART3 vmesnikom,
// s pomo??jo katerega smo implementirali sistemki serijski vmesnik SCI:


// Funkcija USART3_IRQHandler() se izvede vsaki??, ko se spro??i katerakoli od prekinitev USART3 vmesnika.
// Funkcija USART3_IRQHandler() je torej pravzaprav splo??na prekinitvena rutina USART3 vmesnika.
// Znotraj te splo??ne prekinitvene rutine je potrebno ugotoviti, kateri od specifi??nih prekinitvenih
// dogodkov je spro??il prekinitev. Za nas bosta klju??na prekinitvena dogodka sprejetje novega podatka (RXNE)
// ter sprostitev oddajnega podatkovnega registra (TXE).

void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */


	// Kot ??e re??eno, je potrebno znotraj prekinitvene rutine ugotoviti, kateri od specifi??nih
	// prekinitvenih dogodkov je spro??il globalno USART3 prekinitev in se potem ustrezno odzvati
	// na ta prekinitveni dogodek s "callback funkcijo".

	// Vir prekinitve ugotavljamo s pomo??jo prekinitveno-statusnega registra USART vmesnika
	// ob pomo??i LL funkcij.

	// Nujno pa je tudi, da preden se odzovemo na specifi??ni vir prekinitve, preverimo,
	// ??e je ta specifi??na prekinitev sploh omogo??ena. ??e tega ne bi storili, tvegamo,
	// da se na prekinitveni dogodek odzovemo z napa??no prekinitveno "callback" rutino.


//INTERESTING void LL_USART_SetWKUPType (USART_TypeDef * USARTx, uint32_t Type) Type: This parameter can be one of the following values:	??? LL_USART_WAKEUP_ON_ADDRESS	??? LL_USART_WAKEUP_ON_STARTBIT ??? LL_USART_WAKEUP_ON_RXNE


	// ------ Odzivanje na novo-sprejeti podatek (zastavica RXNE = Receive data register not empty) -------


		// Najprej preverimo, ??e je ta specifi??na prekinitev sploh omogo??ena. Uporabimo LL funkcijo.
		if( LL_USART_IsEnabledIT_RXNE_RXFNE(USART3) )		// sploh omogo??ena prekinitev ob RXNE?
		{
			// ??e je prekinitev omogo??ena, potem preverimo ??e, ??e je postavljena ustrezna zastavica.
			if( LL_USART_IsActiveFlag_RXNE_RXFNE (USART3) )	// postavljena zastavica RXNE?
			{
				// ??e je ta specifi??na prekinitev omogo??ena in ??e je postavljena zastavica tega specifi??nega
				// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.

					// DOPOLNI done
				SCI_receive_char_Callback();

				// V vednost: zastavica RXNE se zbri??e avtomatsko, ko preberemo sprejemni register RDR.
			}
		}




	// ------ Odzivanje na sprostitev oddajnega podatkovnega registra TDR (zastavica TXE = Transmitter Empty) -------

		// Najprej preverimo, ??e je ta specifi??na prekinitev sploh omogo??ena. Uporabimo LL funkcijo.
		if( LL_USART_IsEnabledIT_TXE_TXFNF (USART3) )		// sploh omogo??ena prekinitev ob TXE?
		{
			// ??e je prekinitev omogo??ena, potem preverimo ??e, ??e je postavljena ustrezna zastavica.
			if( LL_USART_IsActiveFlag_TXE_TXFNF(USART3) )		// postavljena zastavica TXE?
			{
				// ??e je ta specifi??na prekinitev omogo??ena in ??e je postavljena zastavica tega specifi??nega
				// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.

					// DOPOLNI done
				SCI_transmit_char_Callback();

				// V vednost: zastavica TXE se zbri??e avtomatsko, ko pi??emo v oddajni podatkovni register TDR.
			}
		}




  /* USER CODE END USART3_IRQn 0 */
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

