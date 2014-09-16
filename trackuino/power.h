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
 
// Added configuration file so I could set DEBUG_PIN_INVERT per board
#include "config.h"

#ifndef __POWER_H__
#define __POWER_H__

#ifdef DEBUG_PIN_INVERT
#define DEBUG_PIN_ON LOW
#define DEBUG_PIN_OFF HIGH
#else
#define DEBUG_PIN_ON HIGH
#define DEBUG_PIN_OFF LOW
#endif

void power_save();

#endif // ifndef __POWER_H__

