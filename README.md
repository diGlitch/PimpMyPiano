# PimpMyPiano
## Mbed based interface between Fatar TP44GH keybed and the midi world
----------------------------------------------------------------------

### Preface
Some day the controller board of my StudioLogic SL990Pro stopped working. Instead of buying a whhole new masterkeybard I though "why not building one my self and reusing the high quality Fata TP44GH keybed in there". What had to be done was to read out the double button matrix (two buttons/sensors for each note), meassuring the time between two button presses and convert this data into midi commands.

Main Components:
 - Microcontroller: NUCLEO-F411RE see www.st.com/stm32nucleo
 - 2x shift register
---------------------------------------------------------------------------------------------------


 # PimpMyPiano

Some day the controller board of my StudioLogic SL990Pro stopped working. Instead of buying a whhole new masterkeybard I though "why not building one my self and reusing the high quality Fata TP44GH keybed in there". What had to be done was to read out the double button matrix (two buttons/sensors for each note), meassuring the time between two button presses and convert this data into midi commands after about a year I ended up with a Mbed based interface between a Fatar TP44GH keybed and the midi world.

## How to make it work

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

There are two parts: The software and the hardware.

### Prerequisites
What things you need to install the software and how to install them

You need these things:
- You will need an ARM MBED ready board. I used the NUCLEO-F411RE from ST. I guess the 100Mhz are a bit overkill so assume that something slower with similar pinout would do.
- Hardware that connects the Nucleo with the Button Matrix of the piano. See Hardware folder for schematic and other hardware related details
- Software that runs on the Nucleo. You will find these in src folder. I made the whole project in the online compiler and exportet it in multible ways.


```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc