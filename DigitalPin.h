/*
 * DigitalPin.h - Copyright (c) 2014-2020 - Olivier Poncet
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
#ifndef __INO_FASTIO_DigitalPin_h__
#define __INO_FASTIO_DigitalPin_h__

// ---------------------------------------------------------------------------
// DigitalPin_Traits
// ---------------------------------------------------------------------------

struct DigitalPin_Traits
{
    static uint8_t fakeModeRegister;
    static uint8_t fakeInputRegister;
    static uint8_t fakeOutputRegister;

    static          uint8_t  getPinPort         ( const uint8_t pin );
    static          uint8_t  getPinMask         ( const uint8_t pin );
    static          uint8_t  getPinTimer        ( const uint8_t pin );
    static volatile uint8_t* getModeRegister    ( const uint8_t pin );
    static volatile uint8_t* getInputRegister   ( const uint8_t pin );
    static volatile uint8_t* getOutputRegister  ( const uint8_t pin );
    static          uint8_t  getInterruptNumber ( const uint8_t pin );
    static          bool     hasPWM             ( const uint8_t pin );
};

// ---------------------------------------------------------------------------
// DigitalPin_Wiring
// ---------------------------------------------------------------------------

struct DigitalPin_Wiring
{
    volatile uint8_t* mreg;
    volatile uint8_t* ireg;
    volatile uint8_t* oreg;
    uint8_t           mask;
    uint8_t           pin;
};

// ---------------------------------------------------------------------------
// DigitalPin
// ---------------------------------------------------------------------------

class DigitalPin
{
public: // public interface
    DigitalPin(const uint8_t pin);

    void setup ( const uint8_t pin_mode ) const;

    bool read  ( const bool pin_high = false ) const;

    bool write ( const bool pin_data = false ) const;

    uint8_t pin() const
    {
        return _wiring.pin;
    }

    uint8_t getInterruptNumber() const
    {
        return Traits::getInterruptNumber(_wiring.pin);
    }

    bool hasPWM() const
    {
        return Traits::hasPWM(_wiring.pin);
    }

protected: // protected interface
    using Traits = DigitalPin_Traits;
    using Wiring = DigitalPin_Wiring;

protected: // protected data
    Wiring const _wiring;
};

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __INO_FASTIO_DigitalPin_h__ */
