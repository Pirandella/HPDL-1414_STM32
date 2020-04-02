#include "HPDL.h"

// This array is used to ease the addressing segments
static uint8_t map[4 * DISP_NUM];

void hpdl_init(){
	uint8_t *pmap = map;
	for(uint8_t i = 0; i < DISP_NUM; i++)
		for(uint8_t j = 4; j > 0;)
			*(pmap++) = --j;
}
/*-----------------------------------------------------------------------------------------------------*/
void hpdl_printc(uint8_t pos, char ch){
	if(ch < 0x20) return;									// Check for non printable characters
	if(ch > 0x5F) ch -= 0x20;								// Convert lower case letter to upper case
	uint8_t disp = (((pos) ? (pos) : (1)) >> 2) + 1;		// Get display number
	pos = map[pos];											// Remap global position to local
	WRITE(pos, disp, ch);
}
/*-----------------------------------------------------------------------------------------------------*/
void hpdl_prints(uint8_t pos, char *str){
	while(*str)
		hpdl_printc(pos++, *(str++));
}
/*-----------------------------------------------------------------------------------------------------*/
void hpdl_clear(){
	for(uint8_t i = 0; i < (4 * DISP_NUM); i++)
		hpdl_printc(i, 0x20);
}
