ESP Carillonneur
================

A project to ESP-ify the "Caroling Christmas Bells" product line from Ye Merrie Minstrel, in particular the variant with part number AUS-200.

## Goals:

* Maintain function with the existing OEM music cartridges
* Allow MIDI control over WiFi
* Allow MIDI control from local storage (SD? Flash?)

## Pinout

### Blue (Right) Bell Connector
0. `IO4` (Furthest from connector)
1. `IO33`
2. `IO25`
3. `IO27`
4. `IO26`
5. `IO32` (Closest to connector)


### Orange (Left) Bell Connector
0. `IO17` (Furthest from connector)
1. `IO19`
2. `IO22`
3. `IO21`
4. `IO18`
5. `IO16` (Closest to connector)

### IR expansion Interface
0. `IO34`
1. `IO36`
2. `IO35`
3. `IO39`

### Mainboard Detection Signals
* "Detect" (on the AUS-200, a 10k pulldown): `IO23`
* "Ref" (on the AUS-200, a 4V reference from resistor divider and IN4148): `IO5` (yup I messed up and maybe this should go on an ADC pin later)