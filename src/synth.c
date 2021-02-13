/*
  Copyright 2015 Mikael Forsberg <miforsb@kth.se>
  Copyright 2015 Robin Gunning <rgunning@kth.se>
  
  License: GPLv3

  Synth module
*/


#include "synth.h"
#include <stdint.h>

// Notes
float synth_notes_keys[108] = {
SYNTH_NOTE_C0, SYNTH_NOTE_CIS0, SYNTH_NOTE_D0, SYNTH_NOTE_DIS0, SYNTH_NOTE_E0, SYNTH_NOTE_F0,
SYNTH_NOTE_FIS0, SYNTH_NOTE_G0, SYNTH_NOTE_GIS0, SYNTH_NOTE_A0, SYNTH_NOTE_AIS0, SYNTH_NOTE_B0,
SYNTH_NOTE_C1, SYNTH_NOTE_CIS1, SYNTH_NOTE_D1, SYNTH_NOTE_DIS1, SYNTH_NOTE_E1, SYNTH_NOTE_F1,
SYNTH_NOTE_FIS1, SYNTH_NOTE_G1, SYNTH_NOTE_GIS1, SYNTH_NOTE_A1, SYNTH_NOTE_AIS1, SYNTH_NOTE_B1,
SYNTH_NOTE_C2, SYNTH_NOTE_CIS2, SYNTH_NOTE_D2, SYNTH_NOTE_DIS2, SYNTH_NOTE_E2, SYNTH_NOTE_F2,
SYNTH_NOTE_FIS2, SYNTH_NOTE_G2, SYNTH_NOTE_GIS2, SYNTH_NOTE_A2, SYNTH_NOTE_AIS2, SYNTH_NOTE_B2,
SYNTH_NOTE_C3, SYNTH_NOTE_CIS3, SYNTH_NOTE_D3, SYNTH_NOTE_DIS3, SYNTH_NOTE_E3, SYNTH_NOTE_F3,
SYNTH_NOTE_FIS3, SYNTH_NOTE_G3, SYNTH_NOTE_GIS3, SYNTH_NOTE_A3, SYNTH_NOTE_AIS3, SYNTH_NOTE_B3,
SYNTH_NOTE_C4, SYNTH_NOTE_CIS4, SYNTH_NOTE_D4, SYNTH_NOTE_DIS4, SYNTH_NOTE_E4, SYNTH_NOTE_F4,
SYNTH_NOTE_FIS4, SYNTH_NOTE_G4, SYNTH_NOTE_GIS4, SYNTH_NOTE_A4, SYNTH_NOTE_AIS4, SYNTH_NOTE_B4,
SYNTH_NOTE_C5, SYNTH_NOTE_CIS5, SYNTH_NOTE_D5, SYNTH_NOTE_DIS5, SYNTH_NOTE_E5, SYNTH_NOTE_F5,
SYNTH_NOTE_FIS5, SYNTH_NOTE_G5, SYNTH_NOTE_GIS5, SYNTH_NOTE_A5, SYNTH_NOTE_AIS5, SYNTH_NOTE_B5,
SYNTH_NOTE_C6, SYNTH_NOTE_CIS6, SYNTH_NOTE_D6, SYNTH_NOTE_DIS6, SYNTH_NOTE_E6, SYNTH_NOTE_F6,
SYNTH_NOTE_FIS6, SYNTH_NOTE_G6, SYNTH_NOTE_GIS6, SYNTH_NOTE_A6, SYNTH_NOTE_AIS6, SYNTH_NOTE_B6,
SYNTH_NOTE_C7, SYNTH_NOTE_CIS7, SYNTH_NOTE_D7, SYNTH_NOTE_DIS7, SYNTH_NOTE_E7, SYNTH_NOTE_F7,
SYNTH_NOTE_FIS7, SYNTH_NOTE_G7, SYNTH_NOTE_GIS7, SYNTH_NOTE_A7, SYNTH_NOTE_AIS7, SYNTH_NOTE_B7,
SYNTH_NOTE_C8, SYNTH_NOTE_CIS8, SYNTH_NOTE_D8, SYNTH_NOTE_DIS8, SYNTH_NOTE_E8, SYNTH_NOTE_F8,
SYNTH_NOTE_FIS8, SYNTH_NOTE_G8, SYNTH_NOTE_GIS8, SYNTH_NOTE_A8, SYNTH_NOTE_AIS8, SYNTH_NOTE_B8};

// Notes for major scale
float synth_notes_major[63] = {
SYNTH_NOTE_C0, SYNTH_NOTE_D0, SYNTH_NOTE_E0, SYNTH_NOTE_F0, SYNTH_NOTE_G0, SYNTH_NOTE_A0, SYNTH_NOTE_B0,
SYNTH_NOTE_C1, SYNTH_NOTE_D1, SYNTH_NOTE_E1, SYNTH_NOTE_F1, SYNTH_NOTE_G1, SYNTH_NOTE_A1, SYNTH_NOTE_B1,
SYNTH_NOTE_C2, SYNTH_NOTE_D2, SYNTH_NOTE_E2, SYNTH_NOTE_F2, SYNTH_NOTE_G2, SYNTH_NOTE_A2, SYNTH_NOTE_B2,
SYNTH_NOTE_C3, SYNTH_NOTE_D3, SYNTH_NOTE_E3, SYNTH_NOTE_F3, SYNTH_NOTE_G3, SYNTH_NOTE_A3, SYNTH_NOTE_B3,
SYNTH_NOTE_C4, SYNTH_NOTE_D4, SYNTH_NOTE_E4, SYNTH_NOTE_F4, SYNTH_NOTE_G4, SYNTH_NOTE_A4, SYNTH_NOTE_B4,
SYNTH_NOTE_C5, SYNTH_NOTE_D5, SYNTH_NOTE_E5, SYNTH_NOTE_F5, SYNTH_NOTE_G5, SYNTH_NOTE_A5, SYNTH_NOTE_B5,
SYNTH_NOTE_C6, SYNTH_NOTE_D6, SYNTH_NOTE_E6, SYNTH_NOTE_F6, SYNTH_NOTE_G6, SYNTH_NOTE_A6, SYNTH_NOTE_B6,
SYNTH_NOTE_C7, SYNTH_NOTE_D7, SYNTH_NOTE_E7, SYNTH_NOTE_F7, SYNTH_NOTE_G7, SYNTH_NOTE_A7, SYNTH_NOTE_B7,
SYNTH_NOTE_C8, SYNTH_NOTE_D8, SYNTH_NOTE_E8, SYNTH_NOTE_F8, SYNTH_NOTE_G8, SYNTH_NOTE_A8, SYNTH_NOTE_B8};

// Notes for minor scale
float synth_notes_minor[63] = {
SYNTH_NOTE_C0, SYNTH_NOTE_D0, SYNTH_NOTE_DIS0, SYNTH_NOTE_F0, SYNTH_NOTE_G0, SYNTH_NOTE_GIS0, SYNTH_NOTE_AIS0,
SYNTH_NOTE_C1, SYNTH_NOTE_D1, SYNTH_NOTE_DIS1, SYNTH_NOTE_F1, SYNTH_NOTE_G1, SYNTH_NOTE_GIS1, SYNTH_NOTE_AIS1,
SYNTH_NOTE_C2, SYNTH_NOTE_D2, SYNTH_NOTE_DIS2, SYNTH_NOTE_F2, SYNTH_NOTE_G2, SYNTH_NOTE_GIS2, SYNTH_NOTE_AIS2,
SYNTH_NOTE_C3, SYNTH_NOTE_D3, SYNTH_NOTE_DIS3, SYNTH_NOTE_F3, SYNTH_NOTE_G3, SYNTH_NOTE_GIS3, SYNTH_NOTE_AIS3,
SYNTH_NOTE_C4, SYNTH_NOTE_D4, SYNTH_NOTE_DIS4, SYNTH_NOTE_F4, SYNTH_NOTE_G4, SYNTH_NOTE_GIS4, SYNTH_NOTE_AIS4,
SYNTH_NOTE_C5, SYNTH_NOTE_D5, SYNTH_NOTE_DIS5, SYNTH_NOTE_F5, SYNTH_NOTE_G5, SYNTH_NOTE_GIS5, SYNTH_NOTE_AIS5,
SYNTH_NOTE_C6, SYNTH_NOTE_D6, SYNTH_NOTE_DIS6, SYNTH_NOTE_F6, SYNTH_NOTE_G6, SYNTH_NOTE_GIS6, SYNTH_NOTE_AIS6,
SYNTH_NOTE_C7, SYNTH_NOTE_D7, SYNTH_NOTE_DIS7, SYNTH_NOTE_F7, SYNTH_NOTE_G7, SYNTH_NOTE_GIS7, SYNTH_NOTE_AIS7,
SYNTH_NOTE_C8, SYNTH_NOTE_D8, SYNTH_NOTE_DIS8, SYNTH_NOTE_F8, SYNTH_NOTE_G8, SYNTH_NOTE_GIS8, SYNTH_NOTE_AIS8};

// Notes for pentatonic scale
float synth_notes_pentatonic[45] = {
SYNTH_NOTE_CIS0, SYNTH_NOTE_DIS0, SYNTH_NOTE_FIS0, SYNTH_NOTE_GIS0, SYNTH_NOTE_AIS0,
SYNTH_NOTE_CIS1, SYNTH_NOTE_DIS1, SYNTH_NOTE_FIS1, SYNTH_NOTE_GIS1, SYNTH_NOTE_AIS1,
SYNTH_NOTE_CIS2, SYNTH_NOTE_DIS2, SYNTH_NOTE_FIS2, SYNTH_NOTE_GIS2, SYNTH_NOTE_AIS2,
SYNTH_NOTE_CIS3, SYNTH_NOTE_DIS3, SYNTH_NOTE_FIS3, SYNTH_NOTE_GIS3, SYNTH_NOTE_AIS3,
SYNTH_NOTE_CIS4, SYNTH_NOTE_DIS4, SYNTH_NOTE_FIS4, SYNTH_NOTE_GIS4, SYNTH_NOTE_AIS4,
SYNTH_NOTE_CIS5, SYNTH_NOTE_DIS5, SYNTH_NOTE_FIS5, SYNTH_NOTE_GIS5, SYNTH_NOTE_AIS5,
SYNTH_NOTE_CIS6, SYNTH_NOTE_DIS6, SYNTH_NOTE_FIS6, SYNTH_NOTE_GIS6, SYNTH_NOTE_AIS6,
SYNTH_NOTE_CIS7, SYNTH_NOTE_DIS7, SYNTH_NOTE_FIS7, SYNTH_NOTE_GIS7, SYNTH_NOTE_AIS7,
SYNTH_NOTE_CIS8, SYNTH_NOTE_DIS8, SYNTH_NOTE_FIS8, SYNTH_NOTE_GIS8, SYNTH_NOTE_AIS8};

// Sinwave table due to no math.h
float synth_sines[SYNTH_NUM_SINES] = {
0.000000000f, 0.024541229f, 0.049067674f, 0.073564564f, 0.098017140f, 0.122410675f, 
0.146730474f, 0.170961889f, 0.195090322f, 0.219101240f, 0.242980180f, 0.266712757f, 
0.290284677f, 0.313681740f, 0.336889853f, 0.359895037f, 0.382683432f, 0.405241314f, 
0.427555093f, 0.449611330f, 0.471396737f, 0.492898192f, 0.514102744f, 0.534997620f, 
0.555570233f, 0.575808191f, 0.595699304f, 0.615231591f, 0.634393284f, 0.653172843f, 
0.671558955f, 0.689540545f, 0.707106781f, 0.724247083f, 0.740951125f, 0.757208847f, 
0.773010453f, 0.788346428f, 0.803207531f, 0.817584813f, 0.831469612f, 0.844853565f, 
0.857728610f, 0.870086991f, 0.881921264f, 0.893224301f, 0.903989293f, 0.914209756f, 
0.923879533f, 0.932992799f, 0.941544065f, 0.949528181f, 0.956940336f, 0.963776066f, 
0.970031253f, 0.975702130f, 0.980785280f, 0.985277642f, 0.989176510f, 0.992479535f, 
0.995184727f, 0.997290457f, 0.998795456f, 0.999698819f, 1.000000000f, 0.999698819f, 
0.998795456f, 0.997290457f, 0.995184727f, 0.992479535f, 0.989176510f, 0.985277642f, 
0.980785280f, 0.975702130f, 0.970031253f, 0.963776066f, 0.956940336f, 0.949528181f, 
0.941544065f, 0.932992799f, 0.923879533f, 0.914209756f, 0.903989293f, 0.893224301f, 
0.881921264f, 0.870086991f, 0.857728610f, 0.844853565f, 0.831469612f, 0.817584813f, 
0.803207531f, 0.788346428f, 0.773010453f, 0.757208847f, 0.740951125f, 0.724247083f, 
0.707106781f, 0.689540545f, 0.671558955f, 0.653172843f, 0.634393284f, 0.615231591f, 
0.595699304f, 0.575808191f, 0.555570233f, 0.534997620f, 0.514102744f, 0.492898192f, 
0.471396737f, 0.449611330f, 0.427555093f, 0.405241314f, 0.382683432f, 0.359895037f, 
0.336889853f, 0.313681740f, 0.290284677f, 0.266712757f, 0.242980180f, 0.219101240f, 
0.195090322f, 0.170961889f, 0.146730474f, 0.122410675f, 0.098017140f, 0.073564564f, 
0.049067674f, 0.024541229f, 0.000000000f, -0.024541229f, -0.049067674f, -0.073564564f, 
-0.098017140f, -0.122410675f, -0.146730474f, -0.170961889f, -0.195090322f, -0.219101240f, 
-0.242980180f, -0.266712757f, -0.290284677f, -0.313681740f, -0.336889853f, -0.359895037f, 
-0.382683432f, -0.405241314f, -0.427555093f, -0.449611330f, -0.471396737f, -0.492898192f, 
-0.514102744f, -0.534997620f, -0.555570233f, -0.575808191f, -0.595699304f, -0.615231591f, 
-0.634393284f, -0.653172843f, -0.671558955f, -0.689540545f, -0.707106781f, -0.724247083f, 
-0.740951125f, -0.757208847f, -0.773010453f, -0.788346428f, -0.803207531f, -0.817584813f, 
-0.831469612f, -0.844853565f, -0.857728610f, -0.870086991f, -0.881921264f, -0.893224301f, 
-0.903989293f, -0.914209756f, -0.923879533f, -0.932992799f, -0.941544065f, -0.949528181f, 
-0.956940336f, -0.963776066f, -0.970031253f, -0.975702130f, -0.980785280f, -0.985277642f, 
-0.989176510f, -0.992479535f, -0.995184727f, -0.997290457f, -0.998795456f, -0.999698819f, 
-1.000000000f, -0.999698819f, -0.998795456f, -0.997290457f, -0.995184727f, -0.992479535f, 
-0.989176510f, -0.985277642f, -0.980785280f, -0.975702130f, -0.970031253f, -0.963776066f, 
-0.956940336f, -0.949528181f, -0.941544065f, -0.932992799f, -0.923879533f, -0.914209756f, 
-0.903989293f, -0.893224301f, -0.881921264f, -0.870086991f, -0.857728610f, -0.844853565f, 
-0.831469612f, -0.817584813f, -0.803207531f, -0.788346428f, -0.773010453f, -0.757208847f, 
-0.740951125f, -0.724247083f, -0.707106781f, -0.689540545f, -0.671558955f, -0.653172843f, 
-0.634393284f, -0.615231591f, -0.595699304f, -0.575808191f, -0.555570233f, -0.534997620f, 
-0.514102744f, -0.492898192f, -0.471396737f, -0.449611330f, -0.427555093f, -0.405241314f, 
-0.382683432f, -0.359895037f, -0.336889853f, -0.313681740f, -0.290284677f, -0.266712757f, 
-0.242980180f, -0.219101240f, -0.195090322f, -0.170961889f, -0.146730474f, -0.122410675f, 
-0.098017140f, -0.073564564f, -0.049067674f, -0.024541229f};

// Load song
void synth_load_song1()
{
    int i;
    
    // initialize song with waveform, frequency, frequency smoothing, amplification, amplification smoothing
    synth_init(&synth_songs[0].syn1, SYNTH_WAVE_TRIANGLE, 440.0f, 1.0f, 0.05f, 250.0f);
    
    // Song notes and parameters, bpm = samplerate / tickdelay / 4 * 60
    synth_songs[0].tickdelay = 2500; // 60 bpm at 10khz
    synth_songs[0].nexttick = 0;
    synth_songs[0].length = 48;
    synth_songs[0].tick = 0;
    
    synth_songs[0].chn1[0] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[1] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[2] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[3] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[4] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[5] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[6] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[7] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[8] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[9] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[10] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[11] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[12] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[13] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[14] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[15] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[16] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[17] = SYNTH_IDX_NOTE_D4;
    synth_songs[0].chn1[18] = SYNTH_IDX_NOTE_F4;
    synth_songs[0].chn1[19] = SYNTH_IDX_NOTE_D4;
    
    synth_songs[0].chn1[20] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[21] = SYNTH_IDX_NOTE_D4;
    synth_songs[0].chn1[22] = SYNTH_IDX_NOTE_F4;
    synth_songs[0].chn1[23] = SYNTH_IDX_NOTE_D4;
    
    synth_songs[0].chn1[24] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[25] = SYNTH_IDX_NOTE_D4;
    synth_songs[0].chn1[26] = SYNTH_IDX_NOTE_F4;
    synth_songs[0].chn1[27] = SYNTH_IDX_NOTE_D4;
    
    synth_songs[0].chn1[28] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[29] = SYNTH_IDX_NOTE_D4;
    synth_songs[0].chn1[30] = SYNTH_IDX_NOTE_F4;
    synth_songs[0].chn1[31] = SYNTH_IDX_NOTE_D4;
    
    synth_songs[0].chn1[32] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[33] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[34] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[35] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[36] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[37] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[38] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[39] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[40] = SYNTH_IDX_NOTE_G3;
    synth_songs[0].chn1[41] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[42] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[43] = SYNTH_IDX_NOTE_C4;
    
    synth_songs[0].chn1[44] = SYNTH_IDX_NOTE_A3;
    synth_songs[0].chn1[45] = SYNTH_IDX_NOTE_C4;
    synth_songs[0].chn1[46] = SYNTH_IDX_NOTE_E4;
    synth_songs[0].chn1[47] = SYNTH_IDX_NOTE_C4;
    
    for (i = 0; i < 48; ++i)
    {
        synth_songs[0].amp1[i] = 127;
        synth_songs[0].len1[i] = 127;
    }
}

// load second song
void synth_load_song2()
{
    int i;
    // initialize song with waveform, frequency, frequency smoothing, amplification, amplification smoothing
    synth_init(&synth_songs[1].syn1, SYNTH_WAVE_SINE, 440.0f, 1.0f, 0.05f, 150.0f);
    
    synth_songs[1].tickdelay = 2000;
    synth_songs[1].nexttick = 0;
    synth_songs[1].length = 64;
    synth_songs[1].tick = 0;
    
    synth_songs[1].chn1[0] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[1] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[2] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[3] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[4] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[5] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[6] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[7] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[8] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[9] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[10] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[11] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[12] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[13] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[14] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[15] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[16] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[17] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[18] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[19] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[20] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[21] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[22] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[23] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[24] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[25] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[26] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[27] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[28] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[29] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[30] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[31] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[32] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[33] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[34] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[35] = SYNTH_IDX_NOTE_C5;
    synth_songs[1].chn1[36] = SYNTH_IDX_NOTE_E5;
    synth_songs[1].chn1[37] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[38] = SYNTH_IDX_NOTE_D5;
    synth_songs[1].chn1[39] = SYNTH_IDX_NOTE_C5;
    synth_songs[1].chn1[40] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[41] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[42] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[43] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[44] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[45] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[46] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[47] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[48] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[49] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[50] = SYNTH_IDX_NOTE_FIS4;
    synth_songs[1].chn1[51] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[52] = SYNTH_IDX_NOTE_A4;
    synth_songs[1].chn1[53] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[54] = SYNTH_IDX_NOTE_B4;
    synth_songs[1].chn1[55] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[56] = SYNTH_IDX_NOTE_G4;
    synth_songs[1].chn1[57] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[58] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[59] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[60] = SYNTH_IDX_NOTE_E4;
    synth_songs[1].chn1[61] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[62] = SYNTH_IDX_NOTE_C0;
    synth_songs[1].chn1[63] = SYNTH_IDX_NOTE_C0;
    
    for (i = 0; i < 64; ++i)
    {
        if (synth_songs[1].chn1[i] == SYNTH_IDX_NOTE_C0)
        {
            synth_songs[1].amp1[i] = 0;
        }
        else
        {
            synth_songs[1].chn1[i] += 1;
            synth_songs[1].amp1[i] = 48;
        }
        
        synth_songs[1].len1[i] = 127;
    }
}

void synth_load_song3()
{
    int i;
    
    synth_init(&synth_songs[2].syn1, SYNTH_WAVE_SINE, 440.0f, 1.0f, 0.05f, 50.0f);
    
    synth_songs[2].tickdelay = 2000;
    synth_songs[2].nexttick = 0;
    synth_songs[2].length = 60;
    synth_songs[2].tick = 0;
    
    synth_songs[2].chn1[0] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[1] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[2] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[3] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[4] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[5] = SYNTH_IDX_NOTE_C4;
    synth_songs[2].chn1[6] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[7] = SYNTH_IDX_NOTE_G4;
    synth_songs[2].chn1[8] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[9] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[10] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[11] = SYNTH_IDX_NOTE_G3;
    synth_songs[2].chn1[12] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[13] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[14] = SYNTH_IDX_NOTE_C4;
    synth_songs[2].chn1[15] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[16] = SYNTH_IDX_NOTE_G3;
    synth_songs[2].chn1[17] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[18] = SYNTH_IDX_NOTE_E3;
    synth_songs[2].chn1[19] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[20] = SYNTH_IDX_NOTE_A3;
    synth_songs[2].chn1[21] = SYNTH_IDX_NOTE_B3;
    synth_songs[2].chn1[22] = SYNTH_IDX_NOTE_AIS3;
    synth_songs[2].chn1[23] = SYNTH_IDX_NOTE_A3;
    synth_songs[2].chn1[24] = SYNTH_IDX_NOTE_G3;
    synth_songs[2].chn1[25] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[26] = SYNTH_IDX_NOTE_G4;
    synth_songs[2].chn1[27] = SYNTH_IDX_NOTE_A4;
    synth_songs[2].chn1[28] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[29] = SYNTH_IDX_NOTE_F4;
    synth_songs[2].chn1[30] = SYNTH_IDX_NOTE_G4;
    synth_songs[2].chn1[31] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[32] = SYNTH_IDX_NOTE_C4;
    synth_songs[2].chn1[33] = SYNTH_IDX_NOTE_D4;
    synth_songs[2].chn1[34] = SYNTH_IDX_NOTE_B3;
    synth_songs[2].chn1[35] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[36] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[37] = SYNTH_IDX_NOTE_C4;
    synth_songs[2].chn1[38] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[39] = SYNTH_IDX_NOTE_G3;
    synth_songs[2].chn1[40] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[41] = SYNTH_IDX_NOTE_E3;
    synth_songs[2].chn1[42] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[43] = SYNTH_IDX_NOTE_A3;
    synth_songs[2].chn1[44] = SYNTH_IDX_NOTE_B3;
    synth_songs[2].chn1[45] = SYNTH_IDX_NOTE_AIS3;
    synth_songs[2].chn1[46] = SYNTH_IDX_NOTE_A3;
    synth_songs[2].chn1[47] = SYNTH_IDX_NOTE_G3;
    synth_songs[2].chn1[48] = SYNTH_IDX_NOTE_E4;
    synth_songs[2].chn1[49] = SYNTH_IDX_NOTE_G4;
    synth_songs[2].chn1[50] = SYNTH_IDX_NOTE_A4;
    synth_songs[2].chn1[51] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[52] = SYNTH_IDX_NOTE_F4;
    synth_songs[2].chn1[53] = SYNTH_IDX_NOTE_G4;
    synth_songs[2].chn1[54] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[55] = SYNTH_IDX_NOTE_C4;
    synth_songs[2].chn1[56] = SYNTH_IDX_NOTE_D4;
    synth_songs[2].chn1[57] = SYNTH_IDX_NOTE_B3;
    synth_songs[2].chn1[58] = SYNTH_IDX_NOTE_C0;
    synth_songs[2].chn1[59] = SYNTH_IDX_NOTE_C0;
    
    for (i = 0; i < 64; ++i)
    {
        if (synth_songs[2].chn1[i] == SYNTH_IDX_NOTE_C0)
        {
            synth_songs[2].amp1[i] = 0;
        }
        else
        {
            synth_songs[2].chn1[i] += 1;
            synth_songs[2].amp1[i] = 48;
        }
        
        synth_songs[2].len1[i] = 127;
    }
}


void synth_step_song(synth_song_t* song, float samplerate)
{
    if (song->nexttick > 0)
    {
        --song->nexttick;
    }
    else
    {
        song->nexttick = song->tickdelay;
        
        song->syn1.target_freq = synth_notes_keys[song->chn1[song->tick]];
        song->syn1.target_amp = song->amp1[song->tick] / 255.0f;
        
        song->tick = (song->tick + 1) % song->length;
    }
    
    synth_step(&song->syn1, samplerate);
    
    if (((float)(song->tickdelay - song->nexttick) / (float)song->tickdelay) > (float)song->len1[song->tick] / 255.0)
    {
        // song->syn1.amplitude = 0.0f;
        song->syn1.target_amp = 0.0f;
    }
}

void synth_init(synth_t* dest, uint8_t shape, float freq, float freq_smooth, float amp, float amp_smooth)
{
    dest->shape = shape;
    dest->frequency = freq;
    dest->target_freq = freq;
    dest->freq_smoothing = freq_smooth;
    dest->amplitude = amp;
    dest->target_amp = amp;
    dest->amp_smoothing = amp_smooth;
    dest->phase = 0;
    dest->signal = 127;
}

void synth_step(synth_t* dest, float samplerate)
{
    dest->frequency = dest->frequency + ((dest->target_freq - dest->frequency) / dest->freq_smoothing);
    dest->amplitude = dest->amplitude + ((dest->target_amp - dest->amplitude) / dest->amp_smoothing);
    
    dest->phase += SYNTH_TWOPI * dest->frequency / samplerate;
    
    if (dest->phase > SYNTH_TWOPI)
    {
        dest->phase -= SYNTH_TWOPI;
    }
    
    switch (dest->shape)
    {
        // Waveform
        case SYNTH_WAVE_TRIANGLE:
            if (dest->phase < SYNTH_PI)
            {
                dest->signal = 255 * dest->phase / SYNTH_PI * dest->amplitude;
            }
            else
            {
                dest->signal = 255 * (SYNTH_TWOPI - dest->phase) / SYNTH_PI * dest->amplitude;
            }
            break;
        
        case SYNTH_WAVE_SINE:
            dest->signal = 255 * synth_sines[(int)(SYNTH_NUM_SINES * (dest->phase / SYNTH_TWOPI))] * dest->amplitude;
            break;
        
        case SYNTH_WAVE_SAW:
            dest->signal = 255 * (dest->phase / SYNTH_TWOPI) * dest->amplitude;
            break;
        
        case SYNTH_WAVE_SQUARE:
            if (dest->phase < SYNTH_PI)
            {
                dest->signal = 255 * dest->amplitude;
            }
            else
            {
                dest->signal = 0;
            }
            
            break;
        
        default:
            break;
    }
}

// snap to notes
void synth_set_closest_note(synth_t* dest, int scale)
{
    float* notes;
    int num;
    int i;
    
    switch (scale)
    {
        // Scale
        case SYNTH_SCALE_KEYS:
            notes = synth_notes_keys;
            num = 108;
            break;
        
        case SYNTH_SCALE_MAJOR:
            notes = synth_notes_major;
            num = 63;
            break;
        
        case SYNTH_SCALE_MINOR:
            notes = synth_notes_minor;
            num = 63;
            break;
        
        case SYNTH_SCALE_PENTATONIC:
            notes = synth_notes_pentatonic;
            num = 45;
            break;
        
        default:
            notes = synth_notes_keys;
            num = 108;
            break;
    }
    
    for (i = 0; i < num; ++i)
    {
        if (i > 0 && dest->target_freq < notes[i])
        {
            dest->frequency = notes[i - 1];
            dest->target_freq = notes[i - 1];
            return;
        }
    }
}
