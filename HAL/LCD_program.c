/*
 * LCD_program.c
 *
 *  Created on: Oct 3, 2021
 *      Author: sa7er
 */
#include "../LIBRARY/errorStates.h"
#include "../LIBRARY/stdTypes.h"

#include "util/delay.h"

#include "../MCAL/DIO_interface.h"

#include "LCD_config.h"
#include "LCD_private.h"

ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	u32 Local_u32ErrorState = 0;

	//control lines
	Local_u32ErrorState = DIO_enuSetPinDirection(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8OUTPUT);
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8RW_GROUP,LCD_u8RW_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;

	//data lines
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D7_GROUP,LCD_u8D7_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D6_GROUP,LCD_u8D6_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D5_GROUP,LCD_u8D5_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D4_GROUP,LCD_u8D4_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;


	_delay_ms(35);
#if LCD_u8BIT_MODE == LCD_u8FOUR_BIT_MODE
	Local_u32ErrorState |= (DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (LCD_enuWriteNLatch(LCD_u8FOUR_BIT_FUNCTION_SET))<<LCD_u8ERROR_STATE_SHIFT_BIT;
#elif LCD_u8BIT_MODE == LCD_u8EIGHT_BIT_MODE
	Local_u32ErrorState |= (DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RW_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (LCD_enuWriteNLatch(LCD_u8EIGHT_BIT_FUNCTION_SET))<<LCD_u8ERROR_STATE_SHIFT_BIT;

	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D3_GROUP,LCD_u8D3_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D2_GROUP,LCD_u8D2_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D1_GROUP,LCD_u8D1_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (DIO_enuSetPinDirection(LCD_u8D0_GROUP,LCD_u8D0_PIN,DIO_u8OUTPUT))<<LCD_u8ERROR_STATE_SHIFT_BIT;
#else
#error"LCD mode is wrong"
#endif

	_delay_ms(2);
	Local_u32ErrorState |= (DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RW_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (LCD_enuWriteNLatch(LCD_u8DISPLAY_CONTROL))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	_delay_ms(2);
	Local_u32ErrorState |= (DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RW_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (LCD_enuWriteNLatch(LCD_u8DISPLAY_CLEAR))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	_delay_ms(3);
	Local_u32ErrorState |= (DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RW_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	Local_u32ErrorState |= (LCD_enuWriteNLatch(LCD_u8ENTRY_MODE_SET))<<LCD_u8ERROR_STATE_SHIFT_BIT;

	if(Local_u32ErrorState == 0)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuSendData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);
	Local_u8ErrorState |= (LCD_enuWriteNLatch(Copy_u8Data))<<LCD_u8ERROR_STATE_SHIFT_BIT;

	if(Local_u8ErrorState == 0)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);
	Local_u8ErrorState |= (LCD_enuWriteNLatch(Copy_u8Data))<<LCD_u8ERROR_STATE_SHIFT_BIT;

	if(Local_u8ErrorState == 0)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuSendString(const char * Copy_pcString)
{
	ES_t Local_enuErrorState = ES_NOK;

	u32 Local_u8ErrorState = 0;

	if(Copy_pcString != NULL)
	{
		u8 Local_u8Iterator = 0;
		while(*Copy_pcString)//'\0'
		{
			Local_u8ErrorState = DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);
			Local_u8ErrorState |= (LCD_enuWriteNLatch(*Copy_pcString++))<<(LCD_u8ERROR_STATE_SHIFT_BIT * Local_u8Iterator);
			Local_u8Iterator++;
		}
		if(Local_u8ErrorState == 0)
		{
			Local_enuErrorState = ES_OK;
		}

	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuGoToPosition(u8 Copy_u8Line,u8 Copy_u8Column)//16*2
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);//sending command

	if(Copy_u8Line == LCD_u8ONE)
	{
		Local_u8ErrorState |= LCD_enuWriteNLatch(LCD_u8FIRST_LINE_STARTING_ADDRESS + (Copy_u8Column - LCD_u8ONE))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	}
	else if(Copy_u8Line == LCD_u8TWO)
	{
		Local_u8ErrorState |= LCD_enuWriteNLatch(LCD_u8SECOND_LINE_STARTING_ADDRESS + (Copy_u8Column - LCD_u8ONE))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	}

	if(Local_u8ErrorState == 0)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuSendExtraCharacter(u8 Copy_Au8Arr[],u8 Copy_u8PatternNumber,u8 Copy_u8NumberOfPatterns,u8 Copy_u8Line,u8 Copy_u8Column,u8 Copy_u8IncDec)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);//sending command

	switch(Copy_u8PatternNumber)
	{
		case LCD_u8ZERO:
			LCD_enuWriteNLatch(LCD_u8PATTERN_ZERO);
		break;
		case LCD_u8ONE:
			LCD_enuWriteNLatch(LCD_u8PATTERN_ONE);
		break;
		case LCD_u8TWO:
			LCD_enuWriteNLatch(LCD_u8PATTERN_TWO);
		break;
		case LCD_u8THREE:
			LCD_enuWriteNLatch(LCD_u8PATTERN_THREE);
		break;
		case LCD_u8FOUR:
			LCD_enuWriteNLatch(LCD_u8PATTERN_FOUR);
		break;
		case LCD_u8FIVE:
			LCD_enuWriteNLatch(LCD_u8PATTERN_FIVE);
		break;
		case LCD_u8SIX:
			LCD_enuWriteNLatch(LCD_u8PATTERN_SIX);
		break;
		case LCD_u8SEVEN:
			LCD_enuWriteNLatch(LCD_u8PATTERN_SEVEN);
		break;
	}

	/*FILL THE CGRAM WITH THE PATTERNS*/
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);//sending data

	u8 Local_u8Iterator;
	for(Local_u8Iterator = 0;Local_u8Iterator<Copy_u8NumberOfPatterns*LCD_u8EIGHT;Local_u8Iterator++)
		LCD_enuWriteNLatch(Copy_Au8Arr[Local_u8Iterator]);

	/*INCREMENT OR DECREMENT*/
	if(Copy_u8IncDec == LCD_u8DECREMENT)
	{
		DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);//sending command
		LCD_enuWriteNLatch(LCD_u8ENTRY_MODE_SET_DECREMENT);
	}

	/*GO TO POSITION*/
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8LOW);//sending command
	if(Copy_u8Line == LCD_u8ONE)
	{
		LCD_enuWriteNLatch(LCD_u8FIRST_LINE_STARTING_ADDRESS + (Copy_u8Column - LCD_u8ONE));
	}
	else if(Copy_u8Line == LCD_u8TWO)
	{
		LCD_enuWriteNLatch(LCD_u8SECOND_LINE_STARTING_ADDRESS + (Copy_u8Column - LCD_u8ONE));
	}

	/*DISPLAY DATA*/
	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);//sending data
	for(Local_u8Iterator = 0;Local_u8Iterator<Copy_u8NumberOfPatterns;Local_u8Iterator++)
	{
		LCD_enuWriteNLatch(Copy_u8PatternNumber);
		Copy_u8PatternNumber++;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayInt(s32 Copy_s32Number)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);//sending data

	if(Copy_s32Number == LCD_u8ZERO)
		LCD_enuWriteNLatch(LCD_u8ASCII_ZERO);
	else
	{
		if(Copy_s32Number < LCD_u8ZERO)
			{
				LCD_enuWriteNLatch('-');
				Copy_s32Number *= LCD_u8NEG_ONE;
			}

			//REVERSE THE NUMBER
			s32 Local_s32Remainder = LCD_u8ZERO;
			s32 Local_s32Current;
			s32 Local_s32Duplicate = Copy_s32Number;

			while(Local_s32Duplicate != LCD_u8ZERO)
			{
				Local_s32Current = Local_s32Duplicate%LCD_u8TEN;
				Local_s32Remainder = (Local_s32Remainder * LCD_u8TEN) + Local_s32Current;
				Local_s32Duplicate /= LCD_u8TEN;
			}

			while(Local_s32Remainder != LCD_u8ZERO)
			{
				LCD_enuWriteNLatch( (Local_s32Remainder%LCD_u8TEN) + LCD_u8ASCII_ZERO);
				Local_s32Remainder /= LCD_u8TEN;
			}

			//SOLVING THE ZERO BUG
			while(1)
			{
				Local_s32Current = Copy_s32Number%LCD_u8TEN;
				if(Local_s32Current != LCD_u8ZERO)
					break;
				else
				{
					LCD_enuWriteNLatch(LCD_u8ASCII_ZERO);
					Copy_s32Number /= LCD_u8TEN;
				}
			}
	}

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayFloat(f32 Copy_f32Number)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,DIO_u8HIGH);//sending data

	u32 Local_u32IntVer = (u32)Copy_f32Number;

	if(Local_u32IntVer == LCD_u8ZERO)
	{
		LCD_enuWriteNLatch(LCD_u8ASCII_ZERO);
		//ADD THE FLOATING POINT
		LCD_enuWriteNLatch('.');

		//DISPLAY NUMBERS AFTER THE FLOATING POINT
		while((u32)Copy_f32Number)
		{
			Copy_f32Number *= 10;
			LCD_enuWriteNLatch(((u32)Copy_f32Number%LCD_u8TEN) + LCD_u8ASCII_ZERO);
			Copy_f32Number = Copy_f32Number - (u32)Copy_f32Number;
		}
	}

	else
	{
		if(Copy_f32Number < LCD_u8ZERO)
			{
				LCD_enuWriteNLatch('-');
				Copy_f32Number *= LCD_u8NEG_ONE;
			}

			//REVERSE THE NUMBER
			u32 Local_u32Remainder = LCD_u8ZERO;
			u32 Local_u32Current;
			u32 Local_u32Duplicate = Local_u32IntVer;

			while(Local_u32Duplicate != LCD_u8ZERO)
			{
				Local_u32Current = Local_u32Duplicate%LCD_u8TEN;
				Local_u32Remainder = (Local_u32Remainder * LCD_u8TEN) + Local_u32Current;
				Local_u32Duplicate /= LCD_u8TEN;
			}

			while(Local_u32Remainder != LCD_u8ZERO)
			{
				LCD_enuWriteNLatch( (Local_u32Remainder%LCD_u8TEN) + LCD_u8ASCII_ZERO);
				Local_u32Remainder /= LCD_u8TEN;
			}

			//SOLVING THE ZERO BUG
			s32 Local_s32Duplicate2 = Local_u32IntVer;
			while(1)
			{
				Local_u32Current = Local_s32Duplicate2%LCD_u8TEN;
				if(Local_u32Current != LCD_u8ZERO)
					break;
				else
				{
					LCD_enuWriteNLatch(LCD_u8ASCII_ZERO);
					Local_s32Duplicate2 /= LCD_u8TEN;
				}
			}

			//ADD THE FLOATING POINT
			LCD_enuWriteNLatch('.');

			//DISPLAY NUMBERS AFTER THE FLOATING POINT
			Copy_f32Number -=  Local_u32IntVer;

			while(Copy_f32Number)
			{
				Copy_f32Number *= 10;
				LCD_enuWriteNLatch(((u32)Copy_f32Number%LCD_u8TEN) + LCD_u8ASCII_ZERO);
				Copy_f32Number = Copy_f32Number - (u32)Copy_f32Number;
			}

	}




	return Local_enuErrorState;
}

static ES_t LCD_enuWriteNLatch(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW);
	DIO_enuSetPinValue(LCD_u8RW_GROUP,LCD_u8RW_PIN,DIO_u8LOW);

#if LCD_u8BIT_MODE == LCD_u8FOUR_BIT_MODE

	u8 Local_u8RSValue;

	if(Copy_u8Data == LCD_u8FOUR_BIT_FUNCTION_SET)
	{
		DIO_enuGetPinValue(LCD_u8RS_GROUP,LCD_u8RS_PIN,&Local_u8RSValue);
		if(Local_u8RSValue == DIO_u8LOW)
		{
			DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Data>>DIO_u8PIN7)&1);
			DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,(Copy_u8Data>>DIO_u8PIN6)&1);
			DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,(Copy_u8Data>>DIO_u8PIN5)&1);
			DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,(Copy_u8Data>>DIO_u8PIN4)&1);
			LCD_enuLatch();
		}
	}

	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Data>>DIO_u8PIN7)&1);
	DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,(Copy_u8Data>>DIO_u8PIN6)&1);
	DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,(Copy_u8Data>>DIO_u8PIN5)&1);
	DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,(Copy_u8Data>>DIO_u8PIN4)&1);
	LCD_enuLatch();

	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Data>>DIO_u8PIN3)&1);
	DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,(Copy_u8Data>>DIO_u8PIN2)&1);
	DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,(Copy_u8Data>>DIO_u8PIN1)&1);
	DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,(Copy_u8Data>>DIO_u8PIN0)&1);
	LCD_enuLatch();

#elif LCD_u8BIT_MODE == LCD_u8EIGHT_BIT_MODE

	DIO_enuSetPinValue(LCD_u8D7_GROUP,LCD_u8D7_PIN,(Copy_u8Data>>DIO_u8PIN7)&1);
	DIO_enuSetPinValue(LCD_u8D6_GROUP,LCD_u8D6_PIN,(Copy_u8Data>>DIO_u8PIN6)&1);
	DIO_enuSetPinValue(LCD_u8D5_GROUP,LCD_u8D5_PIN,(Copy_u8Data>>DIO_u8PIN5)&1);
	DIO_enuSetPinValue(LCD_u8D4_GROUP,LCD_u8D4_PIN,(Copy_u8Data>>DIO_u8PIN4)&1);
	DIO_enuSetPinValue(LCD_u8D3_GROUP,LCD_u8D3_PIN,(Copy_u8Data>>DIO_u8PIN3)&1);
	DIO_enuSetPinValue(LCD_u8D2_GROUP,LCD_u8D2_PIN,(Copy_u8Data>>DIO_u8PIN2)&1);
	DIO_enuSetPinValue(LCD_u8D1_GROUP,LCD_u8D1_PIN,(Copy_u8Data>>DIO_u8PIN1)&1);
	DIO_enuSetPinValue(LCD_u8D0_GROUP,LCD_u8D0_PIN,(Copy_u8Data>>DIO_u8PIN0)&1);
	LCD_enuLatch();


#else
#error"LCD mode is wrong"
#endif


	return Local_enuErrorState;
}

static ES_t LCD_enuLatch(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_u8ErrorState = 0;

	Local_u8ErrorState = DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8HIGH);
	_delay_ms(5);
	Local_u8ErrorState |= (DIO_enuSetPinValue(LCD_u8EN_GROUP,LCD_u8EN_PIN,DIO_u8LOW))<<LCD_u8ERROR_STATE_SHIFT_BIT;
	_delay_ms(5);

	if(Local_u8ErrorState == 0)
	{
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
