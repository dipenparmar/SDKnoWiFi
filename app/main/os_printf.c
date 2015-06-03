/******************************************************************************
 * FileName: os_printf.c
 * Description: Alternate SDK (libmain.a)
 * Author: PV`
 * (c) PV` 2015
 * ver 0.0.1
*******************************************************************************/
#include "bios.h"
#include <stdarg.h>

//extern uint8 _mem_buf[2924]; // ������ ����� � ������� RAM_BIOS: 0x3FFFE360..0x3FFFEA80 [1824 ����]
extern char * _sprintf_buf;  // 0x3FFFE360
extern char print_mem_buf[1820]; // 0x3FFFE364..0x3FFFEA80
//=============================================================================
// FLASH code (ICACHE_FLASH_ATTR)
//=============================================================================
//=============================================================================
// int os_printf_plus(const char *format, ...)
// ���������� ����� � ������� RAM-BIOS
//-----------------------------------------------------------------------------
int ICACHE_FLASH_ATTR os_printf_plus(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int i = ets_vprintf(ets_write_char, ((uint32)format >= 0x40200000)? ets_strcpy(print_mem_buf, format) : format, args);
	va_end (args);
	return i;
}
//=============================================================================
// int os_sprintf_plus(char *str, const char *format, ...)
// ���������� ����� � ������� RAM-BIOS
//-----------------------------------------------------------------------------
void ICACHE_FLASH_ATTR _sprintf_out(char c)
{
	if(_sprintf_buf != NULL) *_sprintf_buf++ = c;
}

int ICACHE_FLASH_ATTR os_sprintf_plus(char *str, const char *format, ...)
{
	_sprintf_buf = str;
	va_list args;
	va_start(args, format);
	int i = ets_vprintf(_sprintf_out, ((uint32)format >= 0x40200000)? ets_strcpy(print_mem_buf, format) : format, args);
	va_end (args);
	return i;
}

