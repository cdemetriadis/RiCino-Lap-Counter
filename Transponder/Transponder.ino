// **********************************************************************************
//
// RiCino v2
// Arduino Lap Counter System
// https://github.com/cdemetriadis/RiCino-Lap-Counter
//
// Original code
// by Sergio Vallejo Crespo
// http://lisergio.wordpress.com
//
// Rafactoring, translation and maintenance
// by Constantinos Demetriadis
// http://ohmylovely.com
//
// **********************************************************************************
//
// Transponder
//
// **********************************************************************************


#include "IRTinyTX.h" // Short version on IRemote library

// Transponder Code
// The transponder code is a 2 byte HEX code which
// can range from 0x1000 to 0xFFFF
#define tx 0x1000

IRsend irsend;

void setup() {
    irsend.enableIROut(38);
}

void loop() {
    irsend.sendNEC(tx, 32);
    delay(10);
}
