/*
 * DigitalPin.cpp - Copyright (c) 2014-2020 - Olivier Poncet
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
#include "DigitalPin.h"

// ---------------------------------------------------------------------------
// DigitalPin_Traits
// ---------------------------------------------------------------------------

uint8_t DigitalPin_Traits::fakeModeRegister   = 0;
uint8_t DigitalPin_Traits::fakeInputRegister  = 0;
uint8_t DigitalPin_Traits::fakeOutputRegister = 0;

uint8_t DigitalPin_Traits::getPinPort(const uint8_t pin)
{
    if(pin == static_cast<uint8_t>(-1)) {
        return NOT_A_PORT;
    }
    return digitalPinToPort(pin);
}

uint8_t DigitalPin_Traits::getPinMask(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return 0;
    }
    return digitalPinToBitMask(pin);
}

uint8_t DigitalPin_Traits::getPinTimer(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return NOT_ON_TIMER;
    }
    return digitalPinToTimer(pin);
}

volatile uint8_t* DigitalPin_Traits::getModeRegister(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return &fakeModeRegister;
    }
    return portModeRegister(port);
}

volatile uint8_t* DigitalPin_Traits::getInputRegister(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return &fakeInputRegister;
    }
    return portInputRegister(port);
}

volatile uint8_t* DigitalPin_Traits::getOutputRegister(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return &fakeOutputRegister;
    }
    return portOutputRegister(port);
}

uint8_t DigitalPin_Traits::getInterruptNumber(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return NOT_AN_INTERRUPT;
    }
    return digitalPinToInterrupt(pin);
}

bool DigitalPin_Traits::hasPWM(const uint8_t pin)
{
    const uint8_t port = getPinPort(pin);

    if(port == NOT_A_PORT) {
        return false;
    }
    return digitalPinHasPWM(pin);
}

// ---------------------------------------------------------------------------
// DigitalPin
// ---------------------------------------------------------------------------

DigitalPin::DigitalPin(const uint8_t pin)
    : _wiring { Traits::getModeRegister(pin)
              , Traits::getInputRegister(pin)
              , Traits::getOutputRegister(pin)
              , Traits::getPinMask(pin)
              , pin }
{
}

void DigitalPin::setup(const uint8_t pin_mode) const
{
    switch(pin_mode) {
        case INPUT:
            *_wiring.mreg &= ~_wiring.mask;
            *_wiring.oreg &= ~_wiring.mask;
            break;
        case OUTPUT:
            *_wiring.mreg |=  _wiring.mask;
            *_wiring.oreg &= ~_wiring.mask;
            break;
        case INPUT_PULLUP:
            *_wiring.mreg &= ~_wiring.mask;
            *_wiring.oreg |=  _wiring.mask;
            break;
        default:
            break;
    }
}

bool DigitalPin::read(const bool pin_high) const
{
    const bool pin_data = ((*_wiring.ireg & _wiring.mask) != 0);

    return pin_data || pin_high;
}

bool DigitalPin::write(const bool pin_data) const
{
    if(pin_data == false) {
        *_wiring.oreg &= ~_wiring.mask;
    }
    else {
        *_wiring.oreg |=  _wiring.mask;
    }
    return pin_data;
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
