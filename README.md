# FastIO library

A quite fast I/O library for Arduino.

## Abstract

This Arduino library is designed to have fast I/O on the AVR architecture with an object oriented approach at the cost of 8 bytes per pin.

## Benchmarks

Some benchmarks have been done. The benchmarking sketch is located in the `examples` directory.

### Arduino Leonardo

Here are the results of the benchmark executed on a `Arduino Leonardo` :

```
Slow reader pin number : 2
Slow reader pin mode   : 0
Slow reader elapsed us : 2527992
Slow reader read/sec   : 395570.87

Slow writer pin number : 13
Slow writer pin mode   : 1
Slow writer elapsed us : 5435128
Slow writer write/sec  : 183988.31

Fast reader pin number : 2
Fast reader pin mode   : 0
Fast reader elapsed us : 505640
Fast reader read/sec   : 1977691.62

Fast writer pin number : 13
Fast writer pin mode   : 1
Fast writer elapsed us : 1453620
Fast writer write/sec  : 687937.68
```

The results show that :

  - reading a pin with this library is approx. ~5.00x faster than `digitalRead()`
  - writing a pin with this library is approx. ~3,74x faster than `digitalWrite()`

### Arduino Mega 2560

Here are the results of the benchmark executed on a `Arduino Mega 2560` :

```
Slow reader pin number : 2
Slow reader pin mode   : 0
Slow reader elapsed us : 4967780
Slow reader read/sec   : 201297.15

Slow writer pin number : 13
Slow writer pin mode   : 1
Slow writer elapsed us : 5470796
Slow writer write/sec  : 182788.75

Fast reader pin number : 2
Fast reader pin mode   : 0
Fast reader elapsed us : 503540
Fast reader read/sec   : 1985939.50

Fast writer pin number : 13
Fast writer pin mode   : 1
Fast writer elapsed us : 1446696
Fast writer write/sec  : 691230.25
```

The results show that :

  - reading a pin with this library is approx. ~9.87x faster than `digitalRead()`
  - writing a pin with this library is approx. ~3,78x faster than `digitalWrite()`

