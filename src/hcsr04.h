/*
  hcsr04.h - utilities for working with the HC SR-04
  ultrasound ranging module.
  
  Copyright 2015 Mikael Forsberg <miforsb@kth.se>
  
  License: GPLv3
*/

#ifndef HCSR04_H
#define HCSR04_H

// this is more or less a copy of the pulseIn arduino/MPIDE function
unsigned int hcsr04_poll(volatile unsigned int* trig_port, unsigned int trig_pinmask, volatile unsigned int* echo_port, unsigned int echo_pinmask);

#endif
