/*
 * Keypad_program.c
 *
 *  Created on: Oct 10, 2021
 *      Author: sa7er
 */
#include "../LIBRARY/errorStates.h"
#include "../LIBRARY/stdTypes.h"

#include "util/delay.h"

#include "../MCAL/DIO_interface.h"
#include "LCD_interface.h"

#include "Keypad_config.h"
#include "Keypad_private.h"

ES_t Keypad_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_enuSetPinDirection(KEYPAD_u8C1_GROUP,KEYPAD_u8C1_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C2_GROUP,KEYPAD_u8C2_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C3_GROUP,KEYPAD_u8C3_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(KEYPAD_u8C4_GROUP,KEYPAD_u8C4_PIN,DIO_u8OUTPUT);

	DIO_enuSetPinDirection(KEYPAD_u8R1_GROUP,KEYPAD_u8R1_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R2_GROUP,KEYPAD_u8R2_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R3_GROUP,KEYPAD_u8R3_PIN,DIO_u8INPUT);
	DIO_enuSetPinDirection(KEYPAD_u8R4_GROUP,KEYPAD_u8R4_PIN,DIO_u8INPUT);

	DIO_enuSetPinValue(KEYPAD_u8C1_GROUP,KEYPAD_u8C1_PIN,DIO_u8HIGH);
	DIO_enuSetPinValue(KEYPAD_u8C2_GROUP,KEYPAD_u8C2_PIN,DIO_u8HIGH);
	DIO_enuSetPinValue(KEYPAD_u8C3_GROUP,KEYPAD_u8C3_PIN,DIO_u8HIGH);
	DIO_enuSetPinValue(KEYPAD_u8C4_GROUP,KEYPAD_u8C4_PIN,DIO_u8HIGH);

	DIO_enuSetPinValue(KEYPAD_u8R1_GROUP,KEYPAD_u8R1_PIN,DIO_u8PULL_UP);
	DIO_enuSetPinValue(KEYPAD_u8R2_GROUP,KEYPAD_u8R2_PIN,DIO_u8PULL_UP);
	DIO_enuSetPinValue(KEYPAD_u8R3_GROUP,KEYPAD_u8R3_PIN,DIO_u8PULL_UP);
	DIO_enuSetPinValue(KEYPAD_u8R4_GROUP,KEYPAD_u8R4_PIN,DIO_u8PULL_UP);


	return Local_enuErrorState;
}

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 LocalAu8ColGroups[KEYPAD_u8COL_NUM] = {KEYPAD_u8C1_GROUP,KEYPAD_u8C2_GROUP,KEYPAD_u8C3_GROUP,KEYPAD_u8C4_GROUP};
	u8 LocalAu8ColPins[KEYPAD_u8COL_NUM] = {KEYPAD_u8C1_PIN,KEYPAD_u8C2_PIN,KEYPAD_u8C3_PIN,KEYPAD_u8C4_PIN};

	u8 LocalAu8RowGroups[KEYPAD_u8ROW_NUM] = {KEYPAD_u8R1_GROUP,KEYPAD_u8R2_GROUP,KEYPAD_u8R3_GROUP,KEYPAD_u8R4_GROUP};
	u8 LocalAu8RowPins[KEYPAD_u8ROW_NUM] = {KEYPAD_u8R1_PIN,KEYPAD_u8R2_PIN,KEYPAD_u8R3_PIN,KEYPAD_u8R4_PIN};

	u8 LocalAu8KEYPAD[KEYPAD_u8ROW_NUM][KEYPAD_u8COL_NUM] = KEYPAD_u8KEYPAD;

	u8 Local_u8ColIterator; u8 Local_u8RowIterator; u8 Local_u8Value;

	for(Local_u8ColIterator = 0;Local_u8ColIterator<KEYPAD_u8COL_NUM;Local_u8ColIterator++)
	{
		DIO_enuSetPinValue(LocalAu8ColGroups[Local_u8ColIterator],LocalAu8ColPins[Local_u8ColIterator],DIO_u8LOW);
		for(Local_u8RowIterator = 0;Local_u8RowIterator<KEYPAD_u8ROW_NUM;Local_u8RowIterator++)
		{
			DIO_enuGetPinValue(LocalAu8RowGroups[Local_u8RowIterator],LocalAu8RowPins[Local_u8RowIterator],&Local_u8Value);
			if(!Local_u8Value)//A KEY HAS BEEN PRESSED
			{
				_delay_ms(130);//DEALY UNTIL THE VIBRATION GET DAMPED.
				DIO_enuGetPinValue(LocalAu8RowGroups[Local_u8RowIterator],LocalAu8RowPins[Local_u8RowIterator],&Local_u8Value);
				if(!Local_u8Value)//THE USER IS STILL PRESSING THE KEY.
				{
					/*while (! Local_u8Value)
					{
						DIO_enuGetPinValue(LocalAu8RowGroups[Local_u8RowIterator], LocalAu8RowPins[Local_u8RowIterator], &Local_u8Value);
						LCD_enuSendData('P');
					}*/

					*Copy_pu8KeyValue = LocalAu8KEYPAD[Local_u8RowIterator][Local_u8ColIterator];
					return ES_OK;
				}
			}
		}
		DIO_enuSetPinValue(LocalAu8ColGroups[Local_u8ColIterator],LocalAu8ColPins[Local_u8ColIterator],DIO_u8HIGH);
	}

	*Copy_pu8KeyValue = KEYPAD_u8KEY_NOT_PRESSED;

	return Local_enuErrorState;
}
