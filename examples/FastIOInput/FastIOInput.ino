/*
 * FastIOInput.ino - Copyright (c) 2014-2020 - Olivier Poncet
 *
 * This file is part of the FastIO library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Arduino.h>
#include <DigitalPin.h>

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------

struct Setup
{
    static constexpr unsigned long SERIAL_SPEED = 9600UL;
    static constexpr unsigned long LOOP_DELAY   = 1000UL;
    static constexpr uint8_t       PIN_NUMBER   = A0;
    static constexpr uint8_t       PIN_MODE     = INPUT;
};

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

const DigitalPin digitalPin(Setup::PIN_NUMBER);

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------

void setup()
{
    Serial.begin(Setup::SERIAL_SPEED);
    digitalPin.setup(Setup::PIN_MODE);
}

// ---------------------------------------------------------------------------
// loop
// ---------------------------------------------------------------------------

void loop()
{
    Serial.print(F("pin number : "));
    Serial.println(Setup::PIN_NUMBER);
    Serial.print(F("pin mode   : "));
    Serial.println(Setup::PIN_MODE);
    Serial.print(F("pin value  : "));
    Serial.println(digitalPin.read());
    Serial.println(' ');
    ::delay(Setup::LOOP_DELAY);
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
