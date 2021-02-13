/*
  PICmin - digital theremin
  
  Copyright 2015 Mikael Forsberg <miforsb@kth.se>
  Copyright 2015 Robin Gunning <rgunning@kth.se>
  
  License: GPLv3
*/

#include <stdint.h>
#include <pic32mx.h>

#include "ioshield.h"
#include "ioshield_switches.h"
#include "hcsr04.h"
#include "synth.h"

// pitch trig on PORTD, RD2
#define PORT_PITCH_TRIG (volatile unsigned int*) 0xBF8860D0
#define PORT_PITCH_TRIG_CTRL TRISD
#define PIN_PITCH_TRIG 0b000000000100

// pitch echo on PORTD, RD9
#define PORT_PITCH_ECHO (volatile unsigned int*) 0xBF8860D0
#define PORT_PITCH_ECHO_CTRL TRISD
#define PIN_PITCH_ECHO 0b001000000000

// amp trig on PORTD, RD1
#define PORT_AMP_TRIG (volatile unsigned int*) 0xBF886150
#define PORT_AMP_TRIG_CTRL TRISF
#define PIN_AMP_TRIG 0b000000000010

// amp echo on RF1, PORTF
#define PORT_AMP_ECHO (volatile unsigned int*) 0xBF8860D0
#define PORT_AMP_ECHO_CTRL TRISD
#define PIN_AMP_ECHO 0b000000000010

#define THEREMIN_SCALE_FREE 255
#define THEREMIN_SCALE_KEYS SYNTH_SCALE_KEYS
#define THEREMIN_SCALE_MAJOR SYNTH_SCALE_MAJOR
#define THEREMIN_SCALE_MINOR SYNTH_SCALE_MINOR
#define THEREMIN_SCALE_PENTATONIC SYNTH_SCALE_PENTATONIC

unsigned int theremin_pitch;
unsigned int theremin_amp;
unsigned int theremin_scale;

unsigned int poll_interval;
unsigned int poll_count;
unsigned int poll_enabled;

unsigned int shapebuttonwait;
unsigned int scalebuttonwait;
unsigned int songbuttonwait;

synth_t theremin;
synth_song_t* song;

void user_isr()
{
    synth_step(&theremin, 10000);
    // Play theremin with song or just theremin 
    if (song != 0)
    {
        synth_step_song(song, 10000);
        PORTE = (PORTE & 0xffffff00) | (theremin.signal + (*song).syn1.signal);
    }
    else
    {
        PORTE = (PORTE & 0xffffff00) | theremin.signal;
    }
    
    ++poll_count;
    
    if (poll_count == poll_interval)
    {
        poll_count = 0;
        poll_enabled = 1;
    }
    
    IFS(0) &= 0xeff;
}

int main()
{
    ioshield_setup();
    ioshield_display_init();
    
    poll_interval = 1000;
    poll_count = 0;
    poll_enabled = 0;
    
    shapebuttonwait = 0;
    scalebuttonwait = 0;
    
    synth_load_song1();
    synth_load_song2();
    synth_load_song3();
    song = 0;
    
    theremin_pitch = 0;
    theremin_amp = 0;
    theremin_scale = THEREMIN_SCALE_FREE;
    
    // initialize theremin with waveform, frequency, frequency smoothing, amplification, amplification smoothing
    synth_init(&theremin, SYNTH_WAVE_TRIANGLE, 440.0f, 1000.0f, 0.0f, 1000.0f);
    
    PORT_PITCH_TRIG_CTRL &= ~PIN_PITCH_TRIG;
    PORT_PITCH_ECHO_CTRL |= PIN_PITCH_ECHO;
    
    PORT_AMP_TRIG_CTRL &= ~PIN_AMP_TRIG;
    PORT_AMP_ECHO_CTRL |= PIN_AMP_ECHO;
    
    // RE0 ... RE7 as outputs
    TRISE = 0;
    
    // configure timer 2 for 10khz interrupts
    // T2CON = 0b 1000 0000 0000 0000;
    T2CON = 0x8000;
    PR2 = 8000;
    TMR2 = 0;
    // IFS(0) &= 0b 1110 1111 1111;
    IFS(0) &= 0xeff;
    asm("ei"); // enable interrupts
    IEC(0) |= 0x100; // timer2 interrupt enable, enable index 8
    IPC(2) |= 0x1f;  // timer2 interrupt priority, enable highest priority
    
    while (1)
    {
        if (poll_enabled)
        {
            int buttons = ioshield_get_buttons();
            
            if (buttons != 0) // some button is pressed
            {
                // Change waveform 
                if (buttons & 0b1000) // pressed button 4
                {
                    if (shapebuttonwait == 0)
                    {
                        switch (theremin.shape)
                        {
                            case SYNTH_WAVE_TRIANGLE:
                                theremin.shape = SYNTH_WAVE_SINE;
                                break;
                            
                            case SYNTH_WAVE_SINE:
                                theremin.shape = SYNTH_WAVE_SAW;
                                break;
                            
                            case SYNTH_WAVE_SAW:
                                theremin.shape = SYNTH_WAVE_SQUARE;
                                break;
                            
                            case SYNTH_WAVE_SQUARE:
                                theremin.shape = SYNTH_WAVE_TRIANGLE;
                                break;
                            
                            default:
                                break;
                        }
                    }
                    
                    shapebuttonwait = 1;
                }
                
                // Change snap to notes
                if (buttons & 0b0100) // pressed button 3
                {
                    if (scalebuttonwait == 0)
                    {
                        switch (theremin_scale)
                        {
                            case THEREMIN_SCALE_FREE:
                                theremin_scale = THEREMIN_SCALE_KEYS;
                                break;
                            
                            case THEREMIN_SCALE_KEYS:
                                theremin_scale = THEREMIN_SCALE_MAJOR;
                                break;
                            
                            case THEREMIN_SCALE_MAJOR:
                                theremin_scale = THEREMIN_SCALE_MINOR;
                                break;
                            
                            case THEREMIN_SCALE_MINOR:
                                theremin_scale = THEREMIN_SCALE_PENTATONIC;
                                break;
                            
                            case THEREMIN_SCALE_PENTATONIC:
                                theremin_scale = THEREMIN_SCALE_FREE;
                                break;
                            
                            default:
                                break;
                        }
                    }
                    
                    scalebuttonwait = 1;
                }
                
                // Change song
                if (buttons & 0b0010) // pressed button 2
                {
                    if (songbuttonwait == 0)
                    {
                        if (song == 0)
                        {
                            song = &synth_songs[0];
                        }
                        else if (song == &synth_songs[0])
                        {
                            song = &synth_songs[1];
                        }
                        else if (song == &synth_songs[1])
                        {
                            song = 0;
                        }
                        // else if (song == &synth_songs[2])
                        // {
                            // song = 0;
                        // }
                    }
                    
                    songbuttonwait = 1;
                }
            }
            else
            {
                shapebuttonwait = 0;
                scalebuttonwait = 0;
                songbuttonwait = 0;
            }
            
            poll_enabled = 0;
            
            theremin_pitch = hcsr04_poll(PORT_PITCH_TRIG, PIN_PITCH_TRIG,
                PORT_PITCH_ECHO, PIN_PITCH_ECHO);
            
            theremin_amp = hcsr04_poll(PORT_AMP_TRIG, PIN_AMP_TRIG,
                PORT_AMP_ECHO, PIN_AMP_ECHO);

            // Only change pitch within this ultrasonic range            
            if (theremin_pitch > 1000 && theremin_pitch < 12000)
            {
                theremin.target_freq = ((float) theremin_pitch) / 6.0f;
                
                // Snap to closest note
                if (theremin_scale != THEREMIN_SCALE_FREE)
                {
                    synth_set_closest_note(&theremin, theremin_scale);
                }
                // Only change amp within this ultrasonic range
                if (theremin_amp > 1000 && theremin_amp < 12000)
                {
                    theremin.target_amp = 0.5f * (((float) theremin_amp - 1000) / 11000.0f);
                }
                else
                {
                    theremin.target_amp = 0.5f;
                }
            }
            else
            {
                theremin.target_amp = 0.0f;
            }
            
            // ioshield_display_string(1, ioshield_itoa(theremin_pitch));
            // ioshield_display_string(2, ioshield_itoa(theremin_amp));
            
            switch (theremin.shape)
            {
                // Waveforms
                case SYNTH_WAVE_TRIANGLE:
                    ioshield_display_string(1, "WAVE: TRIANGLE");
                    break;
                
                case SYNTH_WAVE_SINE:
                    ioshield_display_string(1, "WAVE: SINE");
                    break;
                
                case SYNTH_WAVE_SAW:
                    ioshield_display_string(1, "WAVE: SAWTOOTH");
                    break;
                
                case SYNTH_WAVE_SQUARE:
                    ioshield_display_string(1, "WAVE: SQUARE");
                    break;
                
                default:
                    break;
            }
            
            switch (theremin_scale)
            {
                // Scale
                case THEREMIN_SCALE_FREE:
                    ioshield_display_string(2, "SCALE: FREE");
                    break;
                
                case THEREMIN_SCALE_KEYS:
                    ioshield_display_string(2, "SCALE: KEYS");
                    break;
                
                case THEREMIN_SCALE_MAJOR:
                    ioshield_display_string(2, "SCALE: MAJOR");
                    break;
                
                case THEREMIN_SCALE_MINOR:
                    ioshield_display_string(2, "SCALE: MINOR");
                    break;
                
                case THEREMIN_SCALE_PENTATONIC:
                    ioshield_display_string(2, "SCALE: PENTA");
                    break;
                
                default:
                    break;
            }
            
            ioshield_display_update();
        }
    }
    
    return 0;
}

