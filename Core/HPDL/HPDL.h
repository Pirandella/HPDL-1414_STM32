#ifndef _HPDL_H_
#define _HPDL_H_

#include "stm32f1xx_hal.h"

/* Port configuration
 * 	If Data & Control pins are connected to the same port uncomment #define SAME_PORT else unncomment DIFF_PORT
 */
#define SAME_PORT
//#define DIFF_PORT // If Data & Control pins are connected to different ports

#define DISP_NUM	2
#define WR_BIT_NUM 	(((DISP_NUM > 1) & (DISP_NUM < 4)) ? (3) : (7))

// Don't forget to set right bases
#define ADDR_BASE	9
#define WR_BASE		7
#define DATA_BASE	0

#if defined(DIFF_PORT)
#define GPIO_CTRL	GPIOA
#define GPIO_DATA	GPIOA

#define _WR_0		GPIO_CTRL->ODR &= ~(1 << WR_BASE)
#define _WR_1		GPIO_CTRL->ODR |= (1 << WR_BASE)

#define _WR_0_(n)	GPIO_CTRL->ODR &= ~(n << WR_BASE)
#define _WR_1_		GPIO_CTRL->ODR |= (WR_BIT_NUM << WR_BASE)

#define ADDR(a){\
		GPIO_CTRL->ODR &= ~(3 << ADDR_BASE);\
		GPIO_CTRL->ODR |= ((a) ? (a << ADDR_BASE) : (0));\
	}
#define DATA(d){\
		GPIO_DATA->ODR &= ~((3 << ADDR_BASE) | (0x7F << DATA_BASE));\
		GPIO_DATA->ODR |= (d << DATA_BASE);\
	}
#elif defined(SAME_PORT)
#define GPIO		GPIOA

#define _WR_0		GPIO->ODR &= ~(1 << WR_BASE)
#define _WR_1		GPIO->ODR |= (1 << WR_BASE)

#define _WR_0_(n)		GPIO->ODR &= ~(n << WR_BASE)
#define _WR_1_		GPIO->ODR |= (WR_BIT_NUM << WR_BASE)


#define WRITE(a, d){\
		GPIO->ODR &= ~((3 << ADDR_BASE) | (0x7F << DATA_BASE));\
		GPIO->ODR |= ((a << ADDR_BASE) | (d << DATA_BASE));\
	}
#endif


void printc(uint8_t pos, char ch);
void mprintc(uint8_t pos, uint8_t disp, char ch);
void prints(char *str);
void mprints(uint8_t pos, char *str);
void clear(void);

#endif /* _HPDL_H_ */
