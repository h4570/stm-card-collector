#include "FatFs/ff.h"

DWORD get_fattime(void)
{
    return ((DWORD)(2023 - 1980) << 25) // Rok 2023
           | ((DWORD)5 << 21)           // Miesiąc 5
           | ((DWORD)5 << 16)           // Dzień 5
           | ((DWORD)6 << 11)           // Godzina 6
           | ((DWORD)0 << 5)            // Minuta 0
           | ((DWORD)0 >> 1);           // Sekunda 0
}