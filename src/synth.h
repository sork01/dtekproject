#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>

#define SYNTH_WAVE_TRIANGLE 0
#define SYNTH_WAVE_SINE 1
#define SYNTH_WAVE_SAW 2
#define SYNTH_WAVE_SQUARE 3

#define SYNTH_PI 3.1415927f
#define SYNTH_TWOPI 6.2831853f

#define SYNTH_NOTE_C0      16.35f
#define SYNTH_NOTE_CIS0    17.32f
#define SYNTH_NOTE_D0      18.35f
#define SYNTH_NOTE_DIS0    19.45f
#define SYNTH_NOTE_E0      20.60f
#define SYNTH_NOTE_F0      21.83f
#define SYNTH_NOTE_FIS0    23.12f
#define SYNTH_NOTE_G0      24.50f
#define SYNTH_NOTE_GIS0    25.96f
#define SYNTH_NOTE_A0      27.50f
#define SYNTH_NOTE_AIS0    29.14f
#define SYNTH_NOTE_B0      30.87f
#define SYNTH_NOTE_C1      32.70f
#define SYNTH_NOTE_CIS1    34.65f
#define SYNTH_NOTE_D1      36.71f
#define SYNTH_NOTE_DIS1    38.89f
#define SYNTH_NOTE_E1      41.20f
#define SYNTH_NOTE_F1      43.65f
#define SYNTH_NOTE_FIS1    46.25f
#define SYNTH_NOTE_G1      49.00f
#define SYNTH_NOTE_GIS1    51.91f
#define SYNTH_NOTE_A1      55.00f
#define SYNTH_NOTE_AIS1    58.27f
#define SYNTH_NOTE_B1      61.74f
#define SYNTH_NOTE_C2      65.41f
#define SYNTH_NOTE_CIS2    69.30f
#define SYNTH_NOTE_D2      73.42f
#define SYNTH_NOTE_DIS2    77.78f
#define SYNTH_NOTE_E2      82.41f
#define SYNTH_NOTE_F2      87.31f
#define SYNTH_NOTE_FIS2    92.50f
#define SYNTH_NOTE_G2      98.00f
#define SYNTH_NOTE_GIS2    103.83f
#define SYNTH_NOTE_A2      110.00f
#define SYNTH_NOTE_AIS2    116.54f
#define SYNTH_NOTE_B2      123.47f
#define SYNTH_NOTE_C3      130.81f
#define SYNTH_NOTE_CIS3    138.59f
#define SYNTH_NOTE_D3      146.83f
#define SYNTH_NOTE_DIS3    155.56f
#define SYNTH_NOTE_E3      164.81f
#define SYNTH_NOTE_F3      174.61f
#define SYNTH_NOTE_FIS3    185.00f
#define SYNTH_NOTE_G3      196.00f
#define SYNTH_NOTE_GIS3    207.65f
#define SYNTH_NOTE_A3      220.00f
#define SYNTH_NOTE_AIS3    233.08f
#define SYNTH_NOTE_B3      246.94f
#define SYNTH_NOTE_C4      261.63f
#define SYNTH_NOTE_CIS4    277.18f
#define SYNTH_NOTE_D4      293.66f
#define SYNTH_NOTE_DIS4    311.13f
#define SYNTH_NOTE_E4      329.63f
#define SYNTH_NOTE_F4      349.23f
#define SYNTH_NOTE_FIS4    369.99f
#define SYNTH_NOTE_G4      392.00f
#define SYNTH_NOTE_GIS4    415.30f
#define SYNTH_NOTE_A4      440.00f
#define SYNTH_NOTE_AIS4    466.16f
#define SYNTH_NOTE_B4      493.88f
#define SYNTH_NOTE_C5      523.25f
#define SYNTH_NOTE_CIS5    554.37f
#define SYNTH_NOTE_D5      587.33f
#define SYNTH_NOTE_DIS5    622.25f
#define SYNTH_NOTE_E5      659.25f
#define SYNTH_NOTE_F5      698.46f
#define SYNTH_NOTE_FIS5    739.99f
#define SYNTH_NOTE_G5      783.99f
#define SYNTH_NOTE_GIS5    830.61f
#define SYNTH_NOTE_A5      880.00f
#define SYNTH_NOTE_AIS5    932.33f
#define SYNTH_NOTE_B5      987.77f
#define SYNTH_NOTE_C6      1046.50f
#define SYNTH_NOTE_CIS6    1108.73f
#define SYNTH_NOTE_D6      1174.66f
#define SYNTH_NOTE_DIS6    1244.51f
#define SYNTH_NOTE_E6      1318.51f
#define SYNTH_NOTE_F6      1396.91f
#define SYNTH_NOTE_FIS6    1479.98f
#define SYNTH_NOTE_G6      1567.98f
#define SYNTH_NOTE_GIS6    1661.22f
#define SYNTH_NOTE_A6      1760.00f
#define SYNTH_NOTE_AIS6    1864.66f
#define SYNTH_NOTE_B6      1975.53f
#define SYNTH_NOTE_C7      2093.00f
#define SYNTH_NOTE_CIS7    2217.46f
#define SYNTH_NOTE_D7      2349.32f
#define SYNTH_NOTE_DIS7    2489.02f
#define SYNTH_NOTE_E7      2637.02f
#define SYNTH_NOTE_F7      2793.83f
#define SYNTH_NOTE_FIS7    2959.96f
#define SYNTH_NOTE_G7      3135.96f
#define SYNTH_NOTE_GIS7    3322.44f
#define SYNTH_NOTE_A7      3520.00f
#define SYNTH_NOTE_AIS7    3729.31f
#define SYNTH_NOTE_B7      3951.07f
#define SYNTH_NOTE_C8      4186.01f
#define SYNTH_NOTE_CIS8    4434.92f
#define SYNTH_NOTE_D8      4698.63f
#define SYNTH_NOTE_DIS8    4978.03f
#define SYNTH_NOTE_E8      5274.04f
#define SYNTH_NOTE_F8      5587.65f
#define SYNTH_NOTE_FIS8    5919.91f
#define SYNTH_NOTE_G8      6271.93f
#define SYNTH_NOTE_GIS8    6644.88f
#define SYNTH_NOTE_A8      7040.00f
#define SYNTH_NOTE_AIS8    7458.62f
#define SYNTH_NOTE_B8      7902.13f

#define SYNTH_IDX_NOTE_C0      0
#define SYNTH_IDX_NOTE_CIS0    1
#define SYNTH_IDX_NOTE_D0      2
#define SYNTH_IDX_NOTE_DIS0    3
#define SYNTH_IDX_NOTE_E0      4
#define SYNTH_IDX_NOTE_F0      5
#define SYNTH_IDX_NOTE_FIS0    6
#define SYNTH_IDX_NOTE_G0      7
#define SYNTH_IDX_NOTE_GIS0    8
#define SYNTH_IDX_NOTE_A0      9
#define SYNTH_IDX_NOTE_AIS0    10
#define SYNTH_IDX_NOTE_B0      11
#define SYNTH_IDX_NOTE_C1      12
#define SYNTH_IDX_NOTE_CIS1    13
#define SYNTH_IDX_NOTE_D1      14
#define SYNTH_IDX_NOTE_DIS1    15
#define SYNTH_IDX_NOTE_E1      16
#define SYNTH_IDX_NOTE_F1      17
#define SYNTH_IDX_NOTE_FIS1    18
#define SYNTH_IDX_NOTE_G1      19
#define SYNTH_IDX_NOTE_GIS1    20
#define SYNTH_IDX_NOTE_A1      21
#define SYNTH_IDX_NOTE_AIS1    22
#define SYNTH_IDX_NOTE_B1      23
#define SYNTH_IDX_NOTE_C2      24
#define SYNTH_IDX_NOTE_CIS2    25
#define SYNTH_IDX_NOTE_D2      26
#define SYNTH_IDX_NOTE_DIS2    27
#define SYNTH_IDX_NOTE_E2      28
#define SYNTH_IDX_NOTE_F2      29
#define SYNTH_IDX_NOTE_FIS2    30
#define SYNTH_IDX_NOTE_G2      31
#define SYNTH_IDX_NOTE_GIS2    32
#define SYNTH_IDX_NOTE_A2      33
#define SYNTH_IDX_NOTE_AIS2    34
#define SYNTH_IDX_NOTE_B2      35
#define SYNTH_IDX_NOTE_C3      36
#define SYNTH_IDX_NOTE_CIS3    37
#define SYNTH_IDX_NOTE_D3      38
#define SYNTH_IDX_NOTE_DIS3    39
#define SYNTH_IDX_NOTE_E3      40
#define SYNTH_IDX_NOTE_F3      41
#define SYNTH_IDX_NOTE_FIS3    42
#define SYNTH_IDX_NOTE_G3      43
#define SYNTH_IDX_NOTE_GIS3    44
#define SYNTH_IDX_NOTE_A3      45
#define SYNTH_IDX_NOTE_AIS3    46
#define SYNTH_IDX_NOTE_B3      47
#define SYNTH_IDX_NOTE_C4      48
#define SYNTH_IDX_NOTE_CIS4    49
#define SYNTH_IDX_NOTE_D4      50
#define SYNTH_IDX_NOTE_DIS4    51
#define SYNTH_IDX_NOTE_E4      52
#define SYNTH_IDX_NOTE_F4      53
#define SYNTH_IDX_NOTE_FIS4    54
#define SYNTH_IDX_NOTE_G4      55
#define SYNTH_IDX_NOTE_GIS4    56
#define SYNTH_IDX_NOTE_A4      57
#define SYNTH_IDX_NOTE_AIS4    58
#define SYNTH_IDX_NOTE_B4      59
#define SYNTH_IDX_NOTE_C5      60
#define SYNTH_IDX_NOTE_CIS5    61
#define SYNTH_IDX_NOTE_D5      62
#define SYNTH_IDX_NOTE_DIS5    63
#define SYNTH_IDX_NOTE_E5      64
#define SYNTH_IDX_NOTE_F5      65
#define SYNTH_IDX_NOTE_FIS5    66
#define SYNTH_IDX_NOTE_G5      67
#define SYNTH_IDX_NOTE_GIS5    68
#define SYNTH_IDX_NOTE_A5      69
#define SYNTH_IDX_NOTE_AIS5    70
#define SYNTH_IDX_NOTE_B5      71
#define SYNTH_IDX_NOTE_C6      72
#define SYNTH_IDX_NOTE_CIS6    73
#define SYNTH_IDX_NOTE_D6      74
#define SYNTH_IDX_NOTE_DIS6    75
#define SYNTH_IDX_NOTE_E6      76
#define SYNTH_IDX_NOTE_F6      77
#define SYNTH_IDX_NOTE_FIS6    78
#define SYNTH_IDX_NOTE_G6      79
#define SYNTH_IDX_NOTE_GIS6    80
#define SYNTH_IDX_NOTE_A6      81
#define SYNTH_IDX_NOTE_AIS6    82
#define SYNTH_IDX_NOTE_B6      83
#define SYNTH_IDX_NOTE_C7      84
#define SYNTH_IDX_NOTE_CIS7    85
#define SYNTH_IDX_NOTE_D7      86
#define SYNTH_IDX_NOTE_DIS7    87
#define SYNTH_IDX_NOTE_E7      88
#define SYNTH_IDX_NOTE_F7      89
#define SYNTH_IDX_NOTE_FIS7    90
#define SYNTH_IDX_NOTE_G7      91
#define SYNTH_IDX_NOTE_GIS7    92
#define SYNTH_IDX_NOTE_A7      93
#define SYNTH_IDX_NOTE_AIS7    94
#define SYNTH_IDX_NOTE_B7      95
#define SYNTH_IDX_NOTE_C8      96
#define SYNTH_IDX_NOTE_CIS8    97
#define SYNTH_IDX_NOTE_D8      98
#define SYNTH_IDX_NOTE_DIS8    99
#define SYNTH_IDX_NOTE_E8      100
#define SYNTH_IDX_NOTE_F8      101
#define SYNTH_IDX_NOTE_FIS8    102
#define SYNTH_IDX_NOTE_G8      103
#define SYNTH_IDX_NOTE_GIS8    104
#define SYNTH_IDX_NOTE_A8      105
#define SYNTH_IDX_NOTE_AIS8    106
#define SYNTH_IDX_NOTE_B8      107

#define SYNTH_SCALE_KEYS 0
#define SYNTH_SCALE_MAJOR 1
#define SYNTH_SCALE_MINOR 2
#define SYNTH_SCALE_PENTATONIC 3

float synth_notes_keys[108];
float synth_notes_major[63];
float synth_notes_minor[63];
float synth_notes_pentatonic[45];

#define SYNTH_NUM_SINES 256
float sines[SYNTH_NUM_SINES];

typedef struct synth
{
    uint8_t shape;
    float frequency;
    float target_freq;
    float freq_smoothing;
    float amplitude;
    float target_amp;
    float amp_smoothing;
    float phase;
    uint8_t signal;
} synth_t;

typedef struct synth_song
{
    uint16_t tickdelay;
    uint16_t nexttick;
    synth_t syn1;
    uint16_t length;
    uint16_t tick;
    char chn1[128];
    char amp1[128];
    char len1[128];
} synth_song_t;

synth_song_t synth_songs[2];

void synth_init(synth_t* dest, uint8_t shape, float freq, float freq_smooth, float amp, float amp_smooth);
void synth_step(synth_t* dest, float samplerate);
void synth_step_song(synth_song_t* song, float samplerate);
void synth_load_song1();
void synth_load_song2();
void synth_set_closest_note(synth_t* dest, int scale);

#endif
