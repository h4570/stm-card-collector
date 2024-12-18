/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "usart.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usb_settings.h"
#include "rc522.h"
#include "FatFs/ff.h"
#include "usbd_msc_scsi.h"
#include <stdlib.h>

// ================ PORADNIK
// https://www.youtube.com/watch?v=Us_sTdGGcOQ&ab_channel=ControllersTech
// ================

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t str[MAX_LEN]; // Max_LEN = 16
uint8_t sNum[MAX_LEN];
char tagString[8];

FATFS fs;
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void MountAndFormatDisk()
{
  BYTE work[4096];    // Bufor roboczy dla f_mkfs
  MKFS_PARM mkfs_opt; // Opcje formatowania

  // Montowanie systemu plików
  FRESULT fr = f_mount(&fs, "RAM", 0); // Montowanie systemu plików
  if (fr != FR_OK)
  {
    // Obsługa błędów
  }

  // Konfiguracja opcji formatowania
  mkfs_opt.fmt = FM_FAT; // Wybierz format FAT
  mkfs_opt.au_size = 0;  // Automatyczny rozmiar jednostki alokacji

  // Sformatowanie dysku
  fr = f_mkfs("RAM", &mkfs_opt, work, sizeof(work));
  if (fr != FR_OK)
  {
    // Obsługa błędów
  }

  // Odinstalowanie systemu plików
  f_unmount("RAM");
}

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_USB_Device_Init();
  MX_SPI2_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  MountAndFormatDisk();
  MFRC522_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // uint8_t reg = 0x37;
    // uint8_t version;
    // uint8_t address = ((reg << 1) & 0x7E) | 0x80; // MSB = 1 for reading, address is 7 bits

    // HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_RESET); // Assert CS (if using GPIO for NSS)

    // HAL_SPI_Transmit(&hspi2, &address, 1, 50);
    // HAL_SPI_Receive(&hspi2, &version, 1, 50);

    // HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_SET); // De-assert CS

    // if (version != 0)
    // {
    //   int i = 1;
    // }

    // ---

    uint8_t status1 = MFRC522_Request(PICC_REQIDL, str);

    uint8_t status2 = MFRC522_Anticoll(str);

    memcpy(sNum, str, 16);
    HAL_Delay(100);

    if (status2 == MI_OK)
    {
      itoa(sNum[0], tagString, 16);
      itoa(sNum[1], &tagString[1 * 2], 16);
      itoa(sNum[2], &tagString[2 * 2], 16);
      itoa(sNum[3], &tagString[3 * 2], 16);
      int x = 1;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief NVIC Configuration.
 * @retval None
 */
static void MX_NVIC_Init(void)
{
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* USER CODE BEGIN 4 */

// void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
// {
//   // Callback dla zakończenia transmisji przez SPI
// }

// void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
// {
//   // Callback dla zakończenia odbioru przez SPI
// }

// void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
// {
//   // Callback dla zakończenia transmisji i odbioru przez SPI
// }

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == B1_Pin)
  {
    FRESULT fr = f_mount(&fs, "RAM", 0); // Montowanie systemu plików

    FIL fil; // Obiekt pliku
    UINT bw; // Licznik zapisanych bajtów

    fr = f_open(&fil, "com.dat", FA_OPEN_APPEND | FA_WRITE);
    if (fr == FR_OK)
    {
      fr = f_write(&fil, "ABCDEFGH", 9 - 1, &bw); // Zapis "A" do pliku
      fr = f_sync(&fil);                          // Synchronizacja danych na dysku
      fr = f_close(&fil);                         // Zamknięcie pliku
    }

    f_unmount("RAM");

    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    SCSI_ProcessCmd(&hUsbDeviceFS, 0, SCSI_TEST_UNIT_READY);
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

#ifdef USE_FULL_ASSERT
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
