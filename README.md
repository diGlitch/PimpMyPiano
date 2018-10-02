# PimpMyPiano
## Mbed based interface between Fatar TP44GH keybed and the midi world
---------------------------------------------------------------------------------------------------
Some day the controller board of my StudioLogic SL990Pro stopped working. Instead of buying a whhole new masterkeybard I though "why not building one my self and reusing the high quality Fata TP44GH keybed in there". What had to be done was to read out the double button matrix (two buttons/sensors for each note), meassuring the time between two button presses and convert this data into midi commands after about a year I ended up with a Mbed based interface between a Fatar TP44GH keybed and the midi world.

## How to make it work || Underconstruction
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

There are two parts: The software and the hardware.

### Prerequisites || Underconstruction
What things you need to install the software and how to install them

You will need ...:
* an ARM MBED ready board. I used the [NUCLEO-F411RE](https://os.mbed.com/platforms/ST-Nucleo-F411RE/) from ST. I guess the 100Mhz are a bit overkill so assume that something slower with similar pinout would do.
* hardware that connects the Nucleo with the Button Matrix of the piano. See Hardware folder for schematic and other hardware related details such as a part list.
* software that runs on the Nucleo. You can find the [PlatformIO](http://platformio.org) project in the src folder. Just clone the repo or download scr folder as ZIP and open "PimpMyPiano" folder in platformIO.

## Build With
* [MBED OS](https://www.mbed.com/en/platform/mbed-os/)
* [PlatformIO](http://platformio.org) extension for [VSCode](https://code.visualstudio.com/)

## Contributing || Underconstruction

### What is there to be improved
* Overall code base in terms of speed

## Authors
* **Jeremy Constantin Börker** - *Initial and so far all the work* - [diGlitch](https://github.com/diGlitch)

## License
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

## Acknowledgments
* Francois Best's Mbed MIDI Library for Arduino ported by Hiroshi Suga
* YoongHM's Mbed shift register library
* Processing for the mapping formular 
