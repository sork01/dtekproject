#include "ioshield_switches.h"
#include <pic32mx.h>

int ioshield_get_switches()
{
    return ((PORTD & 0xf00) >> 8);
}

int ioshield_get_buttons()
{
    return ((PORTD & 0xe0) >> 4) | ((PORTF & 0x2) >> 1);
}
