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

// Don't forget to set right bases
#define ADDR_BASE	9
#define WR_BASE		7
#define DATA_BASE	0

#if defined(DIFF_PORT)
#define HPDL_GPIO_CTRL	GPIOA
#define HPDL_GPIO_DATA	GPIOB

#define WRITE(a, n, d){\
		HPDL_GPIO_CTRL->ODR |= (WR_BIT_NUM << WR_BASE);\
		HPDL_GPIO_CTRL->ODR &= ~(3 << ADDR_BASE);\
		HPDL_GPIO_CTRL->ODR |= ((a) ? (a << ADDR_BASE) : (0));\
		HPDL_GPIO_DATA->ODR &= ~(0x7F << DATA_BASE);\
		HPDL_GPIO_DATA->ODR |= (d << DATA_BASE);\
		HPDL_GPIO_CTRL->ODR &= ~(n << WR_BASE);\
		HPDL_GPIO_CTRL->ODR |= (WR_BIT_NUM << WR_BASE);\
	}
#elif defined(SAME_PORT)
#define HPDL_GPIO		GPIOA

#define WRITE(a, n, d){\
		HPDL_GPIO->ODR |= (WR_BIT_NUM << WR_BASE);\
		HPDL_GPIO->ODR &= ~((3 << ADDR_BASE) | (0x7F << DATA_BASE));\
		HPDL_GPIO->ODR |= ((a << ADDR_BASE) | (d << DATA_BASE));\
		HPDL_GPIO->ODR &= ~(n << WR_BASE);\
		HPDL_GPIO->ODR |= (WR_BIT_NUM << WR_BASE);\
	}
#endif

/*	Function: hpdl_init
 * 	--------------------------------------------------------------
 * 	Description:
 * 		Initializes map array to to ease segment addressing.
 * 	Arguments:
 * 		None
 * 	Return:
 * 		None
 */
void hpdl_init(void);

/*	Function: hpdl_printc
 *  --------------------------------------------------------------
 *  Description:
 *		Prints a character to HPDL-1414 display.
 *	Arguments:
 *		pos: 	Segment number.
 *		ch:	 	Character that will be printed on the display.
 *	Return:
 *		None
 */
void hpdl_printc(uint8_t pos, char ch);

/*	Function: hpdl_prints
 *	--------------------------------------------------------------
 *	Description:
 *		Prints a string from left to right to all available displays with ability to set starting position.
 *	Arguments:
 *		pos:	Position from where string will be printed
 *		str:	String that will be printed. (Must be null terminated)
 *	Return:
 *		None
 */
void hpdl_prints(uint8_t pos, char *str);

/*	Function: hpdl_clear
 *  --------------------------------------------------------------
 *  Description:
 *  	Clears all available displays
 *  Arguments:
 *  	None
 *  Return:
 *		None
 */
void hpdl_clear(void);

#endif /* _HPDL_H_ */
