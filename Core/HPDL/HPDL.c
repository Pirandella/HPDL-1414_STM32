#include "HPDL.h"

void printc(uint8_t pos, char ch){
	_WR_1;
#if defined(DIFF_PORT)
	ADDR(pos);
	DATA(ch);
#elif defined(SAME_PORT)
	WRITE(pos, ch);
#endif
	_WR_0;
	_WR_1;
}

void mprintc(uint8_t pos, uint8_t disp, char ch){
	_WR_1_;
#if defined(DIFF_PORT)
	ADDR(pos);
	DATA(ch);
#elif defined(SAME_PORT)
	WRITE(pos, ch);
#endif
	_WR_0_(disp);
	_WR_1_;
}

void prints(char *str){
#if DISP_NUM == 1
	uint8_t i = 4;
	while(*str)
		printc(--i, ((*str > 0x5F) ? (*(str++) - 0x20) : (*(str++))));
#else // Multiple displays
	for(uint8_t i = 1; i <= DISP_NUM; i++)
		for(uint8_t j = 4; j > 0;)
			mprintc(--j, i, ((*str > 0x5F) ? (*(str++) - 0x20) : (*(str++))));
#endif
}

void mprints(uint8_t pos, char *str){
#if DISP_NUM == 1

#else

#endif
}

void clear(){
#if DISP_NUM == 1
	uint8_t i = 4;
	while(*(str++))
		printc(--i, 0x20);
#else
	for(uint8_t i = 1; i <= DISP_NUM; i++)
		for(uint8_t j = 4; j > 0;)
			mprintc(--j, i, 0x20);
#endif
}
