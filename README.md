# Project Mini Turntable

All files nececasry to build a mini turntable from 'scratch' (pun intended).

This includes the following:

- C code to control a DC motor (with an L293D IC) with an 5 pin rotary encoder
- STL files for the housing
- Parts list (in this readme)

## Getting started

It's best to prototype this first on a breadboard. Just plug in your favorite Arduino flavour, upload the sketch and wire it up.
When that's done you can use the STL files and adjust them for your needs when building the mini turntable.

## Parts list

- Arduino Pro Mini (I used a 3,3V version because i had some laying arround)
- L293D motor driver IC (mine works with either 3,3V or 5V logic levels but best to check first)
- 5V DC motor
- rotary encoder
- Micro USB pinout board (used as a 5V powersupply)
- prototyping soldering board
- Cables, solder, ...
- 3D printer (i used a Original Prusa Mini with Galaxy Black PLA fillament)
- 4 rubber or felt feet to stick to the underside of the box

## Disclaimer

This project is by no means finished.

Known unsolved issues:

- The DC motor turns plenty fast but doesnt have the torque to easily turn heavier objects (possible solution: adding a gear assembly to lower the speed and up the torque of the motor).
- The motor / motor wiring (could be the wiring from the usb power supply too, didn't have the necesary tools to test it properly) has a big influence on the data wires comming from the rotary encoder. When the cables are placed near to each other the arduino will interpret the interference as the rotary encoder being turned and the motor speed will adjust accordingly (possible solution: using shielded cables).
- The revolving disk turns on a the shaft of the motor (in the center) so any object put off-center will woble (possible solution: put some small wheels on the perimiter of the disk).
- The 3D printed box ended up slightly warped so it's 100% level (possible solution: adding some structural support to it).