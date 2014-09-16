/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __CONFIG_BOARD__
#define __CONFIG_BOARD__


// --------------------------------------------------------------------------
// THIS IS THE leoTracker (REVISION "E") BOARD-SPECIFIC CONFIGURATION FILE
// (http://www.github.com/johnboiles/tinytrackuino)
//
// NOTE: all pins are Arduino based, not the Atmega chip. Mapping:
// http://www.arduino.cc/en/Hacking/PinMapping
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Modem config (afsk.cpp)
// --------------------------------------------------------------------------

// AUDIO_PIN is the audio-out pin. On the Atmega32u4 the audio is generated
// by either timer 1 or timer 4 using PWM.
#define AUDIO_PIN       10

// --------------------------------------------------------------------------
// Radio config (radio_hx1.cpp)
// --------------------------------------------------------------------------

// This is the PTT pin
#define PTT_PIN           5

// How long to delay after raising PTT before transmission
#define PTT_RAISE_DELAY   250

// Since the leoTracker uses several different Radio modules, we need to
// bring the Radio class definition back here (ala Trackuino 1.3.x).
#define RADIO_CLASS       RadioHx1

// This is the pin to enable the radio module
//#define RADIO_ENABLE_PIN   5

// This is the pin to switch from low to high output power
//#define RADIO_HL_PIN      11

// Radio "Warm up" time (how long after enabling radio do we transmit?)
//
// But wait... it's not just "Warm up" time.  It's also a dessert topping!
//
// Due to my lousy coding skills, I also use this value to determine when
// it's time to query the DS18b20 temperature sensors
#define RADIO_WARMUP_TIME 1000

// --------------------------------------------------------------------------
// GPS config (gps.cpp)
// --------------------------------------------------------------------------

// Set to indicate we are using a uBLOX GPS
#define GPS_USING_UBLOX         

// GPS Power Pin
//
// Some versions of leoTracker have GPS power tied to a digital I/O pin
#define GPS_POWER_PIN    8

// Delay time needed after GPS power up but before it's ready to receive
// data (in millis)
#define GPS_POWER_SLEEP_TIME 300

// For the uBLOX we need to know the minimum number of visible satellites 
// before we can enter cyclic mode
#define MIN_NO_CYCLIC_SATS     5

// --------------------------------------------------------------------------
// MicroSD Configuration (microsd.cpp)
// --------------------------------------------------------------------------

#define USD_CARD_SELECT   9
#define USD_CARD_DETECT  13

// --------------------------------------------------------------------------
// Sensors config (sensors.cpp)
// --------------------------------------------------------------------------

// Use either OneWire temperature sensors (currently only the DS18b20 is 
// supported) OR the LM60
#define USE_ONEWIRE_TEMP   1

// Which digital pin for OneWire
#define ONEWIRE_PIN        6

// Out of the box we only support an internal temperature sensor
//#define INTERNAL_DS18B20_DISABLED
#define EXTERNAL_DS18B20_DISABLED

// Initially the code I used had a 5s delay the first time the bus was
// started (w/ a reference to a hang on Linux w/o the delay) so I kept it
// but cut it down a bit (this is in millis)
#define ONEWIRE_STARTUP_DELAY   500

// Use these if not using OneWire (to disable the default sensors)
#define INTERNAL_LM60_DISABLED
#define EXTERNAL_LM60_DISABLED


// Most of the sensors.cpp functions use internal reference voltages (either
// AVCC or 1.1V). If you want to use an external reference, you should
// uncomment the following line:
//
// #define USE_AREF
//
// BEWARE! If you hook up an external voltage to the AREF pin and 
// accidentally set the ADC to any of the internal references, YOU WILL
// FRY YOUR AVR.
//
// It is always advised to connect the AREF pin through a pull-up resistor,
// whose value is defined here in ohms (set to 0 if no pull-up):
//
// #define AREF_PULLUP           4700
//
// Since there is already a 32K resistor at the ADC pin, the actual
// voltage read will be VREF * 32 / (32 + AREF_PULLUP)
//
// Read more in the Arduino reference docs:
// http://arduino.cc/en/Reference/AnalogReference?from=Reference.AREF

// Pin mappings for the internal / external temperature sensors. VS refers
// to (arduino) digital pins, whereas VOUT refers to (arduino) analog pins.
#define INTERNAL_LM60_VS_PIN     6
#define INTERNAL_LM60_VOUT_PIN   0
#define EXTERNAL_LM60_VS_PIN     7
#define EXTERNAL_LM60_VOUT_PIN   2

// Voltage meter analog pin
#define VMETER_PIN               1

// --------------------------------------------------------------------------
// Buzzer config (buzzer.cpp)
// --------------------------------------------------------------------------

#define BUZZER_PIN               3

// --------------------------------------------------------------------------
// Debug
// --------------------------------------------------------------------------

// leoTracker wired it's LEDs differently so need this
#define DEBUG_PIN_INVERT

// This is the LED pin (13 on most Arduinos, 17 on Atmega32u4). The LED will be on while the AVR is
// running and off while it's sleeping, so its brightness gives an indication
// of the CPU activity.
#define LED_PIN                 7

// GPS fix LED
#define GPS_LED_PIN             4

// microSD Activity LED
#define USD_LED_PIN            12

// --------------------------------------------------------------------------
// LCD
// --------------------------------------------------------------------------

//#define LCD_ENABLED
//#define LCD_PINS 12, 11, 5, 8, 9, 10

#endif
