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

#include "mbed.h"
#include "MIDI.h"

using namespace std;

class PianoKey {
    public:
        void mkPressed();
        void mkReleased();
        void brPressed();
        void brReleased();
        PianoKey(int midiNote); // Constructor
    private:
        int midiNote;
        Timer timer;
        bool stateBR;
        bool stateMK;
        bool sendNoteOff;
        int timeMK;
        int timeBR;
        int getVelocity(int x);
        void resetMeasurement();
        void SendNoteOn();
        void SendNoteOff();
    };