/*
 * main.c
 *
 *  Created on: Oct 3, 2021
 *      Author: sa7er
 */
#include "../LIBRARY/errorStates.h"
#include "../LIBRARY/stdTypes.h"

#include "../HAL/LCD_interface.h"
#include "../HAL/Keypad_interface.h"

//functions prototype
u8 App_u8IsOperator(const u8 Copy_u8Operator);
u8 App_u8IsGeneralOperator(const u8 Copy_u8GeneralOperator);
void App_voidFillNumbers(s8 * Copy_s8Num, u8 * Copy_u8Operator, u8 * Copy_u8GeneralOperator);
void App_voidCalculate(s8 Copy_s8Num1, s8 Copy_s8Num2, u8 Copy_u8Operator);

int main()
{
	LCD_enuInit();
	Keypad_enuInit();

	s32 Local_s32Num1 = NULL, Local_s32Num2 = NULL;
	u8 Local_u8Operator, Local_u8GeneralOperator;
	s32 Local_s32Num = 0;
	u8 Local_u8PressedKey, Local_u8Iterator = 0, Local_u8IsNegative = FALSE;



while(1)//super loop system
{
	while(Local_s32Num1 == NULL)
	{
		Keypad_enuGetPressedKey(&Local_u8PressedKey);
		if(Local_u8PressedKey != KEYPAD_u8KEY_NOT_PRESSED)
		{
			if(App_u8IsGeneralOperator(Local_u8PressedKey) == 'c')
			{
				LCD_enuSendCommand(0x01);
				Local_u8Iterator = 0;
				continue;
			}
			if(Local_u8Iterator == 0 && App_u8IsOperator(Local_u8PressedKey) == '-')//ENTERED NUMBER IS NEGATIVE
			{
				Local_u8IsNegative = TRUE;
				Local_u8Iterator++;
				LCD_enuSendData(Local_u8PressedKey);
				continue;
			}
			LCD_enuSendData(Local_u8PressedKey);
			if(App_u8IsOperator(Local_u8PressedKey))//the real operator is entered
			{
				if(Local_u8IsNegative)
				{
					Local_s32Num1 = Local_s32Num * -1;
					Local_u8IsNegative = FALSE;
					Local_u8Operator = Local_u8PressedKey;
					Local_u8Iterator = 0;
					Local_s32Num = 0;
					break;
				}
				Local_u8IsNegative = FALSE;
				Local_s32Num1 = Local_s32Num;
				Local_u8Operator = Local_u8PressedKey;
				Local_u8Iterator = 0;
				Local_s32Num = 0;
				break;
			}
			Local_s32Num = Local_s32Num * 10 + (Local_u8PressedKey - 48);
			Local_u8Iterator++;
		}
	}

	while(Local_s32Num2 == NULL)
	{
		Keypad_enuGetPressedKey(&Local_u8PressedKey);
		if(Local_u8PressedKey != KEYPAD_u8KEY_NOT_PRESSED)
		{
			if(App_u8IsGeneralOperator(Local_u8PressedKey) == 'c')
			{
				LCD_enuSendCommand(0x01);
				Local_u8Iterator = 0;
				continue;
			}
			if(Local_u8Iterator == 0 && App_u8IsOperator(Local_u8PressedKey) == '-')//ENTERED NUMBER IS NEGATIVE
			{
				Local_u8IsNegative = TRUE;
				Local_u8Iterator++;
				LCD_enuSendData(Local_u8PressedKey);
				continue;
			}
			LCD_enuSendData(Local_u8PressedKey);
			if(App_u8IsGeneralOperator(Local_u8PressedKey))
			{
				if(Local_u8IsNegative)
				{
					Local_s32Num2 = Local_s32Num * -1;
					Local_u8IsNegative = FALSE;
					Local_u8GeneralOperator = Local_u8PressedKey;
					Local_u8Iterator = 0;
					Local_s32Num = 0;
					break;
				}
				Local_u8IsNegative = FALSE;
				Local_s32Num2 = Local_s32Num;
				Local_u8GeneralOperator = Local_u8PressedKey;
				Local_u8Iterator = 0;
				Local_s32Num = 0;
				break;
			}
			Local_s32Num = Local_s32Num * 10 + (Local_u8PressedKey - 48);
			Local_u8Iterator++;
		}
	}
	//calculate
	//LCD_enuDisplayInt(Local_s32Num1);
	//LCD_enuSendData(Local_u8Operator);
	App_voidCalculate(Local_s32Num1,Local_s32Num2,Local_u8Operator);
	Local_s32Num1 = Local_s32Num2 = NULL;

}
	return 0;
}

u8 App_u8IsOperator(const u8 Copy_u8Operator)
{
	if(Copy_u8Operator == '+' || Copy_u8Operator == '-' || Copy_u8Operator == 'x' || Copy_u8Operator == '/')
	{
		return Copy_u8Operator;
	}

	return 0;
}

u8 App_u8IsGeneralOperator(const u8 Copy_u8GeneralOperator)
{
	if(Copy_u8GeneralOperator == '=' || Copy_u8GeneralOperator == 'c')
	{
		return Copy_u8GeneralOperator;
	}
	return 0;
}

void App_voidFillNumbers(s8 * Copy_s8Num, u8 * Copy_u8Operator, u8 * Copy_u8GeneralOperator)
{
	s8 Local_s8Num = 0;
	u8 Local_u8PressedKey = 0, Local_u8Iterator = 0, Local_u8IsNegative = FALSE;
	while(1)
	{
		Keypad_enuGetPressedKey(&Local_u8PressedKey);
		if(Local_u8PressedKey != KEYPAD_u8KEY_NOT_PRESSED)
		{
			//LCD_enuSendData(Local_u8PressedKey);
			if(Local_u8Iterator == 0 && App_u8IsOperator(Local_u8PressedKey) == '-')//ENTERED NUMBER IS NEGATIVE
			{
				Local_u8IsNegative = TRUE;
				Local_u8Iterator++;
				LCD_enuSendData(Local_u8PressedKey);
				continue;
			}
			LCD_enuSendData(Local_u8PressedKey);
			if(App_u8IsOperator(Local_u8PressedKey))//the real operator is entered
			{
				if(Local_u8IsNegative)
					*Copy_s8Num = Local_s8Num*-1;
				*Copy_s8Num = Local_s8Num;
				*Copy_u8Operator = Local_u8PressedKey;
				break;
			}
			if(App_u8IsGeneralOperator(Local_u8PressedKey))
			{
				*Copy_u8GeneralOperator = Local_u8PressedKey;
				break;
			}
			Local_s8Num = Local_s8Num * 10 + (Local_u8PressedKey - 48);
			Local_u8Iterator++;
		}
	}
}

void App_voidCalculate(s8 Copy_s8Num1, s8 Copy_s8Num2, u8 Copy_u8Operator)
{
	switch(Copy_u8Operator)
	{
		case '+':
			LCD_enuGoToPosition(LCD_u8TWO,LCD_u8ONE);
			LCD_enuDisplayInt((Copy_s8Num1 + Copy_s8Num2));
		break;
		case '-':
			LCD_enuGoToPosition(LCD_u8TWO,LCD_u8ONE);
			LCD_enuDisplayInt((Copy_s8Num1 - Copy_s8Num2));
		break;
		case 'x':
			LCD_enuGoToPosition(LCD_u8TWO,LCD_u8ONE);
			LCD_enuDisplayInt((Copy_s8Num1 * Copy_s8Num2));
		break;
		case '/':
			LCD_enuGoToPosition(LCD_u8TWO,LCD_u8ONE);
			LCD_enuDisplayInt((Copy_s8Num1 / Copy_s8Num2));
		break;
	}
}
