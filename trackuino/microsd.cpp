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

#include "config.h"
#include "microsd.h"
#include "pin.h"
#include <Arduino.h>
#include <SdFat.h>


void microsd_setup() {
#ifdef USE_MICROSD
  // Configure pins (looks like we need to configure MOSO/SCK here too)
  pinMode(USD_CARD_DETECT, INPUT);
  pinMode(SCK,             OUTPUT);
  pinMode(MOSI,            OUTPUT);
  
#ifdef USD_LED_PIN   
  pinMode(USD_LED_PIN,     OUTPUT);
  
  // Indicate the microSD socket is in use
  pin_write(USD_LED_PIN,   HIGH);
#endif  


  // Initialize SD
  if (!sd.begin(USD_CARD_SELECT, SPI_HALF_SPEED)) {
    // Need to indicate error code here!
	while(1);
  }

 
#ifdef USD_CARD_DETECT     
  // Now we need to check to see if a card is inserted.
  if (digitalRead(USD_CARD_DETECT) == LOW) {
    // There is a card in the microSD slot.

    // Check for a configuration file 

/*	
	// (cheesy to re-use the log file variable. Maybe it should be better named?)
	if (logFile.open("AUTOEXEC.CFG", O_READ)) {
	  // Found it!  Load the configuration data and save to EEPROM
	  
	  int data;
	  while ((data = logFile.read()) >=0) Serial.write(data);
	  
	  // Close the file
	  logFile.close();
	  
	  // Need to rename the file so we don't find it again
	  if (!sd.rename("AUTOEXEC.CFG", "AUTOEXEC.$$$")) {
	    // Error.  Need to do something more here!
	    while(1);
	  }
	  // Let the watchdog reboot us here
	}
*/	  	
    // Create a new file on the microSD card
	}
#endif

#ifdef USD_LED_PIN
  // We are done setting up the microSD, turn off the activity LED
  pin_write(USD_LED_PIN,   LOW);
#endif
#endif
}