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

#if defined(AVR) && !defined(__AVR_ATmega32U4__)

#ifndef __AFSK_AVR_H__
#define __AFSK_AVR_H__

#include <stdint.h>
#include <avr/pgmspace.h>
#include "config.h"

#define AFSK_ISR ISR(TIMER2_OVF_vect)

// Exported consts
extern const uint32_t MODEM_CLOCK_RATE;
extern const uint8_t REST_DUTY;
extern const uint16_t TABLE_SIZE;
extern const uint32_t PLAYBACK_RATE;

// Exported vars
extern const uint8_t afsk_sine_table[] PROGMEM;

#if AUDIO_PIN == 3
#  define OCR2 OCR2B
#elif AUDIO_PIN == 11
#  define OCR2 OCR2A
#else
#  error "Only AUDIO_PIN 3 and 11 are supported for AVR processors."
#endif

// Inline functions (this saves precious cycles in the ISR)
inline uint8_t afsk_read_sample(int phase)
{
  return pgm_read_byte_near(afsk_sine_table + phase);
}

inline void afsk_output_sample(uint8_t s)
{
  OCR2 = s;
}

inline void afsk_clear_interrupt_flag()
{
  // atmegas don't need this as opposed to pic32s.
}

#ifdef DEBUG_MODEM
inline uint16_t afsk_timer_counter()
{
  uint16_t t = TCNT2;
  if ((TIFR2 & _BV(TOV2)) && t < 128)
    t += 256;
  return t;
}

inline int afsk_isr_overrun()
{
  return (TIFR2 & _BV(TOV2));
}
#endif


// Exported functions
void afsk_setup();
void afsk_send(const uint8_t *buffer, int len);
void afsk_start();
bool afsk_flush();
void afsk_isr();
void afsk_timer_setup();
void afsk_timer_start();
void afsk_timer_stop();
void afsk_enable(bool status);
#ifdef DEBUG_MODEM
void afsk_debug();
#endif

#endif
#endif // AVR
