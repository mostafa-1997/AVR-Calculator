/*
 * Keypad_config.h
 *
 *  Created on: Oct 10, 2021
 *      Author: sa7er
 */

#ifndef HAL_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_CONFIG_H_

#define KEYPAD_u8COL_NUM		4
#define KEYPAD_u8ROW_NUM		4

#define KEYPAD_u8KEYPAD			{ {'7','8','9','/'},\
								  {'4','5','6','x'},\
								  {'1','2','3','-'},\
								  {'c','0','=','+'}  }

											/*CONFIGURE COLUMN PINS*/
#define KEYPAD_u8C1_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8C2_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8C3_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8C4_GROUP		DIO_u8GROUP_C

#define KEYPAD_u8C1_PIN			DIO_u8PIN4
#define KEYPAD_u8C2_PIN			DIO_u8PIN5
#define KEYPAD_u8C3_PIN			DIO_u8PIN6
#define KEYPAD_u8C4_PIN			DIO_u8PIN7

											/*CONFIGURE ROW PINS*/
#define KEYPAD_u8R1_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8R2_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8R3_GROUP		DIO_u8GROUP_C
#define KEYPAD_u8R4_GROUP		DIO_u8GROUP_C

#define KEYPAD_u8R1_PIN			DIO_u8PIN0
#define KEYPAD_u8R2_PIN			DIO_u8PIN1
#define KEYPAD_u8R3_PIN			DIO_u8PIN2
#define KEYPAD_u8R4_PIN			DIO_u8PIN3

#endif /* HAL_KEYPAD_CONFIG_H_ */
