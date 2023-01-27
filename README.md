ESP Carillonneur
================

A project to ESP-ify the "Caroling Christmas Bells" product line from Ye Merrie Minstrel, in particular the variant with part number AUS-200.

## Goals:

* Maintain function with the existing OEM music cartridges
* Allow MIDI control over WiFi
* Allow MIDI control from local storage (SD? Flash?)

## Pinout

### Blue (Right) Bell Connector
0. `IO23` (Furthest from connector)
1. `IO21`
2. `IO18`
3. `IO5`
4. `IO19`
5. `IO22` (Closest to connector)


### Orange (Left) Bell Connector
0. `IO16` (Furthest from connector)
1. `IO4`
2. `IO26`
3. `IO25`
4. `IO27`
5. `IO17` (Closest to connector)

### IR expansion Interface
0. `IO32`
1. `IO34`
2. `IO33`
3. `IO35`

### Mainboard Detection Signals
* "Detect" (on the AUS-200, a 10k pulldown): `IO39`
* "Ref" (on the AUS-200, a 4V reference from resistor divider and IN4148): `IO36`