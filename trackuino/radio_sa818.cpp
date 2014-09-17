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
#include "pin.h"
#include "radio_sa818.h"
#include <Arduino.h>


void RadioSA818::setup()
{
  // Configure pins
  pinMode(PTT_PIN,            OUTPUT);
  pinMode(AUDIO_PIN,          OUTPUT);
#ifdef RADIO_ENABLE_PIN
  pinMode(RADIO_ENABLE_PIN,   OUTPUT);
#endif

#ifdef RADIO_HL_PIN  
  pinMode(RADIO_HL_PIN,       OUTPUT);  // NEVER pull this pin high! 
#endif

  // Now set the initial values  
  pin_write(PTT_PIN,          LOW);
  
#ifdef RADIO_HL_PIN  
  pin_write(RADIO_HL_PIN,     LOW);     // Switch to low power
#endif

#if APRS_SLOT == -1
#ifdef RADIO_ENABLE_PIN
  // If time slotting is disabled, turn the radio on now (since we will
  // be transmitting shortly.
  pin_write(RADIO_ENABLE_PIN, HIGH);
#endif  
#endif
}

void RadioSA818::ptt_on()
{
  pin_write(PTT_PIN, HIGH);
  
#ifdef PTT_RAISE_DELAY  
  // According to NiceRF we should wait "hundreds of millis" to
  // allow the unit to settle down before we actually transmit
  delay(PTT_RAISE_DELAY);
#endif  
}

void RadioSA818::ptt_off()
{
  pin_write(PTT_PIN, LOW);
}


void RadioSA818::enable(bool status) 
{
#ifdef RADIO_ENABLED_PIN
  if (status) 
    pin_write(RADIO_ENABLED_PIN,  HIGH);
  else
    pin_write(RADIO_ENABLED_PIN,  LOW);
#endif	
}