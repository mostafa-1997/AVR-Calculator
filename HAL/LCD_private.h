/*
 * LCD_private.h
 *
 *  Created on: Oct 3, 2021
 *      Author: sa7er
 */

#ifndef HAL_LCD_PRIVATE_H_
#define HAL_LCD_PRIVATE_H_

#define LCD_u8FOUR_BIT_MODE				40
#define LCD_u8EIGHT_BIT_MODE			80

/*                                 LCD INITIALIZATION                    */
#define LCD_u8EIGHT_BIT_FUNCTION_SET	0x38
#define LCD_u8FOUR_BIT_FUNCTION_SET		0x28
#define LCD_u8DISPLAY_CONTROL			0X0F
#define LCD_u8DISPLAY_CLEAR				0X01
#define LCD_u8ENTRY_MODE_SET			0x06
#define LCD_u8ENTRY_MODE_SET_DECREMENT	0x04

static ES_t LCD_enuWriteNLatch(u8 Copy_u8Value);
static ES_t LCD_enuLatch(void);

#define LCD_u8ERROR_STATE_SHIFT_BIT		2


#define LCD_u8FIRST_LINE_STARTING_ADDRESS	0x80
#define LCD_u8SECOND_LINE_STARTING_ADDRESS	0xC0

#define LCD_u8PATTERN_ZERO				0x40
#define LCD_u8PATTERN_ONE				0x48
#define LCD_u8PATTERN_TWO				0x50
#define LCD_u8PATTERN_THREE				0x58
#define LCD_u8PATTERN_FOUR				0x60
#define LCD_u8PATTERN_FIVE				0x68
#define LCD_u8PATTERN_SIX				0x70
#define LCD_u8PATTERN_SEVEN				0x78

#define LCD_u8DECREMENT					80
#define LCD_u8INCREMENT					90

#define LCD_f8FLOAT_ZERO				0.0
#define LCD_u8NEG_ONE					-1

#define LCD_u8ZERO						0
#define LCD_u8ONE						1
#define LCD_u8TWO						2
#define LCD_u8THREE						3
#define LCD_u8FOUR						4
#define LCD_u8FIVE						5
#define LCD_u8SIX						6
#define LCD_u8SEVEN						7
#define LCD_u8EIGHT						8
#define LCD_u8NINE						9
#define LCD_u8TEN						10
#define LCD_u8ELEVEN					11
#define LCD_u8TWELVE					12
#define LCD_u8THIRTEEN					13
#define LCD_u8FOURTEEN					14
#define LCD_u8FIFTEEN					15
#define LCD_u8SIXTEEN					16

#define LCD_u8ASCII_ZERO				48
#define LCD_u8ASCII_ONE					49
#define LCD_u8ASCII_TWO					50
#define LCD_u8ASCII_THREE				51
#define LCD_u8ASCII_FOUR				52
#define LCD_u8ASCII_FIVE				53
#define LCD_u8ASCII_SIX					54
#define LCD_u8ASCII_SEVEN				55
#define LCD_u8ASCII_EIGHT				56
#define LCD_u8ASCII_NINE				57

#endif /* HAL_LCD_PRIVATE_H_ */
