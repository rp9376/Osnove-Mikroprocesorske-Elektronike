/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/*
 * Ta pojekt je clone vaje ko smo implementirali tipkvnico
 * To je bilo storjeno ker DMA USART ni sodeloval na kasnejših verzijah
 * Ostale komponente so bile implementirane naknadno
 *
 *Velik problem je bla UART komunikacija a se je reslo z uporabo HAL DMA UART za RX in UART_it za TX
 *
 * Funkcija printf pošilja na izhod uart3 (blocking mode) (_write)
 *
 * Vem da ni prov da je cela aplikacija narjena v main.c in v while a jebi ga
 * Sem opazu da bi blo mogoče fino kje uporablat avtomate ampak sem si sprot zmislevou delovanje kode in je blo ze prepozn (ne grem se enkrat pisat)
 *
 * Je nekej programerskih grehov ampak sej zdej sm stromar in si to lah prvosim
 *
 * lp in lep pozdrav RP
 */




/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "LED.h"
#include "kbd.h"
#include "buf.h"
// nismo uporabili SCI
#include "timing_utils.h"
#include "periodic_services.h"
#include "lcd_backlight.h"
#include "lcd.h"
#include "joystick.h"

#include <stdio.h> //za printf

#include "HC05.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define DEBUG_MODE 1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc4;
DMA_HandleTypeDef hdma_adc4;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart3_rx;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM4_Init(void);
static void MX_FMC_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC4_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */



void MouseMode();
void MusicMode();
void KeyboardMode();



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


//RX bufferji
#define BTBuf_SIZE 50
uint8_t BTBuf[BTBuf_SIZE];

#define CONBuf_SIZE 50
uint8_t CONBuf[CONBuf_SIZE];

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) 	//UART DMA RX handler
{
	/*
	 * Note:: Kar se pošilja na Miškov UART bo bilo s to funkcijo posredovano
	 * 		  BT modulu, to se lahko odpravi z popravkom te funkcije ampak je implementirano
	 * 		  za namene hitrega debagiranja in ker ne moti samega programa pri delovanju
	 *
	 * 		  Ugotovitev: Ta zadeva dela velik bols ko na arduinu (Software serial je trash)
	 *
	 */
	if(huart->Instance == USART1) 											// RX iz BT
		{
			HAL_UART_Transmit_IT(&huart3, BTBuf, Size); 					//pošle kar sprejme iz BT na Con

			HAL_UARTEx_ReceiveToIdle_DMA(&huart1, BTBuf, BTBuf_SIZE);		//ponovno vklopi DMA za uart
			__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT); 				//izklopi interupt Half transfer
		}

	if(huart->Instance == USART3) 										// RX iz console
	{
#if DEBUG_MODE == 1
		HAL_UART_Transmit_IT(&huart3, CONBuf, Size); 					//echo (za testirat zadeve)
#endif
		HAL_UART_Transmit_IT(&huart1, CONBuf, Size); 					//Posle prejeto iz konzole na BT

		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, CONBuf, CONBuf_SIZE);		//ponovno vklopi DMA za uart
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT); 				//izklopi interupt Half transfer
	}
}

int _write(int file, char *ptr, int len)		//Za printf (standard output redirection)
{
	// Vhodna argumenta _write funkcije "*ptr" in "len" specificirata,
	// kje se nahajajo podatki, ki jih printf() funkcija želi poslati
	// ter kako dolgi so ti podatki (v smislu števila bajtov).


	HAL_UART_Transmit(&huart3, (uint8_t*) ptr, (uint16_t) len, 1);

	// Funkcija _write() mora vrniti število uspešno poslanih
	// znakov. Tu poenostavimo in privzamemo, da je bilo uspešno
	// poslanih vseh "len" znakov.
	return len;
}

/////////////	MOJE SPREMENLJIVKE	//////////////////////
uint8_t Mode = 0; //0 = Disconnected  1 = Mouse  2 = Keyboard  3 = Music
uint8_t OldMode = 5; //Nekej kar ni nic
//uint8_t TextUpdateFlag = 1;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  //////////	SPREMENLJIVKE	/////////////
    uint8_t Connected = 0; 	//če je HC05 povezan z upravljano napravo = 1 //spremenljivka se bo passala naprej kot pointer


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_FMC_Init();
  MX_SPI1_Init();
  MX_ADC4_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //Inicializacija sistemskih modulov
  LED_init();
  KBD_init();
  PSERV_init();
  PSERV_enable(); 	//Zažene periodic services (branje tipkovnice)
  LCD_Init(); 		//Vsebuje tudi init za backlight
  LCD_uGUI_init();
  JOY_init(&hadc4, &htim1);

  BT_init(&huart1, &huart3, &Connected);

  setvbuf(stdout, NULL, _IONBF, 0);


//Znaki da je miško pričel s kodo
  LEDs_on(0b10101010);
  HAL_Delay(50);
  LEDs_off(LEDs_read());
  LEDs_on(0b01010101);
  HAL_Delay(50);
  LEDs_off(LEDs_read());
  LEDs_on(0b10101010);
  HAL_Delay(50);
  LEDs_write(0);


  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, BTBuf, BTBuf_SIZE); 	//Vklop DMA za UART1 RX
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);				//Izklop interuta HalfTransfer

  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, CONBuf, CONBuf_SIZE);	//Vklop DMA za UART3 RX
  __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);				//Izklop interuta HalfTransfer

#if DEBUG_MODE == 1
  HAL_UART_Transmit_IT(&huart3, (uint8_t*) "Im alive\n", 9);
#endif


  //Priprava zaslona
 LCD_uGUI_demo_Misko3();
 UG_SetForecolor(C_WHITE);
 UG_FontSelect(&FONT_16X26);
 UG_PutString(7, 90,"__________________");
 UG_FontSelect(&FONT_10X16);
 UG_PutString(295, 3,":)");




 	 while (1)
 	 {
 		 //Joystisk button to Connect or Disconnect
 		 if(JOY_get_pressed_key() == JOY_BTN_FIRE)		//Ali je JOY gumb pritisnjen
 		 {
 			if(Connected == 0)						//Ali je BT povezan ali ne
 			{BT_Connect();}
 			else
 			{BT_Disconnect();}
 		 }

 		if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7)) //Preverja povezanost BT modula z napravo
 		{
 			if(Mode == 0)		//To se zgodi ob prehodu iz Mode 0 na Mode 1
 			{
 				LED_on(7);			//LED 7 se prizge ko je BT povezan
 				Connected = 1;		//Postavi Connected flag da lahko ostale funkcije vidijo ali je BT povezan
 				Mode = 1;
 			}

 		}else
 		{
 			 if(Mode != 0)		//To se zgodi na pregodu na Mode 0
 			 {
 				 LED_off(7);			//LED 7 se ugasne ko je BT povezan
 				  Connected = 0;		//Postavi Connected flag da lahko ostale funkcije vidijo ali je BT povezan
 				  Mode = 0;
 			 }
 		}

	 switch(Mode)		//Mode handler
	 {
		 case 1:	//Mouse mode
			 if(OldMode != Mode)				//To se zgodi ob spremembi modov (1x prvi cikel moda)
			 {
				 KBD_flush();
				 UG_FillFrame( 0, 120, 320, 240, C_BLACK); 	//Blackout working portion
				 UG_FontSelect(&FONT_10X16);
				 UG_PutString(25, 130,"MODE: Mouse Mode");
				 UG_FontSelect(&FONT_6X8);
				 UG_PutString(15, 160,"Joystick: Move cursor");
				 UG_PutString(15, 180,"Buttons: ^ Scroll Up\n         v Scroll Down\n         < Left Click\n         > Right Click\n        OK Middle Click");
				 UG_PutString(220, 230,"ESC Next Mode");
				 OldMode = Mode;
			 }
			 MouseMode();
			 break;

		 case 2:
			 if(OldMode != Mode)
			 {
				 KBD_flush();
				 UG_FillFrame( 0, 120, 320, 240, C_BLACK); 	//Blackout working portion
				 UG_FontSelect(&FONT_10X16);
				 UG_PutString(25, 130,"MODE: Keyboard Mode");
				 UG_FontSelect(&FONT_6X8);
				 UG_PutString(15, 160,"Joystick: ^ & v Cycle character");
				 UG_PutString(15, 170,"          < Clear character");
				 UG_PutString(15, 180,"          > Next character / 3x New line");
				 UG_PutString(15, 200,"Buttons: Arrow Keys");
				 UG_PutString(15, 210,"         OK - Capslock");
				 UG_PutString(220, 230,"ESC Next Mode");
				 OldMode = Mode;
			 }
			 KeyboardMode();
			 break;

		 case 3:
			 if(OldMode != Mode)
			 {
				 KBD_flush();
				 UG_FillFrame( 0, 120, 320, 240, C_BLACK); 	//Blackout working portion
				 UG_FontSelect(&FONT_10X16);
				 UG_PutString(25, 130,"MODE: Music control Mode");
				 UG_FontSelect(&FONT_6X8);
				 UG_PutString(15, 160,"Joystick: ^ & v Volume Up/Down");
				 UG_PutString(15, 170,"          < & > Prev/Next Track");
				 UG_PutString(15, 190,"Buttons: ^ Play/Pause");
				 UG_PutString(15, 200,"         v Mute/Unmute");
				 UG_PutString(15, 210,"         < Open browser");
				 UG_PutString(15, 220,"         > Home");
				 UG_PutString(15, 230,"        OK Signature");
				 UG_PutString(220, 230,"ESC Next Mode");

				 OldMode = Mode;
			 }
			 MusicMode();
			 break;

		 case 0:
			 if(OldMode != Mode)
			 {
				 UG_FillFrame( 0, 120, 320, 240, C_BLACK); 	//Blackout working portion
				 UG_FontSelect(&FONT_10X16);
				 UG_PutString(50, 125,"Press Joystick button");
				 UG_PutString(50, 145,"to Connect/Disconnect");
				 UG_PutString(10, 200,"(1st connection is manual)");
				 UG_PutString(10, 220,"Connect to Miska3 Bluetooth");
				 OldMode = Mode;
			 }

			 break;

		 default:

			 break;
	 }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC4_Init(void)
{

  /* USER CODE BEGIN ADC4_Init 0 */

  /* USER CODE END ADC4_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC4_Init 1 */

  /* USER CODE END ADC4_Init 1 */

  /** Common config
  */
  hadc4.Instance = ADC4;
  hadc4.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc4.Init.Resolution = ADC_RESOLUTION_12B;
  hadc4.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc4.Init.GainCompensation = 0;
  hadc4.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc4.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc4.Init.LowPowerAutoWait = DISABLE;
  hadc4.Init.ContinuousConvMode = DISABLE;
  hadc4.Init.NbrOfConversion = 2;
  hadc4.Init.DiscontinuousConvMode = DISABLE;
  hadc4.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T1_TRGO;
  hadc4.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc4.Init.DMAContinuousRequests = ENABLE;
  hadc4.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc4.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC4_Init 2 */

  /* USER CODE END ADC4_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 14399;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 90;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  TIM_InitStruct.Prescaler = 1439;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 99;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM4, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM4);
  LL_TIM_SetClockSource(TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH1);
  LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM4);
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**TIM4 GPIO Configuration
  PB6   ------> TIM4_CH1
  */
  GPIO_InitStruct.Pin = LCD_BKLT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(LCD_BKLT_GPIO_Port, &GPIO_InitStruct);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

  /* TIM6 interrupt Init */
  NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));
  NVIC_EnableIRQ(TIM6_DAC_IRQn);

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  TIM_InitStruct.Prescaler = 143;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 49999;
  LL_TIM_Init(TIM6, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM6);
  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM6);
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FMC_NORSRAM_DEVICE;
  hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
  hsram1.Init.NBLSetupTime = 0;
  hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;
  hsram1.Init.MaxChipSelectPulse = DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 1;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 1;
  Timing.DataHoldTime = 1;
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

  /**/
  LL_GPIO_ResetOutputPin(LED_1_GPIO_Port, LED_1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_2_GPIO_Port, LED_2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_3_GPIO_Port, LED_3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_4_GPIO_Port, LED_4_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_5_GPIO_Port, LED_5_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_6_GPIO_Port, LED_6_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_7_GPIO_Port, LED_7_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_0_GPIO_Port, LED_0_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LCD_RST_GPIO_Port, LCD_RST_Pin);

  /**/
  LL_GPIO_ResetOutputPin(TCH_ChipSelect_GPIO_Port, TCH_ChipSelect_Pin);

  /**/
  GPIO_InitStruct.Pin = JOY_BTN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(JOY_BTN_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_ESC_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_ESC_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_OK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_OK_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = HC_05_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(HC_05_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_4_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_5_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_6_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_6_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_7_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_7_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_0_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_0_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_UP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_UP_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_DOWN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_DOWN_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_LEFT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_LEFT_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BTN_RIGHT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BTN_RIGHT_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TCH_ReqPending_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(TCH_ReqPending_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TCH_ChipSelect_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(TCH_ChipSelect_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void MouseMode()
{
	int8_t MoveX = JOY_get_axis_position(X);
	int8_t MoveY = JOY_get_axis_position(Y);

	MoveX -= 50;				//Joystick ma 4 razločne hitrsti
	MoveX = MoveX / 10;
	MoveX *= 1.6;				//naredi rahlo nelinearnost pri premikanu

	MoveY -= 50;
	MoveY = MoveY / 10;
	MoveY *= -1;
	MoveY *= 1.6;

	static uint8_t update = 0;		//Ko Pošljemo L/D klik ga moremo nato izpustit.. to je nice rešitev da ne upocasnjuje prevec
	static int8_t Wheel = 0;
	static uint8_t Button = 0x00;
	if(Wheel || Button)
	{
		update = 1;
		Wheel = 0;
		Button = 0;
	}



	//Preverja pritisnjenost posameznih tipk na miskotu
	if(KBD_get_button_state(BTN_UP) == BTN_SIG_VALUE_PRESSED)
	{
		Wheel = 1;				//
		//SendKeyCode(0x52);	//Pošlje tipko tipkovnice Arrow up //Lepsi scroll na telefonu
		HAL_Delay(50); 			//Ni uporabno brez delaya.. scrolla prehitr
	}
	if(KBD_get_button_state(BTN_DOWN) == BTN_SIG_VALUE_PRESSED)
	{
		Wheel = -1;
		//SendKeyCode(0x51);	//Pošlje tipko tipkovnice Arrow down	//Lepsi scroll na telefonu
		HAL_Delay(50);			//Ni uporabno brez delaya.. scrolla prehitr
	}
	if(KBD_get_button_state(BTN_LEFT) == BTN_SIG_VALUE_PRESSED)
	{
		Button = BP_MOUSE_BTN_LEFT;			//0x01 == Left click
	}
	if(KBD_get_button_state(BTN_RIGHT) == BTN_SIG_VALUE_PRESSED)
	{
		Button = BP_MOUSE_BTN_RIGHT;			//0x01 == Right click
	}
	if(KBD_get_button_state(BTN_OK) == BTN_SIG_VALUE_PRESSED)
	{
		Button = BP_MOUSE_BTN_MIDDLE;
	}
	if(KBD_get_button_state(BTN_ESC) == BTN_SIG_VALUE_PRESSED)
	{
		Mode = 2; 	//Gumb esc premakne mode na Keyboard mode
	}


	if(MoveX || MoveY || Button || Wheel || update) 		//Preveri ali je sploh potrebno pošiljati premik
	{
		LED_on(0);											//Led 0 Se prižge ko se nekaj pošlje
		MouseMoveClickWheel(MoveX, MoveY, Button, Wheel); 	//Pošlji pakez za miško
		HAL_Delay(8);										//Bluetooth umira če pošiljamo prehitro
		LED_off(0);
		update = 0;
	}
}


void MusicMode()
{
	int8_t JoyposX = JOY_get_axis_position(X);
	int8_t JoyposY = JOY_get_axis_position(Y);
	static uint8_t XisInRange = 0;

	if(JoyposX >= 80 || JoyposX <= 20)	//Pozicija za X
	{
		if(XisInRange == 0)
		{
			//Ko se premaknemo v območje
			LED_on(0);
			if(JoyposX >= 80) //ko je joy na desni
			{
				SendDataByte(0x01, 0x00);	//Scan next track
			}
			else if(JoyposX <= 20)
			{
				SendDataByte(0x02, 0x00);	//Scan prev track
			}
		XisInRange = 1;
		}
	}
	else
	{
		if(XisInRange)
		{
			// ko se premaknemo izven območja
			LED_off(0);
			XisInRange = 0;
		}
	}

	if(JoyposY >= 80)		//Pozicija za Y
	{
		LED_on(0);
		SendDataByte(0x00, 0x10);	//Volume Up
		HAL_Delay(150);		//Da ne gre prehitr volume
		LED_off(0);
	}else if(JoyposY <= 20)	//Pozicija za Y
	{
		LED_on(0);
		SendDataByte(0x00, 0x20);	//Volume Down
		HAL_Delay(150);				//Da ne gre prehitr volume
		LED_off(0);
	}


	buttons_enum_t pressed_key = KBD_get_pressed_key();		//Pregleda gumbe
	switch(pressed_key)
	{
	case BTN_UP:
		SendDataByte(0x00, 0x80);	//Play/pause
		break;
	case BTN_DOWN:
		SendDataByte(0x00, 0x40);	//Mute
		break;
	case BTN_LEFT:
		SendDataByte(0x80, 0x00);	//Open Browser
		break;
	case BTN_RIGHT:
		SendDataByte(0x00, 0x01);	//Home
		break;
	case BTN_OK:
		//SendDataByte(0x04, 0x00);	//Stop music
#define MyDelay 300
		LED_on(0);
		SendString("MiSKa3\n");
		HAL_Delay(MyDelay);
		LED_off(0);
		HAL_Delay(MyDelay);
		LED_on(0);
		SendString("By: Rok Plesko ");
		HAL_Delay(MyDelay);
		LED_off(0);
		HAL_Delay(MyDelay);
		LED_on(0);
		SendString("vss IKT\n");
		HAL_Delay(MyDelay);
		LED_off(0);
		HAL_Delay(MyDelay);
		LED_on(0);
		SendString("FE UNI LJ - 1.7.2022\n");
		HAL_Delay(MyDelay);
		LED_off(0);
		HAL_Delay(MyDelay);
		LED_on(0);
		SendString("main.rokplesko");
		HAL_Delay(MyDelay);
		SendString("@gmail.com\n\n");
		HAL_Delay(MyDelay);
		LED_off(0);
		HAL_Delay(MyDelay);




		break;
	case BTN_ESC:
		Mode = 1;
		break;
	default:
		break;
	}
}


typedef enum{MID, UP, DOWN, LEFT, RIGHT} JoyPos;

char keyTable[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                   'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '9', '8', '7', '6', '5', '4', '3', '2', '1', '0'//, '@', ';', ',', '.'
                  };
uint8_t TableLen = sizeof(keyTable) - 1; //to bi se verjetno lah bols nardil

void KeyboardMode()
{
	int8_t JoyposX = JOY_get_axis_position(X);
	int8_t JoyposY = JOY_get_axis_position(Y);
	static JoyPos CurrentPos = MID;
	static JoyPos OldPos;
	static int8_t tablePos = 0;
	static uint8_t spaceRepet = 1;
	static uint16_t CharsInRow = 0;
	static uint8_t BkSpce = 0;

	OldPos = CurrentPos;

	if(JoyposY <= 20)			//Preverja v katerem ekstremu je joystick
		CurrentPos = DOWN;
	else if(JoyposY >= 80)
		CurrentPos = UP;
	else if(JoyposX >= 80)
		CurrentPos = RIGHT;
	else if(JoyposX <= 20)
		CurrentPos = LEFT;
	else
		CurrentPos = MID;

	if(OldPos != CurrentPos)	//Preverja ali je joystick v novem extremu
	{
		CharsInRow = 0;
	}


	switch(CurrentPos)			//Izvaja kodo posameznega ekstrema
	{
	case UP:
		tablePos --;
		CharsInRow ++;
		if(tablePos <= 0)		//Za primer ko pride do preliva znakov
			tablePos = TableLen;
		if(spaceRepet < 3 || BkSpce)			//V primeru da je bil pred tem poslan Enter ne pobriše tega znaka (Entra)
			SendChar((char) 8);			//Send backspace
		spaceRepet = 0;
		BkSpce = 0;
		SendCharAddr(&keyTable[tablePos]);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		HAL_Delay((250 - (CharsInRow * 30) > 100) ? 250 - (CharsInRow * 30) : 100); 	//To je samo fancy način postopnega zmansevanja
		break;																				//delaya ampak da ima mejo

	case DOWN:						//Joystick dol pobriše trenutni znak in ga zamenja z njegovim naslednikom (iz keyTable)
		tablePos ++;
		CharsInRow ++;
		if(tablePos > TableLen)		//Za primer ko pride do preliva znakov
			tablePos = 1;
		if(spaceRepet < 3 || BkSpce)			//V primeru da je bil pred tem poslan Enter ne pobriše tega znaka (Entra)
			SendChar((char) 8);			//Send backspace
		spaceRepet = 0;
		BkSpce = 0;
		SendCharAddr(&keyTable[tablePos]);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		HAL_Delay((250 - (CharsInRow * 30) > 100) ? 250 - (CharsInRow * 30) : 100); 	//To je samo fancy način postopnega zmansevanja
		break;																				//delaya ampak da ima mejo

	case LEFT:					//Joystick v levo pobrise zadnji znak (lahko se ga tudi zadrzi)
		spaceRepet = 0;
		BkSpce ++;
		CharsInRow ++;
		tablePos = 0;						//Ob pisanju novega znaka se pozicija v tebeli postavi na začetek
		SendKeyCode(0x2a);		//Send backspace
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		HAL_Delay((250 - (CharsInRow * 30) > 50) ? 250 - (CharsInRow * 30) : 50);		//Fancy delay
		break;

	case RIGHT:
		if(OldPos == MID)
		{
			tablePos = 0;						//Ob pisanju novega znaka se pozicija v tebeli postavi na začetek
			spaceRepet ++;						//stetje zaporednih presledkov
			BkSpce = 0;
			if(spaceRepet <= 3)
			{
				SendCharAddr(&keyTable[0]); 	//Pošlje prvi znak ki je 'SPACE'
			}else
			{
				SendChar((char) 13);			//Pošlje CR znak ki se obnaša kot enter
			}
			LED_on(0);
			HAL_Delay(5);
			LED_off(0);
		}
		break;

	case MID:
		break;
	}

	buttons_enum_t pressed_key = KBD_get_pressed_key();		//Pregleda gumbe
	switch(pressed_key)
	{
	case BTN_UP:
		SendKeyCode(0x52);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		break;
	case BTN_DOWN:
		SendKeyCode(0x51);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		break;
	case BTN_LEFT:
		SendKeyCode(0x50);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		break;
	case BTN_RIGHT:
		SendKeyCode(0x4F);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		break;
	case BTN_OK:
		LED_toggle(3);
		LED_toggle(4);
		SendKeyCode(0x39);
		LED_on(0);
		HAL_Delay(5);
		LED_off(0);
		break;
	case BTN_ESC:
		Mode = 3;
	default:
		break;
	}








}








/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
