/*
 * FastIOBenchmark.ino - Copyright (c) 2014-2025 - Olivier Poncet
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
    static constexpr unsigned long SERIAL_SPEED      = 9600UL;
    static constexpr uint8_t       INPUT_PIN_NUMBER  = 2;
    static constexpr uint8_t       INPUT_PIN_MODE    = INPUT;
    static constexpr uint8_t       OUTPUT_PIN_NUMBER = LED_BUILTIN;
    static constexpr uint8_t       OUTPUT_PIN_MODE   = OUTPUT;
    static constexpr unsigned long RUN_COUNT         = 1000000UL;
};

// ---------------------------------------------------------------------------
// prototypes
// ---------------------------------------------------------------------------

extern void benchmarkSlowReader ( Stream&             stream
                                , const uint8_t       pin_number
                                , const uint8_t       pin_mode
                                , const unsigned long run_count );

extern void benchmarkSlowWriter ( Stream&             stream
                                , const uint8_t       pin_number
                                , const uint8_t       pin_mode
                                , const unsigned long run_count );

extern void benchmarkFastReader ( Stream&             stream
                                , const uint8_t       pin_number
                                , const uint8_t       pin_mode
                                , const unsigned long run_count );

extern void benchmarkFastWriter ( Stream&             stream
                                , const uint8_t       pin_number
                                , const uint8_t       pin_mode
                                , const unsigned long run_count );

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------

void setup()
{
    Serial.begin(Setup::SERIAL_SPEED);
}

// ---------------------------------------------------------------------------
// loop
// ---------------------------------------------------------------------------

void loop()
{
    benchmarkSlowReader ( Serial
                        , Setup::INPUT_PIN_NUMBER
                        , Setup::INPUT_PIN_MODE
                        , Setup::RUN_COUNT );

    benchmarkSlowWriter ( Serial
                        , Setup::OUTPUT_PIN_NUMBER
                        , Setup::OUTPUT_PIN_MODE
                        , Setup::RUN_COUNT );

    benchmarkFastReader ( Serial
                        , Setup::INPUT_PIN_NUMBER
                        , Setup::INPUT_PIN_MODE
                        , Setup::RUN_COUNT );

    benchmarkFastWriter ( Serial
                        , Setup::OUTPUT_PIN_NUMBER
                        , Setup::OUTPUT_PIN_MODE
                        , Setup::RUN_COUNT );
}

// ---------------------------------------------------------------------------
// SlowReader
// ---------------------------------------------------------------------------

struct SlowReader
{
    using PinType = uint8_t;

    static unsigned long run ( const uint8_t       pin_number
                             , const uint8_t       pin_mode
                             , const unsigned long run_count )
    {
        const PinType digitalPin(pin_number);

        const unsigned long startTime(::micros());
        if(run_count > 0) {
            bool          value = false;
            unsigned long count = run_count;
            ::pinMode(digitalPin, pin_mode);
            do {
                (void)(value = !value);
                value = ::digitalRead(digitalPin);
            } while(--count != 0);
        }
        const unsigned long endTime(::micros());
        const unsigned long elapsedTime(endTime - startTime);

        return elapsedTime;
    }
};

void benchmarkSlowReader ( Stream&             stream
                         , const uint8_t       pin_number
                         , const uint8_t       pin_mode
                         , const unsigned long run_count )
{
    const unsigned long elapsed = SlowReader::run(pin_number, pin_mode, run_count);
    const float         io_rate = 1000000.0f * static_cast<float>(run_count) / static_cast<float>(elapsed);

    stream.print(F("Slow reader pin number : "));
    stream.println(pin_number);
    stream.print(F("Slow reader pin mode   : "));
    stream.println(pin_mode);
    stream.print(F("Slow reader elapsed us : "));
    stream.println(elapsed);
    stream.print(F("Slow reader read/sec   : "));
    stream.println(io_rate);
    stream.println(' ');
}

// ---------------------------------------------------------------------------
// SlowWriter
// ---------------------------------------------------------------------------

struct SlowWriter
{
    using PinType = uint8_t;

    static unsigned long run ( const uint8_t       pin_number
                             , const uint8_t       pin_mode
                             , const unsigned long run_count )
    {
        const PinType digitalPin(pin_number);

        const unsigned long startTime(::micros());
        if(run_count > 0) {
            bool          value = false;
            unsigned long count = run_count;
            ::pinMode(digitalPin, pin_mode);
            do {
                (void)(value = !value);
                ::digitalWrite(digitalPin, value);
            } while(--count != 0);
        }
        const unsigned long endTime(::micros());
        const unsigned long elapsedTime(endTime - startTime);

        return elapsedTime;
    }
};

void benchmarkSlowWriter ( Stream&             stream
                         , const uint8_t       pin_number
                         , const uint8_t       pin_mode
                         , const unsigned long run_count )
{
    const unsigned long elapsed = SlowWriter::run(pin_number, pin_mode, run_count);
    const float         io_rate = 1000000.0f * static_cast<float>(run_count) / static_cast<float>(elapsed);

    stream.print(F("Slow writer pin number : "));
    stream.println(pin_number);
    stream.print(F("Slow writer pin mode   : "));
    stream.println(pin_mode);
    stream.print(F("Slow writer elapsed us : "));
    stream.println(elapsed);
    stream.print(F("Slow writer write/sec  : "));
    stream.println(io_rate);
    stream.println(' ');
}

// ---------------------------------------------------------------------------
// FastReader
// ---------------------------------------------------------------------------

struct FastReader
{
    using PinType = DigitalPin;

    static unsigned long run ( const uint8_t       pin_number
                             , const uint8_t       pin_mode
                             , const unsigned long run_count )
    {
        const PinType digitalPin(pin_number);

        const unsigned long startTime(::micros());
        if(run_count > 0) {
            bool          value = false;
            unsigned long count = run_count;
            digitalPin.setup(pin_mode);
            do {
                (void)(value = !value);
                value = digitalPin.read();
            } while(--count != 0);
        }
        const unsigned long endTime(::micros());
        const unsigned long elapsedTime(endTime - startTime);

        return elapsedTime;
    }
};

void benchmarkFastReader ( Stream&             stream
                         , const uint8_t       pin_number
                         , const uint8_t       pin_mode
                         , const unsigned long run_count )
{
    const unsigned long elapsed = FastReader::run(pin_number, pin_mode, run_count);
    const float         io_rate = 1000000.0f * static_cast<float>(run_count) / static_cast<float>(elapsed);

    stream.print(F("Fast reader pin number : "));
    stream.println(pin_number);
    stream.print(F("Fast reader pin mode   : "));
    stream.println(pin_mode);
    stream.print(F("Fast reader elapsed us : "));
    stream.println(elapsed);
    stream.print(F("Fast reader read/sec   : "));
    stream.println(io_rate);
    stream.println(' ');
}

// ---------------------------------------------------------------------------
// FastWriter
// ---------------------------------------------------------------------------

struct FastWriter
{
    using PinType = DigitalPin;

    static unsigned long run ( const uint8_t       pin_number
                             , const uint8_t       pin_mode
                             , const unsigned long run_count )
    {
        const PinType digitalPin(pin_number);

        const unsigned long startTime(::micros());
        if(run_count > 0) {
            bool          value = false;
            unsigned long count = run_count;
            digitalPin.setup(pin_mode);
            do {
                (void)(value = !value);
                digitalPin.write(value);
            } while(--count != 0);
        }
        const unsigned long endTime(::micros());
        const unsigned long elapsedTime(endTime - startTime);

        return elapsedTime;
    }
};

void benchmarkFastWriter ( Stream&             stream
                         , const uint8_t       pin_number
                         , const uint8_t       pin_mode
                         , const unsigned long run_count )
{
    const unsigned long elapsed = FastWriter::run(pin_number, pin_mode, run_count);
    const float         io_rate = 1000000.0f * static_cast<float>(run_count) / static_cast<float>(elapsed);

    stream.print(F("Fast writer pin number : "));
    stream.println(pin_number);
    stream.print(F("Fast writer pin mode   : "));
    stream.println(pin_mode);
    stream.print(F("Fast writer elapsed us : "));
    stream.println(elapsed);
    stream.print(F("Fast writer write/sec  : "));
    stream.println(io_rate);
    stream.println(' ');
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
