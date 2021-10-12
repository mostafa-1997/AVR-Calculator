/*
 * LCD_config.h
 *
 *  Created on: Oct 3, 2021
 *      Author: sa7er
 */

#ifndef HAL_LCD_CONFIG_H_
#define HAL_LCD_CONFIG_H_

#define LCD_u8BIT_MODE				LCD_u8FOUR_BIT_MODE


/*                         CONTROL LINES                                                   */
#define LCD_u8RS_GROUP				DIO_u8GROUP_B
#define LCD_u8RS_PIN				DIO_u8PIN1

#define LCD_u8RW_GROUP				DIO_u8GROUP_B
#define LCD_u8RW_PIN				DIO_u8PIN2

#define LCD_u8EN_GROUP				DIO_u8GROUP_B
#define LCD_u8EN_PIN				DIO_u8PIN3



/*                         DATA LINES                                                   */
#define LCD_u8D7_GROUP				DIO_u8GROUP_A
#define LCD_u8D7_PIN				DIO_u8PIN7

#define LCD_u8D6_GROUP				DIO_u8GROUP_A
#define LCD_u8D6_PIN				DIO_u8PIN6

#define LCD_u8D5_GROUP				DIO_u8GROUP_A
#define LCD_u8D5_PIN				DIO_u8PIN5

#define LCD_u8D4_GROUP				DIO_u8GROUP_A
#define LCD_u8D4_PIN				DIO_u8PIN4

#define LCD_u8D3_GROUP				DIO_u8GROUP_A
#define LCD_u8D3_PIN				DIO_u8PIN4

#define LCD_u8D2_GROUP				DIO_u8GROUP_A
#define LCD_u8D2_PIN				DIO_u8PIN5

#define LCD_u8D1_GROUP				DIO_u8GROUP_A
#define LCD_u8D1_PIN				DIO_u8PIN6

#define LCD_u8D0_GROUP				DIO_u8GROUP_A
#define LCD_u8D0_PIN				DIO_u8PIN7


#endif /* HAL_LCD_CONFIG_H_ */
