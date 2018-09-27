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

// Special Thanks to: Johannes Löwe, Codruta Lugoj


#include "mbed.h"
#include "MIDI.h"
#include <cmath>
#include "PianoKey.h"
#include "ShiftReg.h"

MIDI midi(PB_6, PA_10); // Serail2
Serial pc(USBTX, USBRX); // tx, rx
InterruptIn btn(USER_BUTTON);
DigitalOut led(LED1);

ShiftReg   HC595(PB_10, PA_8, PA_9);
int regCounter = 0;

DigitalIn tl_1(PC_10);
DigitalIn tl_2(PC_12);
DigitalIn tl_3(PA_13);
DigitalIn tl_4(PA_14);
DigitalIn tl_5(PA_15);
DigitalIn tl_6(PB_7);
DigitalIn tl_7(PC_2);
DigitalIn tl_8(PC_3);

DigitalIn tr_1(PC_11);
DigitalIn tr_2(PD_2);
DigitalIn tr_3(PA_0);
DigitalIn tr_4(PA_1);
DigitalIn tr_5(PA_4);
DigitalIn tr_6(PB_0);
DigitalIn tr_7(PC_1);
DigitalIn tr_8(PC_0);

const int DELAY = 05; // time delay to set output register

// set t pins as pullup inputs.
// set mk5 and br5 to 0 to read it t
PianoKey A_0(21);
PianoKey Asharp_0(22);
PianoKey B_0(23);
PianoKey C_1(24);
PianoKey Csharp_1(25);
PianoKey D_1(26);
PianoKey Dsharp_1(27);
PianoKey E_1(28);
PianoKey F_1(29);
PianoKey Fsharp_1(30);
PianoKey G_1(31);
PianoKey Gsharp_1(32);
PianoKey A_1(33);
PianoKey Asharp_1(34);
PianoKey B_1(35);
PianoKey C_2(36);
PianoKey Csharp_2(37);
PianoKey D_2(38);
PianoKey Dsharp_2(39);
PianoKey E_2(40);
PianoKey F_2(41);
PianoKey Fsharp_2(42);
PianoKey G_2(43);
PianoKey Gsharp_2(44);
PianoKey A_2(45);
PianoKey Asharp_2(46);
PianoKey B_2(47);
PianoKey C_3(48);
PianoKey Csharp_3(49);
PianoKey D_3(50);
PianoKey Dsharp_3(51);
PianoKey E_3(52);
PianoKey F_3(53);
PianoKey Fsharp_3(54);
PianoKey G_3(55);
PianoKey Gsharp_3(56);
PianoKey A_3(57);
PianoKey Asharp_3(58);
PianoKey B_3(59);
PianoKey C_4(60);

PianoKey Csharp_4(61);
PianoKey D_4(62);
PianoKey Dsharp_4(63);
PianoKey E_4(64);
PianoKey F_4(65);
PianoKey Fsharp_4(66);
PianoKey G_4(67);
PianoKey Gsharp_4(68);
PianoKey A_4(69);
PianoKey Asharp_4(70);
PianoKey B_4(71);
PianoKey C_5(72);
PianoKey Csharp_5(73);
PianoKey D_5(74);
PianoKey Dsharp_5(75);
PianoKey E_5(76);
PianoKey F_5(77);
PianoKey Fsharp_5(78);
PianoKey G_5(79);
PianoKey Gsharp_5(80);
PianoKey A_5(81);
PianoKey Asharp_5(82);
PianoKey B_5(83);
PianoKey C_6(84);
PianoKey Csharp_6(85);
PianoKey D_6(86);
PianoKey Dsharp_6(87);
PianoKey E_6(88);
PianoKey F_6(89);
PianoKey Fsharp_6(90);
PianoKey G_6(91);
PianoKey Gsharp_6(92);
PianoKey A_6(93);
PianoKey Asharp_6(94);
PianoKey B_6(95);
PianoKey C_7(96);
PianoKey Csharp_7(97);
PianoKey D_7(98);
PianoKey Dsharp_7(99);
PianoKey E_7(100);
PianoKey F_7(101);
PianoKey Fsharp_7(102);
PianoKey G_7(103);
PianoKey Gsharp_7(104);
PianoKey A_7(105);
PianoKey Asharp_7(106);
PianoKey B_7(107);
PianoKey C_8(108);


void buttonOn()   // midi test
{
    pc.printf("Button pressed\n");
    midi.sendNoteOn(60, 127, 1);
}

void buttonOff()   // midi test
{
    pc.printf("Button released\n");
    midi.sendNoteOff(60, 127, 1);
}

void readInput()
{
    if (tl_1.read() == 0) {
            led = 1;
        } else {
            led = 0;
        }
        
    if (regCounter == 1) {
        if (tr_1.read() == 0) {
            A_0.brPressed();
        } else {
            A_0.brReleased();
        }
        if (tr_2.read() == 0) {
            Asharp_0.brPressed();
        } else {
            Asharp_0.brReleased();
        }
        if (tr_3.read() == 0) {
            B_0.brPressed();
        } else {
            B_0.brReleased();
        }
        if (tr_4.read() == 0) {
            C_1.brPressed();
        } else {
            C_1.brReleased();
        }
        if (tr_5.read() == 0) {
            Csharp_1.brPressed();
        } else {
            Csharp_1.brReleased();
        }
        if (tr_6.read() == 0) {
            D_1.brPressed();
        } else {
            D_1.brReleased();
        }
        if (tr_7.read() == 0) {
            Dsharp_1.brPressed();
        } else {
            Dsharp_1.brReleased();
        }
        if (tr_8.read() == 0) {
            E_1.brPressed();
        } else {
            E_1.brReleased();
        }
        if (tl_1.read() == 0) {
            Csharp_4.brPressed();
        } else {
            Csharp_4.brReleased();
        }
        if (tl_2.read() == 0) {
            D_4.brPressed();
        } else {
            D_4.brReleased();
        }
        if (tl_3.read() == 0) {
            Dsharp_4.brPressed();
        } else {
            Dsharp_4.brReleased();
        }
        if (tl_4.read() == 0) {
            E_4.brPressed();
        } else {
            E_4.brReleased();
        }
        if (tl_5.read() == 0) {
            F_4.brPressed();
        } else {
            F_4.brReleased();
        }
        if (tl_6.read() == 0) {
            Fsharp_4.brPressed();
        } else {
            Fsharp_4.brReleased();
        }
        if (tl_7.read() == 0) {
            G_4.brPressed();
        } else {
            G_4.brReleased();
        }
        if (tl_8.read() == 0) {
            Gsharp_4.brPressed();
        } else {
            Gsharp_4.brReleased();
        }
    }
    if (regCounter == 2) {
        if (tr_1.read() == 0) {
            A_0.mkPressed();
        } else {
            A_0.mkReleased();
        }
        if (tr_2.read() == 0) {
            Asharp_0.mkPressed();
        } else {
            Asharp_0.mkReleased();
        }
        if (tr_3.read() == 0) {
            B_0.mkPressed();
        } else {
            B_0.mkReleased();
        }
        if (tr_4.read() == 0) {
            C_1.mkPressed();
        } else {
            C_1.mkReleased();
        }
        if (tr_5.read() == 0) {
            Csharp_1.mkPressed();
        } else {
            Csharp_1.mkReleased();
        }
        if (tr_6.read() == 0) {
            D_1.mkPressed();
        } else {
            D_1.mkReleased();
        }
        if (tr_7.read() == 0) {
            Dsharp_1.mkPressed();
        } else {
            Dsharp_1.mkReleased();
        }
        if (tr_8.read() == 0) {
            E_1.mkPressed();
        } else {
            E_1.mkReleased();
        }
        if (tl_1.read() == 0) {
            Csharp_4.mkPressed();
        } else {
            Csharp_4.mkReleased();
        }
        if (tl_2.read() == 0) {
            D_4.mkPressed();
        } else {
            D_4.mkReleased();
        }
        if (tl_3.read() == 0) {
            Dsharp_4.mkPressed();
        } else {
            Dsharp_4.mkReleased();
        }
        if (tl_4.read() == 0) {
            E_4.mkPressed();
        } else {
            E_4.mkReleased();
        }
        if (tl_5.read() == 0) {
            F_4.mkPressed();
        } else {
            F_4.mkReleased();
        }
        if (tl_6.read() == 0) {
            Fsharp_4.mkPressed();
        } else {
            Fsharp_4.mkReleased();
        }
        if (tl_7.read() == 0) {
            G_4.mkPressed();
        } else {
            G_4.mkReleased();
        }
        if (tl_8.read() == 0) {
            Gsharp_4.mkPressed();
        } else {
            Gsharp_4.mkReleased();
        }
    }

    if (regCounter == 3) {
        if (tr_1.read() == 0) {
            F_1.brPressed();
        } else {
            F_1.brReleased();
        }
        if (tr_2.read() == 0) {
            Fsharp_1.brPressed();
        } else {
            Fsharp_1.brReleased();
        }
        if (tr_3.read() == 0) {
            G_1.brPressed();
        } else {
            G_1.brReleased();
        }
        if (tr_4.read() == 0) {
            Gsharp_1.brPressed();
        } else {
            Gsharp_1.brReleased();
        }
        if (tr_5.read() == 0) {
            A_1.brPressed();
        } else {
            A_1.brReleased();
        }
        if (tr_6.read() == 0) {
            Asharp_1.brPressed();
        } else {
            Asharp_1.brReleased();
        }
        if (tr_7.read() == 0) {
            B_1.brPressed();
        } else {
            B_1.brReleased();
        }
        if (tr_8.read() == 0) {
            C_2.brPressed();
        } else {
            C_2.brReleased();
        }
        if (tl_1.read() == 0) {
            A_4.brPressed();
        } else {
            A_4.brReleased();
        }
        if (tl_2.read() == 0) {
            Asharp_4.brPressed();
        } else {
            Asharp_4.brReleased();
        }
        if (tl_3.read() == 0) {
            B_4.brPressed();
        } else {
            B_4.brReleased();
        }
        if (tl_4.read() == 0) {
            C_5.brPressed();
        } else {
            C_5.brReleased();
        }
        if (tl_5.read() == 0) {
            Csharp_5.brPressed();
        } else {
            Csharp_5.brReleased();
        }
        if (tl_6.read() == 0) {
            D_5.brPressed();
        } else {
            D_5.brReleased();
        }
        if (tl_7.read() == 0) {
            Dsharp_5.brPressed();
        } else {
            Dsharp_5.brReleased();
        }
        if (tl_8.read() == 0) {
            E_5.brPressed();
        } else {
            E_5.brReleased();
        }
    }
    if (regCounter == 4) {
        if (tr_1.read() == 0) {
            F_1.mkPressed();
        } else {
            F_1.mkReleased();
        }
        if (tr_2.read() == 0) {
            Fsharp_1.mkPressed();
        } else {
            Fsharp_1.mkReleased();
        }
        if (tr_3.read() == 0) {
            G_1.mkPressed();
        } else {
            G_1.mkReleased();
        }
        if (tr_4.read() == 0) {
            Gsharp_1.mkPressed();
        } else {
            Gsharp_1.mkReleased();
        }
        if (tr_5.read() == 0) {
            A_1.mkPressed();
        } else {
            A_1.mkReleased();
        }
        if (tr_6.read() == 0) {
            Asharp_1.mkPressed();
        } else {
            Asharp_1.mkReleased();
        }
        if (tr_7.read() == 0) {
            B_1.mkPressed();
        } else {
            B_1.mkReleased();
        }
        if (tr_8.read() == 0) {
            C_2.mkPressed();
        } else {
            C_2.mkReleased();
        }
        if (tl_1.read() == 0) {
            A_4.mkPressed();
        } else {
            A_4.mkReleased();
        }
        if (tl_2.read() == 0) {
            Asharp_4.mkPressed();
        } else {
            Asharp_4.mkReleased();
        }
        if (tl_3.read() == 0) {
            B_4.mkPressed();
        } else {
            B_4.mkReleased();
        }
        if (tl_4.read() == 0) {
            C_5.mkPressed();
        } else {
            C_5.mkReleased();
        }
        if (tl_5.read() == 0) {
            Csharp_5.mkPressed();
        } else {
            Csharp_5.mkReleased();
        }
        if (tl_6.read() == 0) {
            D_5.mkPressed();
        } else {
            D_5.mkReleased();
        }
        if (tl_7.read() == 0) {
            Dsharp_5.mkPressed();
        } else {
            Dsharp_5.mkReleased();
        }
        if (tl_8.read() == 0) {
            E_5.mkPressed();
        } else {
            E_5.mkReleased();
        }
    }

    if (regCounter == 5) {
        if (tr_1.read() == 0) {
            Csharp_2.brPressed();
        } else {
            Csharp_2.brReleased();
        }
        if (tr_2.read() == 0) {
            D_2.brPressed();
        } else {
            D_2.brReleased();
        }
        if (tr_3.read() == 0) {
            Dsharp_2.brPressed();
        } else {
            Dsharp_2.brReleased();
        }
        if (tr_4.read() == 0) {
            E_2.brPressed();
        } else {
            E_2.brReleased();
        }
        if (tr_5.read() == 0) {
            F_2.brPressed();
        } else {
            F_2.brReleased();
        }
        if (tr_6.read() == 0) {
            Fsharp_2.brPressed();
        } else {
            Fsharp_2.brReleased();
        }
        if (tr_7.read() == 0) {
            G_2.brPressed();
        } else {
            G_2.brReleased();
        }
        if (tr_8.read() == 0) {
            Gsharp_2.brPressed();
        } else {
            Gsharp_2.brReleased();
        }
        if (tl_1.read() == 0) {
            F_5.brPressed();
        } else {
            F_5.brReleased();
        }
        if (tl_2.read() == 0) {
            Fsharp_5.brPressed();
        } else {
            Fsharp_5.brReleased();
        }
        if (tl_3.read() == 0) {
            G_5.brPressed();
        } else {
            G_5.brReleased();
        }
        if (tl_4.read() == 0) {
            Gsharp_5.brPressed();
        } else {
            Gsharp_5.brReleased();
        }
        if (tl_5.read() == 0) {
            A_5.brPressed();
        } else {
            A_5.brReleased();
        }
        if (tl_6.read() == 0) {
            Asharp_5.brPressed();
        } else {
            Asharp_5.brReleased();
        }
        if (tl_7.read() == 0) {
            B_5.brPressed();
        } else {
            B_5.brReleased();
        }
        if (tl_8.read() == 0) {
            C_6.brPressed();
        } else {
            C_6.brReleased();
        }
    }
    if (regCounter == 6) {
        if (tr_1.read() == 0) {
            Csharp_2.mkPressed();
        } else {
            Csharp_2.mkReleased();
        }
        if (tr_2.read() == 0) {
            D_2.mkPressed();
        } else {
            D_2.mkReleased();
        }
        if (tr_3.read() == 0) {
            Dsharp_2.mkPressed();
        } else {
            Dsharp_2.mkReleased();
        }
        if (tr_4.read() == 0) {
            E_2.mkPressed();
        } else {
            E_2.mkReleased();
        }
        if (tr_5.read() == 0) {
            F_2.mkPressed();
        } else {
            F_2.mkReleased();
        }
        if (tr_6.read() == 0) {
            Fsharp_2.mkPressed();
        } else {
            Fsharp_2.mkReleased();
        }
        if (tr_7.read() == 0) {
            G_2.mkPressed();
        } else {
            G_2.mkReleased();
        }
        if (tr_8.read() == 0) {
            Gsharp_2.mkPressed();
        } else {
            Gsharp_2.mkReleased();
        }
        if (tl_1.read() == 0) {
            F_5.mkPressed();
        } else {
            F_5.mkReleased();
        }
        if (tl_2.read() == 0) {
            Fsharp_5.mkPressed();
        } else {
            Fsharp_5.mkReleased();
        }
        if (tl_3.read() == 0) {
            G_5.mkPressed();
        } else {
            G_5.mkReleased();
        }
        if (tl_4.read() == 0) {
            Gsharp_5.mkPressed();
        } else {
            Gsharp_5.mkReleased();
        }
        if (tl_5.read() == 0) {
            A_5.mkPressed();
        } else {
            A_5.mkReleased();
        }
        if (tl_6.read() == 0) {
            Asharp_5.mkPressed();
        } else {
            Asharp_5.mkReleased();
        }
        if (tl_7.read() == 0) {
            B_5.mkPressed();
        } else {
            B_5.mkReleased();
        }
        if (tl_8.read() == 0) {
            C_6.mkPressed();
        } else {
            C_6.mkReleased();
        }
    }

    if (regCounter == 7) {
        if (tr_1.read() == 0) {
            A_2.brPressed();
        } else {
            A_2.brReleased();
        }
        if (tr_2.read() == 0) {
            Asharp_2.brPressed();
        } else {
            Asharp_2.brReleased();
        }
        if (tr_3.read() == 0) {
            B_2.brPressed();
        } else {
            B_2.brReleased();
        }
        if (tr_4.read() == 0) {
            C_3.brPressed();
        } else {
            C_3.brReleased();
        }
        if (tr_5.read() == 0) {
            Csharp_3.brPressed();
        } else {
            Csharp_3.brReleased();
        }
        if (tr_6.read() == 0) {
            D_3.brPressed();
        } else {
            D_3.brReleased();
        }
        if (tr_7.read() == 0) {
            Dsharp_3.brPressed();
        } else {
            Dsharp_3.brReleased();
        }
        if (tr_8.read() == 0) {
            E_3.brPressed();
        } else {
            E_3.brReleased();
        }  
        if (tl_1.read() == 0) {
            Csharp_6.brPressed();
        } else {
            Csharp_6.brReleased();
        }
        if (tl_2.read() == 0) {
            D_6.brPressed();
        } else {
            D_6.brReleased();
        }
        if (tl_3.read() == 0) {
            Dsharp_6.brPressed();
        } else {
            Dsharp_6.brReleased();
        }
        if (tl_4.read() == 0) {
            E_6.brPressed();
        } else {
            E_6.brReleased();
        }
        if (tl_5.read() == 0) {
            F_6.brPressed();
        } else {
            F_6.brReleased();
        }
        if (tl_6.read() == 0) {
            Fsharp_6.brPressed();
        } else {
            Fsharp_6.brReleased();
        }
        if (tl_7.read() == 0) {
            G_6.brPressed();
        } else {
            G_6.brReleased();
        }
        if (tl_8.read() == 0) {
            Gsharp_6.brPressed();
        } else {
            Gsharp_6.brReleased();
        }
    }
    if (regCounter == 8) {
        if (tr_1.read() == 0) {
            A_2.mkPressed();
        } else {
            A_2.mkReleased();
        }
        if (tr_2.read() == 0) {
            Asharp_2.mkPressed();
        } else {
            Asharp_2.mkReleased();
        }
        if (tr_3.read() == 0) {
            B_2.mkPressed();
        } else {
            B_2.mkReleased();
        }
        if (tr_4.read() == 0) {
            C_3.mkPressed();
        } else {
            C_3.mkReleased();
        }
        if (tr_5.read() == 0) {
            Csharp_3.mkPressed();
        } else {
            Csharp_3.mkReleased();
        }
        if (tr_6.read() == 0) {
            D_3.mkPressed();
        } else {
            D_3.mkReleased();
        }
        if (tr_7.read() == 0) {
            Dsharp_3.mkPressed();
        } else {
            Dsharp_3.mkReleased();
        }
        if (tr_8.read() == 0) {
            E_3.mkPressed();
        } else {
            E_3.mkReleased();
        }  
        if (tl_1.read() == 0) {
            Csharp_6.mkPressed();
        } else {
            Csharp_6.mkReleased();
        }
        if (tl_2.read() == 0) {
            D_6.mkPressed();
        } else {
            D_6.mkReleased();
        }
        if (tl_3.read() == 0) {
            Dsharp_6.mkPressed();
        } else {
            Dsharp_6.mkReleased();
        }
        if (tl_4.read() == 0) {
            E_6.mkPressed();
        } else {
            E_6.mkReleased();
        }
        if (tl_5.read() == 0) {
            F_6.mkPressed();
        } else {
            F_6.mkReleased();
        }
        if (tl_6.read() == 0) {
            Fsharp_6.mkPressed();
        } else {
            Fsharp_6.mkReleased();
        }
        if (tl_7.read() == 0) {
            G_6.mkPressed();
        } else {
            G_6.mkReleased();
        }
        if (tl_8.read() == 0) {
            Gsharp_6.mkPressed();
        } else {
            Gsharp_6.mkReleased();
        }
    }
    
    if (regCounter == 9) {
        if (tr_1.read() == 0) {
            F_3.brPressed();
        } else {
            F_3.brReleased();
        }
        if (tr_2.read() == 0) {
            Fsharp_3.brPressed();
        } else {
            Fsharp_3.brReleased();
        }
        if (tr_3.read() == 0) {
            G_3.brPressed();
        } else {
            G_3.brReleased();
        }
        if (tr_4.read() == 0) {
            Gsharp_3.brPressed();
        } else {
            Gsharp_3.brReleased();
        }
        if (tr_5.read() == 0) {
            A_3.brPressed();
        } else {
            A_3.brReleased();
        }
        if (tr_6.read() == 0) {
            Asharp_3.brPressed();
        } else {
            Asharp_3.brReleased();
        }
        if (tr_7.read() == 0) {
            B_3.brPressed();
        } else {
            B_3.brReleased();
        }
        if (tr_8.read() == 0) {
            C_4.brPressed();
        } else {
            C_4.brReleased();
        }
        if (tl_1.read() == 0) {
            A_6.brPressed();
        } else {
            A_6.brReleased();
        }
        if (tl_2.read() == 0) {
            Asharp_6.brPressed();
        } else {
            Asharp_6.brReleased();
        }
        if (tl_3.read() == 0) {
            B_6.brPressed();
        } else {
            B_6.brReleased();
        }
        if (tl_4.read() == 0) {
            C_7.brPressed();
        } else {
            C_7.brReleased();
        }
        if (tl_5.read() == 0) {
            Csharp_7.brPressed();
        } else {
            Csharp_7.brReleased();
        }
        if (tl_6.read() == 0) {
            D_7.brPressed();
        } else {
            D_7.brReleased();
        }
        if (tl_7.read() == 0) {
            Dsharp_7.brPressed();
        } else {
            Dsharp_7.brReleased();
        }
        if (tl_8.read() == 0) {
            E_7.brPressed();
        } else {
            E_7.brReleased();
        }
    }
    if (regCounter == 10) {
        if (tr_1.read() == 0) {
            F_3.mkPressed();
        } else {
            F_3.mkReleased();
        }
        if (tr_2.read() == 0) {
            Fsharp_3.mkPressed();
        } else {
            Fsharp_3.mkReleased();
        }
        if (tr_3.read() == 0) {
            G_3.mkPressed();
        } else {
            G_3.mkReleased();
        }
        if (tr_4.read() == 0) {
            Gsharp_3.mkPressed();
        } else {
            Gsharp_3.mkReleased();
        }
        if (tr_5.read() == 0) {
            A_3.mkPressed();
        } else {
            A_3.mkReleased();
        }
        if (tr_6.read() == 0) {
            Asharp_3.mkPressed();
        } else {
            Asharp_3.mkReleased();
        }
        if (tr_7.read() == 0) {
            B_3.mkPressed();
        } else {
            B_3.mkReleased();
        }
        if (tr_8.read() == 0) {
            C_4.mkPressed();
        } else {
            C_4.mkReleased();
        }
        if (tl_1.read() == 0) {
            A_6.mkPressed();
        } else {
            A_6.mkReleased();
        }
        if (tl_2.read() == 0) {
            Asharp_6.mkPressed();
        } else {
            Asharp_6.mkReleased();
        }
        if (tl_3.read() == 0) {
            B_6.mkPressed();
        } else {
            B_6.mkReleased();
        }
        if (tl_4.read() == 0) {
            C_7.mkPressed();
        } else {
            C_7.mkReleased();
        }
        if (tl_5.read() == 0) {
            Csharp_7.mkPressed();
        } else {
            Csharp_7.mkReleased();
        }
        if (tl_6.read() == 0) {
            D_7.mkPressed();
        } else {
            D_7.mkReleased();
        }
        if (tl_7.read() == 0) {
            Dsharp_7.mkPressed();
        } else {
            Dsharp_7.mkReleased();
        }
        if (tl_8.read() == 0) {
            E_7.mkPressed();
        } else {
            E_7.mkReleased();
        }
    }
    
    if (regCounter == 11) {
        if (tl_1.read() == 0) {
            F_7.brPressed();
        } else {
            F_7.brReleased();
        }
        if (tl_2.read() == 0) {
            Fsharp_7.brPressed();
        } else {
            Fsharp_7.brReleased();
        }
        if (tl_3.read() == 0) {
            G_7.brPressed();
        } else {
            G_7.brReleased();
        }
        if (tl_4.read() == 0) {
            Gsharp_7.brPressed();
        } else {
            Gsharp_7.brReleased();
        }
        if (tl_5.read() == 0) {
            A_7.brPressed();
        } else {
            A_7.brReleased();
        }
        if (tl_6.read() == 0) {
            Asharp_7.brPressed();
        } else {
            Asharp_7.brReleased();
        }
        if (tl_7.read() == 0) {
            B_7.brPressed();
        } else {
            B_7.brReleased();
        }
        if (tl_8.read() == 0) {
            C_8.brPressed();
        } else {
            C_8.brReleased();
        }
    }
    if (regCounter == 12) {
        if (tl_1.read() == 0) {
            F_7.mkPressed();
        } else {
            F_7.mkReleased();
        }
        if (tl_2.read() == 0) {
            Fsharp_7.mkPressed();
        } else {
            Fsharp_7.mkReleased();
        }
        if (tl_3.read() == 0) {
            G_7.mkPressed();
        } else {
            G_7.mkReleased();
        }
        if (tl_4.read() == 0) {
            Gsharp_7.mkPressed();
        } else {
            Gsharp_7.mkReleased();
        }
        if (tl_5.read() == 0) {
            A_7.mkPressed();
        } else {
            A_7.mkReleased();
        }
        if (tl_6.read() == 0) {
            Asharp_7.mkPressed();
        } else {
            Asharp_7.mkReleased();
        }
        if (tl_7.read() == 0) {
            B_7.mkPressed();
        } else {
            B_7.mkReleased();
        }
        if (tl_8.read() == 0) {
            C_8.mkPressed();
        } else {
            C_8.mkReleased();
        }
    }
}

void regNext()
{
    if (regCounter == 0) {
        HC595.ShiftBit(0);
        HC595.Latch();
        regCounter++;
    } else {
        HC595.ShiftBit(1);
        HC595.Latch();
        regCounter++;
        if (regCounter > 16) {
            HC595.ShiftBit(0);
            HC595.Latch();
            regCounter = 1; // restart cycle
        }
    }
}

int main()
{
    pc.printf("\nHello World\n\n");
    midi.begin(MIDI_CHANNEL_OMNI);
    //Init ShiftRegister
    for(int i = 0; i < 16; i++) {
        HC595.ShiftBit(1);
    }
    HC595.Latch();
    // midi test
    btn.rise(&buttonOff);
    btn.fall(&buttonOn);

    tl_1.mode(PullUp);
    tl_2.mode(PullUp);
    tl_3.mode(PullUp);
    tl_4.mode(PullUp);
    tl_5.mode(PullUp);
    tl_6.mode(PullUp);
    tl_7.mode(PullUp);
    tl_8.mode(PullUp);
    
    tr_1.mode(PullUp);
    tr_2.mode(PullUp);
    tr_3.mode(PullUp);
    tr_4.mode(PullUp);
    tr_5.mode(PullUp);
    tr_6.mode(PullUp);
    tr_7.mode(PullUp);
    tr_8.mode(PullUp);

    while(1) {
        regNext();
        wait_us(DELAY);
        readInput();
    }
}
