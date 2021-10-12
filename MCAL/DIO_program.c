/*
 * DIO_program.c
 *
 *  Created on: Sep 28, 2021
 *      Author: sa7er
 */

#include "../LIBRARY/errorStates.h"
#include "../LIBRARY/stdTypes.h"

#include "DIO_private.h"
#include "DIO_config.h"

ES_t DIO_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	DIO_u8DDRA  = CONC(DIO_u8PORTA_PIN7_DIR,DIO_u8PORTA_PIN6_DIR,DIO_u8PORTA_PIN5_DIR,DIO_u8PORTA_PIN4_DIR,DIO_u8PORTA_PIN3_DIR,DIO_u8PORTA_PIN2_DIR,DIO_u8PORTA_PIN1_DIR,DIO_u8PORTA_PIN0_DIR);
	DIO_u8PORTA = CONC(DIO_u8PORTA_PIN7_VALUE,DIO_u8PORTA_PIN6_VALUE,DIO_u8PORTA_PIN5_VALUE,DIO_u8PORTA_PIN4_VALUE,DIO_u8PORTA_PIN3_VALUE,DIO_u8PORTA_PIN2_VALUE,DIO_u8PORTA_PIN1_VALUE,DIO_u8PORTA_PIN0_VALUE);

	DIO_u8DDRB  = CONC(DIO_u8PORTB_PIN7_DIR,DIO_u8PORTB_PIN6_DIR,DIO_u8PORTB_PIN5_DIR,DIO_u8PORTB_PIN4_DIR,DIO_u8PORTB_PIN3_DIR,DIO_u8PORTB_PIN2_DIR,DIO_u8PORTB_PIN1_DIR,DIO_u8PORTB_PIN0_DIR);
	DIO_u8PORTB = CONC(DIO_u8PORTB_PIN7_VALUE,DIO_u8PORTB_PIN6_VALUE,DIO_u8PORTB_PIN5_VALUE,DIO_u8PORTB_PIN4_VALUE,DIO_u8PORTB_PIN3_VALUE,DIO_u8PORTB_PIN2_VALUE,DIO_u8PORTB_PIN1_VALUE,DIO_u8PORTB_PIN0_VALUE);

	DIO_u8DDRC  = CONC(DIO_u8PORTC_PIN7_DIR,DIO_u8PORTC_PIN6_DIR,DIO_u8PORTC_PIN5_DIR,DIO_u8PORTC_PIN4_DIR,DIO_u8PORTC_PIN3_DIR,DIO_u8PORTC_PIN2_DIR,DIO_u8PORTC_PIN1_DIR,DIO_u8PORTC_PIN0_DIR);
	DIO_u8PORTC = CONC(DIO_u8PORTC_PIN7_VALUE,DIO_u8PORTC_PIN6_VALUE,DIO_u8PORTC_PIN5_VALUE,DIO_u8PORTC_PIN4_VALUE,DIO_u8PORTC_PIN3_VALUE,DIO_u8PORTC_PIN2_VALUE,DIO_u8PORTC_PIN1_VALUE,DIO_u8PORTC_PIN0_VALUE);

	DIO_u8DDRD  = CONC(DIO_u8PORTD_PIN7_DIR,DIO_u8PORTD_PIN6_DIR,DIO_u8PORTD_PIN5_DIR,DIO_u8PORTD_PIN4_DIR,DIO_u8PORTD_PIN3_DIR,DIO_u8PORTD_PIN2_DIR,DIO_u8PORTD_PIN1_DIR,DIO_u8PORTD_PIN0_DIR);
	DIO_u8PORTD = CONC(DIO_u8PORTD_PIN7_VALUE,DIO_u8PORTD_PIN6_VALUE,DIO_u8PORTD_PIN5_VALUE,DIO_u8PORTD_PIN4_VALUE,DIO_u8PORTD_PIN3_VALUE,DIO_u8PORTD_PIN2_VALUE,DIO_u8PORTD_PIN1_VALUE,DIO_u8PORTD_PIN0_VALUE);

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Direction)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID <= DIO_u8GROUP_D && Copy_u8PinID <= DIO_u8PIN7 && Copy_u8Direction <= DIO_u8OUTPUT)
	{
		switch(Copy_u8PortID)
		{
			case DIO_u8GROUP_A:
				DIO_u8DDRA &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8DDRA |= (Copy_u8Direction<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_B:
				DIO_u8DDRB &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8DDRB |= (Copy_u8Direction<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_C:
				DIO_u8DDRC &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8DDRC |= (Copy_u8Direction<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_D:
				DIO_u8DDRD &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8DDRD |= (Copy_u8Direction<<Copy_u8PinID);
			break;
		}

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Value)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID <= DIO_u8GROUP_D && Copy_u8PinID <= DIO_u8PIN7
	&& (Copy_u8Value <= DIO_u8HIGH || Copy_u8Value <= DIO_u8PULL_UP))
	{
		switch(Copy_u8PortID)
		{
			case DIO_u8GROUP_A:
				DIO_u8PORTA &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8PORTA |= (Copy_u8Value<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_B:
				DIO_u8PORTB &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8PORTB |= (Copy_u8Value<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_C:
				DIO_u8PORTC &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8PORTC |= (Copy_u8Value<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_D:
				DIO_u8PORTD &= ~(DIO_u8MASK_BIT<<Copy_u8PinID);
				DIO_u8PORTD |= (Copy_u8Value<<Copy_u8PinID);
			break;
		}

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuTogglePinValue(u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID <= DIO_u8GROUP_D && Copy_u8PinID <= DIO_u8PIN7)
	{
		switch(Copy_u8PortID)
		{
			case DIO_u8GROUP_A:
				DIO_u8PORTA ^= (DIO_u8MASK_BIT<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_B:
				DIO_u8PORTB ^= (DIO_u8MASK_BIT<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_C:
				DIO_u8PORTC ^= (DIO_u8MASK_BIT<<Copy_u8PinID);
			break;

			case DIO_u8GROUP_D:
				DIO_u8PORTD ^= (DIO_u8MASK_BIT<<Copy_u8PinID);
			break;
		}

		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuGetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 * Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(*Copy_pu8Value != NULL)
		{
			if(Copy_u8PortID <= DIO_u8GROUP_D && Copy_u8PinID <= DIO_u8PIN7)
			{
				switch(Copy_u8PortID)
				{
					case DIO_u8GROUP_A:
						*Copy_pu8Value = (DIO_u8PINA>>Copy_u8PinID) & DIO_u8MASK_BIT;
					break;

					case DIO_u8GROUP_B:
						*Copy_pu8Value = (DIO_u8PINB>>Copy_u8PinID) & DIO_u8MASK_BIT;
					break;

					case DIO_u8GROUP_C:
						*Copy_pu8Value = (DIO_u8PINC>>Copy_u8PinID) & DIO_u8MASK_BIT;
					break;

					case DIO_u8GROUP_D:
						*Copy_pu8Value = (DIO_u8PIND>>Copy_u8PinID) & DIO_u8MASK_BIT;
					break;
				}

				Local_enuErrorState = ES_OK;
			}
			else
			{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER;
		}

	return Local_enuErrorState;
}
