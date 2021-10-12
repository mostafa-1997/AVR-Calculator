/*
 * DIO_private.h
 *
 *  Created on: Sep 28, 2021
 *      Author: sa7er
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#define DIO_u8GROUP_A		0
#define DIO_u8GROUP_B		1
#define DIO_u8GROUP_C		2
#define DIO_u8GROUP_D		3


#define DIO_u8PIN0			0
#define DIO_u8PIN1			1
#define DIO_u8PIN2			2
#define DIO_u8PIN3			3
#define DIO_u8PIN4			4
#define DIO_u8PIN5			5
#define DIO_u8PIN6			6
#define DIO_u8PIN7			7


#define DIO_u8INPUT			0
#define DIO_u8OUTPUT		1

#define DIO_u8MASK_BIT		1

#define DIO_u8LOW			0
#define DIO_u8HIGH			1

#define DIO_u8FLOAT			0
#define DIO_u8PULL_UP		1


#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)    0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)         CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)


#define DIO_u8DDRA *((u8*)0x3A)
#define DIO_u8PORTA *((u8*)0x3B)
#define DIO_u8PINA  *((volatile u8*)0x39)

#define DIO_u8DDRB *((u8*)0x37)
#define DIO_u8PORTB *((u8*)0x38)
#define DIO_u8PINB *((volatile u8*)0x39)

#define DIO_u8DDRC *((u8*)0x34)
#define DIO_u8PORTC *((u8*)0x35)
#define DIO_u8PINC *((volatile u8*)0x33)

#define DIO_u8DDRD	*((u8*)0x31)
#define DIO_u8PORTD	*((u8*)0x32)
#define DIO_u8PIND	*((volatile u8*)0x30)


#endif /* DIO_PRIVATE_H_ */
