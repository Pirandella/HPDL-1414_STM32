#ifndef _HPDL_H_
#define _HPDL_H_

#include "stm32f1xx_hal.h"

/* Port configuration
 * 	If Data & Control pins are connected to the same port uncomment #define SAME_PORT else unncomment DIFF_PORT
 */
#define SAME_PORT
//#define DIFF_PORT // If Data & Control pins are connected to different ports

#define DISP_NUM	2
#define WR_BIT_NUM  3
//#define WR_BIT_NUM 	(((DISP_NUM > 1) & (DISP_NUM < 4)) ? (3) : (7))

// Don't forget to set right bases
#define ADDR_BASE	9
#define WR_BASE		7
#define DATA_BASE	0

#if defined(DIFF_PORT)
#define GPIO_CTRL	GPIOA
#define GPIO_DATA	GPIOB

#define _WR_0		GPIO_CTRL->ODR &= ~(1 << WR_BASE)
#define _WR_1		GPIO_CTRL->ODR |= (1 << WR_BASE)

#define _WR_0_(n)	GPIO_CTRL->ODR &= ~(n << WR_BASE)
#define _WR_1_		GPIO_CTRL->ODR |= (WR_BIT_NUM << WR_BASE)

#elif defined(SAME_PORT)
#define GPIO		GPIOA

#define _WR_0		GPIO->ODR &= ~(1 << WR_BASE)
#define _WR_1		GPIO->ODR |= (1 << WR_BASE)

#define _WR_0_(n)	GPIO->ODR &= ~(n << WR_BASE)
#define _WR_1_		GPIO->ODR |= (WR_BIT_NUM << WR_BASE)
#endif

/*	Function: printc
 *  --------------------------------------------------------------
 *  Description:
 *		Prints a character to HPDL-1414 display.
 *		(Works only with one display)
 *	Arguments:
 *		pos: Segment number (0 - 3). Where 3 is the most left segment.
 *		ch:	 Character that will be printed on the display.
 *	Return:
 *		None
 */
void printc(uint8_t pos, char ch);

/*	Function: mprintc
 *  --------------------------------------------------------------
 *  Description:
 *		Prints a character to HPDL-1414 display.
 *		(Works with multiple displays)
 *	Arguments:
 *		pos: 	Segment number (0 - 3). Where 3 is the most left segment.
 *		disp:	Display number (1 - DISP_NUM). Where 1 is the most left display.
 *		ch:	 	Character that will be printed on the display.
 *	Return:
 *		None
 */
void mprintc(uint8_t pos, uint8_t disp, char ch);

/*	Function: prints
 *	--------------------------------------------------------------
 *	Description:
 *		Prints a string from left to right to all available displays.
 *	Arguments:
 *		str:	String that will be printed
 *	Return:
 *		None
 */
void prints(char *str);

/*	Function: mprints
 *	--------------------------------------------------------------
 *	Description:
 *		Prints a string from left to right to all available displays with ability to set starting position.
 *	Arguments:
 *		pos:	Position from where string will be printed
 *		disp:	Display number (1 - DISP_NUM). Where 1 is the most left display.
 *		str:	String that will be printed
 *	Return:
 *		None
 */
void mprints(uint8_t pos, uint8_t disp, char *str);

/*	Function: clear
 *  --------------------------------------------------------------
 *  Description:
 *  	Clears all available displays
 *  Arguments:
 *  	None
 *  Return:
 *		None
 */
void clear(void);

#endif /* _HPDL_H_ */
