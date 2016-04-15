// **********************************************************************************
//
// RiCino
// Arduino Lap Counter System
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

// IR code list
#define tx23 0x00FFFF01
#define tx24 0x00FFFF02
#define tx25 0x00FFFF03
#define tx26 0x00FFFF04
#define tx27 0x00FFFF05
#define tx28 0x00FFFF06
#define tx29 0x00FFFF07
#define tx30 0x00FFFF08
#define tx31 0x00FFFF09
#define tx32 0x00FFFF0A
#define tx33 0x00FFFF0B
#define tx34 0x00FFFF0C
#define tx35 0x00FFFF0D
#define tx36 0x00FFFF0E
#define tx37 0x00FFFF0F
#define tx38 0x00FFFF10
#define tx39 0x00FFFF11
#define tx40 0x00FFFF12

IRsend irsend;

void setup() {
    irsend.enableIROut(38);
}

void loop() {
    // Select which Tx to issue from the list above
    irsend.sendNEC(tx23, 32);
    delay(10);
}
