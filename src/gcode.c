/* Includes ------------------------------------------------------------------*/
#include "gcode.h"

/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "stm32f2xx_hal.h"
#include "usb_device.h"
#include "config.h"
/* USER CODE END Includes */


 /* USER CODE BEGIN EXPORTED_DEFINES */
#define DF_COMMAND_SIZE	80
 /* USER CODE END EXPORTED_DEFINES */

/* USER CODE BEGIN EXPORTED_VARIABLES */
uint8_t g_uiCommand[DF_COMMAND_SIZE];
/* USER CODE END EXPORTED_VARIABLES */

/* Private function prototypes -----------------------------------------------*/
BOOL SetCurrent(int iAxis, float fCurrent);
/* Private function prototypes -----------------------------------------------*/


void delay_us(const uint16_t us)
{
  uint32_t i = us * 20;
  while (i-- > 0) {
    asm("nop");
  }
}

void gcode_process_line()
{
	// データー取得
	if (CDC_Get_ReadData_FS(g_uiCommand, DF_ARRY_SIZE(g_uiCommand)) == FALSE)
	{
		return;
	}

	if (strcmp(g_uiCommand, "PWM_START") == 0)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		CDC_Transmit_FS("OK");
	}
	else if (strcmp(g_uiCommand, "PWM_STOP") == 0)
	{
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		CDC_Transmit_FS("OK");
	}
	else if (strcmp(g_uiCommand, "CURRENT_X_ON") == 0)
	{
		// X軸電流設定
		if (SetCurrent(0, 1000) == FALSE)
		{
			CDC_Transmit_FS("NG");
		}
		else
		{
			CDC_Transmit_FS("OK");
		}
	}
	else if (strcmp(g_uiCommand, "CURRENT_X_OFF") == 0)
	{
		// X軸電流OFF
		if (SetCurrent(0, 0) == FALSE)
		{
			CDC_Transmit_FS("NG");
		}
		else
		{
			CDC_Transmit_FS("OK");
		}
	}
	else if (strcmp(g_uiCommand, "CURRENT_Y_ON") == 0)
	{
		// Y軸電流設定
		if (SetCurrent(1, 1000) == FALSE)
		{
			CDC_Transmit_FS("NG");
		}
		else
		{
			CDC_Transmit_FS("OK");
		}
	}
	else if (strcmp(g_uiCommand, "CURRENT_Y_OFF") == 0)
	{
		// Y軸電流OFF
		if (SetCurrent(1, 0) == FALSE)
		{
			CDC_Transmit_FS("NG");
		}
		else
		{
			CDC_Transmit_FS("OK");
		}
	}
	else if (strcmp(g_uiCommand, "SENSE_X") == 0)
	{
		if (HAL_GPIO_ReadPin(GPIOA, X_LIMIT_Pin) != GPIO_PIN_RESET)
		{
			CDC_Transmit_FS("OFF");
		}
		else
		{
			CDC_Transmit_FS("ON");
		}
	}
	else if (strcmp(g_uiCommand, "SENSE_Y") == 0)
	{
		if (HAL_GPIO_ReadPin(GPIOA, Y_LIMIT_Pin) != GPIO_PIN_RESET)
		{
			CDC_Transmit_FS("OFF");
		}
		else
		{
			CDC_Transmit_FS("ON");
		}
	}
	else if (strcmp(g_uiCommand, "SENSE_SW") == 0)
	{
		if (HAL_GPIO_ReadPin(GPIOA, D_SWITCH_Pin) != GPIO_PIN_RESET)
		{
			CDC_Transmit_FS("OFF");
		}
		else
		{
			CDC_Transmit_FS("ON");
		}
	}
	else if (strcmp(g_uiCommand, "MOTOR_X") == 0)
	{
		HAL_GPIO_WritePin(GPIOC, X_EN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, X_DIR_Pin, GPIO_PIN_SET);
		for (int i = 0; i < 25000; i++)
		{
			HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_SET);
			delay_us(25);
			HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_RESET);
			delay_us(25);

		}
		HAL_GPIO_WritePin(GPIOC, X_EN_Pin, GPIO_PIN_SET);

		CDC_Transmit_FS("OK");
	}
	else if (strcmp(g_uiCommand, "MOTOR_Y") == 0)
	{
		HAL_GPIO_WritePin(GPIOC, Y_EN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, Y_DIR_Pin, GPIO_PIN_SET);
		for (int i = 0; i < 25000; i++)
		{
			HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_SET);
			delay_us(35);
			HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_RESET);
			delay_us(35);

		}
		HAL_GPIO_WritePin(GPIOC, Y_EN_Pin, GPIO_PIN_SET);

		CDC_Transmit_FS("OK");
	}
	else if (strcmp(g_uiCommand, "MOTOR_TEST") == 0)
	{
		HAL_GPIO_WritePin(GPIOC, X_EN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, Y_EN_Pin, GPIO_PIN_RESET);

		for (int i = 0; i < 200; i++)
		{
			// ----------------------------------------------
			HAL_GPIO_WritePin(GPIOC, X_DIR_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, Y_DIR_Pin, GPIO_PIN_SET);
			for (int j = 0; j < 25000; j++)
			{
				HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_SET);
				delay_us(40);
				HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_RESET);
				delay_us(40);
			}
			HAL_Delay(10);
			// ----------------------------------------------
			HAL_GPIO_WritePin(GPIOC, X_DIR_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, Y_DIR_Pin, GPIO_PIN_RESET);
			for (int j = 0; j < 25000; j++)
			{
				HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_SET);
				delay_us(40);
				HAL_GPIO_WritePin(GPIOC, X_STEP_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, Y_STEP_Pin, GPIO_PIN_RESET);
				delay_us(40);
			}
			// ----------------------------------------------
		}

		HAL_GPIO_WritePin(GPIOC, X_EN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, Y_EN_Pin, GPIO_PIN_SET);

		CDC_Transmit_FS("OK");
	}
	else
	{
		CDC_Transmit_FS("Not Command!!!");
	}
}

BOOL SetCurrent(int iAxis, float fCurrent)
{
	uint16_t pot = (uint16_t)((0.256 * fCurrent * 8.0 * SENSE_RESISTOR + MAX_STEPPER_DIGIPOT_VOLTAGE / 2) / MAX_STEPPER_DIGIPOT_VOLTAGE);

	uint8_t data[3];

	if (pot > 0xFF)
	{
		data[0] = 0x01;
		data[1] = (uint8_t)0x100;
	}
	else
	{
		data[0] = 0x00;
		data[1] = (uint8_t)pot;
	}

	switch (iAxis)
	{
	case 0:	// X軸
		data[0] |= MCP4461_VW1;
		break;
	case 1:	// Y軸
		data[0] |= MCP4461_VW3;
		break;
	}

	data[0] |= MCP4461_WRITE;

	if (HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)0x2C << 1, (uint8_t *)data, 2, 1000) !=  HAL_OK)
	{
		return FALSE;
	}

	return TRUE;
}
