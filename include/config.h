/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG__H__
#define __CONFIG__H__

#ifdef __cplusplus
 extern "C" {
#endif


 /* USER CODE BEGIN EXPORTED_DEFINES */
#define MCP4461_VW0 0x00
#define MCP4461_VW1 0x10
#define MCP4461_NVW0 0x20
#define MCP4461_NVW1 0x30
#define MCP4461_TCON0 0x40
#define MCP4461_STATUS 0x50
#define MCP4461_VW2 0x60
#define MCP4461_VW3 0x70
#define MCP4461_NVW2 0x80
#define MCP4461_NVW3 0x90
#define MCP4461_TCON1 0xA0
#define MCP4461_WRITE 0x0
#define MCP4461_INCREMENT 0x4 //01 left shift by 2
#define MCP4461_DECREMENT 0x8 //10 left shift by 2
#define MCP4461_READ 0xC //11 left shift by 2

#define SENSE_RESISTOR 0.1
#define MAX_STEPPER_DIGIPOT_VOLTAGE (3.3 * 2.5 / (2.7 + 2.5))


 /* USER CODE END EXPORTED_DEFINES */

 /* USER CODE BEGIN EXPORTED_MACRO */
#define DF_ARRY_SIZE(ARRY)	sizeof(ARRY) / sizeof(ARRY[0])




/* USER CODE END EXPORTED_MACRO */


 /* USER CODE BEGIN EXPORTED_TYPES */
 typedef enum {
     FALSE = 0,
     TRUE
 } BOOL;

 /* USER CODE END EXPORTED_TYPES */

 /* USER CODE BEGIN EXPORTED_VARIABLES */
 extern I2C_HandleTypeDef hi2c1;
 extern TIM_HandleTypeDef htim3;
 /* USER CODE END EXPORTED_VARIABLES */



#ifdef __cplusplus
}
#endif

#endif /* __CONFIG__H__ */
