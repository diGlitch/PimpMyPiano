/*
<PimpMyPiano - Mbed based interface between a Fatar TP44GH keybed and the midi world.>
Copyright (C) 2018  Jeremy Constantin Börker aka diGlitch

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "PianoKey.h"
#include <stdlib.h> 

extern Serial pc;
extern MIDI midi;

const int MIN_DURATION = 3.0; // in ms
const int MAX_DURATION = 300.0; // in ms

#define DEBUG 0

PianoKey::PianoKey(int _midiNote)
{
    midiNote = _midiNote;
    timer.start();
    stateBR = false; //State for mk5
    stateMK = false; //State for br5
    sendNoteOff = false;
    timeMK = -1;
    timeBR = -1;
}

// Velocity courves
// velo1 - linear

int velo1 [(MAX_DURATION - MIN_DURATION)+1] = {127, 127, 126, 126, 125, 125, 124, 124, 124, 123, 123, 122, 122, 121, 121, 121, 120, 120, 119, 119, 119, 118, 118, 117, 117, 116, 116, 116, 115, 115, 114, 114, 113, 113, 113, 112, 112, 111, 111, 110, 110, 110, 109, 109, 108, 108, 107, 107, 107, 106, 106, 105, 105, 105, 104, 104, 103, 103, 102, 102, 102, 101, 101, 100, 100, 99, 99, 99, 98, 98, 97, 97, 96, 96, 96, 95, 95, 94, 94, 93, 93, 93, 92, 92, 91, 91, 91, 90, 90, 89, 89, 88, 88, 88, 87, 87, 86, 86, 85, 85, 85, 84, 84, 83, 83, 82, 82, 82, 81, 81, 80, 80, 79, 79, 79, 78, 78, 77, 77, 77, 76, 76, 75, 75, 74, 74, 74, 73, 73, 72, 72, 71, 71, 71, 70, 70, 69, 69, 68, 68, 68, 67, 67, 66, 66, 65, 65, 65, 64, 64, 63, 63, 63, 62, 62, 61, 61, 60, 60, 60, 59, 59, 58, 58, 57, 57, 57, 56, 56, 55, 55, 54, 54, 54, 53, 53, 52, 52, 51, 51, 51, 50, 50, 49, 49, 49, 48, 48, 47, 47, 46, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 40, 39, 39, 38, 38, 37, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 32, 32, 32, 31, 31, 30, 30, 29, 29, 29, 28, 28, 27, 27, 26, 26, 26, 25, 25, 24, 24, 23, 23, 23, 22, 22, 21, 21, 21, 20, 20, 19, 19, 18, 18, 18, 17, 17, 16, 16, 15, 15, 15, 14, 14, 13, 13, 12, 12, 12, 11, 11, 10, 10, 9, 9, 9, 8, 8, 7, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 2, 2, 1, 1};
int velo2 [(MAX_DURATION - MIN_DURATION)+1] = {127, 126, 124, 123, 122, 121, 119, 118, 117, 116, 115, 113, 112, 111, 110, 109, 108, 106, 105, 104, 103, 102, 101, 100, 99, 98, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 70, 69, 68, 67, 66, 65, 65, 64, 63, 62, 61, 61, 60, 59, 58, 57, 57, 56, 55, 54, 54, 53, 52, 52, 51, 50, 50, 49, 48, 48, 47, 46, 46, 45, 44, 44, 43, 42, 42, 41, 41, 40, 39, 39, 38, 38, 37, 37, 36, 35, 35, 34, 34, 33, 33, 32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 26, 25, 25, 24, 24, 23, 23, 23, 22, 22, 21, 21, 21, 20, 20, 19, 19, 19, 18, 18, 18, 17, 17, 17, 16, 16, 16, 15, 15, 15, 14, 14, 14, 14, 13, 13, 13, 12, 12, 12, 12, 11, 11, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int velo3 [(MAX_DURATION - MIN_DURATION)+1] = {127, 125, 123, 121, 118, 116, 114, 112, 110, 108, 106, 104, 102, 100, 98, 96, 95, 93, 91, 89, 87, 86, 84, 82, 80, 79, 77, 76, 74, 72, 71, 69, 68, 66, 65, 64, 62, 61, 59, 58, 57, 56, 54, 53, 52, 51, 50, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 34, 33, 32, 31, 30, 30, 29, 28, 27, 27, 26, 25, 25, 24, 23, 23, 22, 21, 21, 20, 20, 19, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 14, 14, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 10, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Adapted from processing.org map method
int PianoKey::getVelocity(int x)
{
    if (x > MAX_DURATION) {
        x = MAX_DURATION;
    }
#if DEBUG == 1
    printf("Velocity: %d with ", velo3[x-3]);
    printf(" %d ms\n", x);
#endif
    return velo3[x];
}

void PianoKey::resetMeasurement()
{
    timer.reset();
    timeMK = -1;
    timeBR = -1;
}

void PianoKey::SendNoteOn() {
    if (stateBR && stateMK) {
        int velo = getVelocity(abs(timeMK - timeBR));
        midi.sendNoteOn(midiNote, velo, 1);
#if DEBUG == 1
        printf("Send a note! :) \n");
        printf("-------------------\n");
        printf("time MK: %d \n", timeMK);
        printf("time BR: %d \n", timeBR);
        printf("difference: %d \n", timeBR-timeMK);
        printf("difference: %d \n", abs(timeBR-timeMK)) ;
        printf("velocity: %d \n", velo);
        printf("-------------------\n");
#endif
    }
}

void PianoKey::SendNoteOff() {
    if (!stateBR && !stateMK) {
        midi.sendNoteOff(midiNote, 0, 1);
#if DEBUG == 1
        printf("Turn a note off! ): \n");
#endif
    }
}

// 1st
void PianoKey::brPressed()
{
    if (!stateBR) {
        timeBR = timer.read_ms();
        stateBR = true;
        //printf("BR PRESSED\n");
        SendNoteOn();
    }
}

void PianoKey::brReleased()
{
    if (stateBR) {
        stateBR = false;
        SendNoteOff();
        //printf("BR Released\n");
    }
}

//2nd
void PianoKey::mkPressed()
{
    if (!stateMK) {
        timeMK = timer.read_ms();
        stateMK = true;
        //printf("MK PRESSED\n");
        SendNoteOn();
    }
}

void PianoKey::mkReleased()
{
    if (stateMK) {
        stateMK = false;
        //printf("MK Released\n");
        SendNoteOff();
        resetMeasurement();
    }

}