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

/* Credit to:
 *
 * cathedrow for this idea on using the ADC as a volt meter:
 * http://code.google.com/p/tinkerit/wiki/SecretVoltmeter
 */

#ifdef AVR

#include "config.h"
#include "pin.h"
#include "sensors_avr.h"
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#  include <WProgram.h>
#endif

#if defined(__AVR_ATmega32U4__)
#define INTERNAL_REFERENCE_VOLTAGE 2560L
#else
#define INTERNAL_REFERENCE_VOLTAGE 1100L
#endif

// Are we using Dallas 1-wire hardware?
#ifdef USE_ONEWIRE_TEMP
#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire ds(ONEWIRE_PIN);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&ds);
#endif

/*
 * sensors_aref: measure an external voltage hooked up to the AREF pin,
 * optionally (and recommendably) through a pull-up resistor. This is
 * incompatible with all other functions that use internal references
 * (see config.h)
 */
#ifdef USE_AREF
void sensors_setup()
{
  // Nothing to set-up when AREF is in use
}

unsigned long sensors_aref()
{
  unsigned long result;
  // Read 1.1V reference against AREF (p. 262)
  ADMUX = _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = (ADCH << 8) | ADCL;

  // millivolts = 1.1 * 1024 * 1000 / result
  result = 1126400 / result;

  // aref = read aref * (32K + AREF_PULLUP) / 32K
  result = result * (32000UL + AREF_PULLUP) / 32000;

  return result;
}
#endif

#ifndef USE_AREF
#ifdef USE_ONEWIRE_TEMP
// Support for the DS18b20 temperature sensor (OneWire) 

// Call this function before using temperature data so any devices can
// be polled and the data made ready for use
void request_temperatures() {
  sensors.requestTemperatures(); // Send the command to get temperatures
}

void sensors_setup() {
  sensors.begin();                // Start the library
  delay(ONEWIRE_STARTUP_DELAY);   // Need to wait a moment?
  
  // Let's load some data so the software will be able to have data to report
  // if it needs it
  request_temperatures();
  
#ifdef DEBUG_SENS
  delay(600);  // Probably should be in config eh?
#else
  delay(100);  // Hard code a short delay here for debugging
#endif
}

int sensors_ds18b20(int sensorNumber) {
  float tempC;
  long  tempLong;
  
  tempC = sensors.getTempCByIndex(sensorNumber);         // Query specified sensor
  if (TEMP_UNIT == 3)
    tempC = DallasTemperature::toFahrenheit(tempC); // Convert to F
  
  // Do I need to do this?
  tempLong = (long)(tempC * 100.0);
  // Pass it back as an integer
  return (int)(tempLong) + CALIBRATION_VAL;
}

int sensors_ext_ds18b20() {
  return sensors_ds18b20(1);
  }
  
int sensors_int_ds18b20() {
  return sensors_ds18b20(0);
  }
#else
void sensors_setup()
{
  pinMode(INTERNAL_LM60_VS_PIN, OUTPUT);
  pinMode(EXTERNAL_LM60_VS_PIN, OUTPUT);
}

int sensors_lm60(int powerPin, int readPin)
{
  pin_write(powerPin, HIGH);      // Turn the LM60 on
  analogReference(INTERNAL);      // Ref=1.1V. Okay up to 108 degC (424 + 6.25*108 = 1100mV)
  analogRead(readPin);            // Disregard the 1st conversion after changing ref (p.256)
  delay(10);                      // This is needed when switching references
  int adc = analogRead(readPin);  // Real read
  pin_write(powerPin, LOW);       // Turn the LM60 off

  int mV = INTERNAL_REFERENCE_VOLTAGE * adc / 1024L;   // Millivolts

  switch(TEMP_UNIT) {
    case 1: // C
      // Vo(mV) = (6.25*T) + 424 -> T = (Vo - 424) * 100 / 625
      return (4L * (mV - 424) / 25) + CALIBRATION_VAL;
    case 2: // K
      // C + 273 = K
      return (4L * (mV - 424) / 25) + 273 + CALIBRATION_VAL;
    case 3: // F
      // (9/5)C + 32 = F
      return (36L * (mV - 424) / 125) + 32 + CALIBRATION_VAL;
  }
}

int sensors_ext_lm60()
{
  return sensors_lm60(EXTERNAL_LM60_VS_PIN, EXTERNAL_LM60_VOUT_PIN);
}

int sensors_int_lm60()
{
  return sensors_lm60(INTERNAL_LM60_VS_PIN, INTERNAL_LM60_VOUT_PIN);
}
#endif

int sensors_vin()
{
  analogReference(DEFAULT);      // Ref=5V
  analogRead(VMETER_PIN);        // Disregard the 1st conversion after changing ref (p.256)
  delay(10);                     // This is needed when switching references

  uint16_t adc = analogRead(VMETER_PIN); 
  
  // Check the CPU speed here
#if F_CPU > 8000000L  
  uint16_t mV = 5000L * adc / 1024;
#else  
  uint16_t mV = 3300L * adc / 1024;
#endif  
   
  // Vin = mV * R2 / (R1 + R2)
  int vin = (uint32_t)mV * (VMETER_R1 + VMETER_R2) / VMETER_R2;
  return vin;
}


#endif
#endif // ifdef AVR
