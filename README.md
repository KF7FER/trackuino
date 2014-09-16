Trackuino
=========
Firmware to turn your Arduino into an APRS tracker. This is based on [John Boile's](https://github.com/johnboiles/trackuino) port of [Trackuino](http://code.google.com/p/trackuino) by EA5HAV Javi.

Board support
-------------
Arduinos based on ATmega328 (e.g. Uno), ATmega32u4 (e.g. Arduino Leonardo), and chipKIT Uno32 are supported. Here are a couple PCB designs that work with this firmware:

* [Official Trackuino Shield](https://code.google.com/p/trackuino/wiki/TrackuinoShield22)
* [TinyTrackuino](https://github.com/johnboiles/tinytrackuino)
* [leoTracker](https://github.com/KF7FER/leoTracker)

Building with the Arduino IDE
-----------------------------

1. Open `trackuino/trackuino.ino`
2. Locate the `config.h` tab and replace settings with your own (`S_CALLSIGN`, `APRS_COMMENT`, etc).
3. Select the appropriate board for your hardware setup
4. Click Upload

On ATmega328 and other boards with only a single serial port, make sure to unplug the GPS when uploading or flashing will fail with an error.

External libraries used
----------------------------

This build of Trackuino uses the following external libraries:

* [OneWire Library (by PJRC)](https://www.pjrc.com/teensy/td_libs_OneWire.html)
* [DallasTemperature (by Miles Burton)](http://milesburton.com/Dallas_Temperature_Control_Library)
* [SdFat BETA (by Bill Greiman)](https://github.com/greiman/SdFat-beta)

Status
----------------------------

Currently this software seems to work fine but has NOT been flight tested so use at your own risk.

It looks like there are going to be resource issues attempting to keep all the current leoTracker features; it's going to be impossible to have Dallas OneWire sensors and the microSD and keep the USB boot loader; something will have to go (we are out of space in flash).  Most likely the bootloader and the board will feature the ability to be configured via microSD cards.


Building at the command line
----------------------------
A makefile is included for easy building and uploading outside the Arduino IDE. The `BOARD` environment variable needs to be specified so the makefile can know what board to compile for. For boards not included in the official Arduino IDE, you can set `BOARDSPATH` to point at a directory that has details about the board.

For example, for an Arduino UNO (included in the Arduino IDE)

    BOARD=uno make upload

Or for a Sparkfun ProMicro 5V/16MHz board (assuming Sparkfun boards are installed in `~/Documents/Arduino/hardware`)

    BOARD=promicro16 BOARDSPATH=~/Documents/Arduino/hardware/sf32u4_boards make upload
