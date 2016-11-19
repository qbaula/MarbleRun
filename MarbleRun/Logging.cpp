#include <Windows.h>
#include <strsafe.h>
#include "Logging.h"

void Logging::log(const wchar_t *fmt ...) {
	/*
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	*/

	wchar_t szBuff[1024];
    va_list arg;

    va_start(arg, fmt);
    _vsnwprintf_s(szBuff, sizeof(szBuff) - 1, fmt, arg);
    va_end(arg);

    OutputDebugString(szBuff);
}
