/*
  hcsr04.h - utilities for working with the HC SR-04
  ultrasound ranging module.
  
  Copyright 2015 Mikael Forsberg <miforsb@kth.se>
  
  License: GPLv3
*/

// this is more or less a copy of the pulseIn arduino/MPIDE function
unsigned int hcsr04_poll(volatile unsigned int* trig_port, unsigned int trig_pinmask, volatile unsigned int* echo_port, unsigned int echo_pinmask)
{
    unsigned int timeout = 50000;
    unsigned int length = 0;
    int i;
    
    while (((*echo_port) & echo_pinmask) != 0)
    {
        if (--timeout <= 0)
        {
            return 13;
        }
    }
    
    (*trig_port) &= ~trig_pinmask;
    (*trig_port) |= trig_pinmask;
    for (i = 0; i < 40; ++i);
    (*trig_port) &= ~trig_pinmask;
    
    while (((*echo_port) & echo_pinmask) == 0)
    {
        if (--timeout <= 0)
        {
            return 17;
        }
    }
    
    while (((*echo_port) & echo_pinmask) != 0)
    {
        ++length;
        
        if (--timeout <= 0)
        {
            return 19;
        }
    }
    
    return length;
}
