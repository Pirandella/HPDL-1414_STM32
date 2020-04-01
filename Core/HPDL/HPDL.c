#include "HPDL.h"

void printc(uint8_t pos, char ch){
	if(ch < 0x20) return;									// Check for non printable characters
	if(ch > 0x5F) ch -= 0x20;								// Convert lower case letter to upper case
	_WR_1;
#if defined(DIFF_PORT)
	GPIO_CTRL->ODR &= ~(3 << ADDR_BASE); 					// Clear address bits
	GPIO_CTRL->ODR |= ((pos) ? (pos << ADDR_BASE) : (0)); 	// Write address bits
	GPIO_DATA->ODR &= ~(0x7F << DATA_BASE);					// Clear data bits
	GPIO_DATA->ODR |= (ch << DATA_BASE); 					// Write data bits
#elif defined(SAME_PORT)
	GPIO->ODR &= ~((3 << ADDR_BASE) | (0x7F << DATA_BASE)); // Clear address and data bits
	GPIO->ODR |= ((pos << ADDR_BASE) | (ch << DATA_BASE)); 	// Write address and data bits
#endif
	_WR_0;
	_WR_1;
}

void mprintc(uint8_t pos, uint8_t disp, char ch){
	if(ch < 0x20) return;									// Check for non printable characters
	if(ch > 0x5F) ch -= 0x20;								// Convert lower case letter to upper case
	_WR_1_;
#if defined(DIFF_PORT)
	GPIO_CTRL->ODR &= ~(3 << ADDR_BASE); 					// Clear address bits
	GPIO_CTRL->ODR |= ((pos) ? (pos << ADDR_BASE) : (0)); 	// Write address bits
	GPIO_DATA->ODR &= ~(0x7F << DATA_BASE);					// Clear data bits
	GPIO_DATA->ODR |= (ch << DATA_BASE); 					// Write data bits
#elif defined(SAME_PORT)
	GPIO->ODR &= ~((3 << ADDR_BASE) | (0x7F << DATA_BASE)); // Clear address and data bits
	GPIO->ODR |= ((pos << ADDR_BASE) | (ch << DATA_BASE)); 	// Write address and data bits
#endif
	_WR_0_(disp);
	_WR_1_;
}

void prints(char *str){
#if DISP_NUM == 1
	uint8_t i = 4;
	while(*str)
		printc(--i, *(str++));
#else // Multiple displays
	for(uint8_t i = 1; i <= DISP_NUM; i++)					// Loop through display numbers
		for(uint8_t j = 4; j > 0; str++)					// Loop through segments
			mprintc(--j, i, *str);
#endif
}

void mprints(uint8_t pos, uint8_t disp, char *str){
#if DISP_NUM == 1
	if(pos > 3) return;
	for(uint8_t i = pos; i > 0; str++)
		printc(--i, *str);
#else
	// Loop through displays and set flag when it's time to print on second display
	for(uint8_t i = disp, k; i <= DISP_NUM; i++, k = 1)
		// Loop through segments. If k equal to 1 then print char on the second display at segment 3
		for(uint8_t j = ((k) ? (4) : (pos + 1)); j > 0;)
			mprintc(--j, i, *str++);
#endif
}

void clear(){
#if DISP_NUM == 1
	for(uint8_t i = 4; i > 0;)
		printc(--i, 0x20);
#else
	for(uint8_t i = 1; i <= DISP_NUM; i++)					// Loop through display numbers
		for(uint8_t j = 4; j > 0;)							// Loop through segments
			mprintc(--j, i, 0x20);
#endif
}
