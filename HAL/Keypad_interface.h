/*
 * Keypad_interface.h
 *
 *  Created on: Oct 10, 2021
 *      Author: sa7er
 */

#ifndef HAL_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_INTERFACE_H_

ES_t Keypad_enuInit(void);

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue);

#define KEYPAD_u8KEY_NOT_PRESSED		0xff

#endif /* HAL_KEYPAD_INTERFACE_H_ */
