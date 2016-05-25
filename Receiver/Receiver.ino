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
// Receiver
//
// **********************************************************************************


#include <IRremote.h>

int m, s, mu=0, md=0, su=0, sd=0, l=0, lu=0, ld=0, lc=0, redLed=4, greenLed=8, zround=0, RECV_PIN=10, tx=0, timer=0, connect=1, led_status = 1;
long int time, timeStart;
IRrecv irrecv(RECV_PIN);
decode_results results;
char message[3];

// **********************************************************************************

void setup() {
    Serial.begin(19200);
    pinMode(redLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    irrecv.enableIRIn();
    connect_Zround();
}

void loop() {
  
}

// **********************************************************************************

void connect_Zround() {

    int flash = 0;
    while (connect == 1) {

        led_indicators();

        // Read Message from Serial Port
        while (Serial.available() > 0) {
            for (int i = 0; i < 3; i++) {
                message[i] = Serial.read();
                delay(50);
            }
        }

        // Message: Connection from Zround "%C&"
        if (message[0] == '%') {
            if (message[1] == 'C') {
                if (message[2] == '&') {

                    int count = 0;
                    while (count <= 20) {
                        // Message: Confirmation "%A&"
                        Serial.write("%A&");
                        delay(100);
                        count++;
                    }

                    led_status = 2;

                    message[0] = ('0');
                }
            }
        }

        // Start Practice or Race
        if (message[0] == '%') {
            if (message[1] == 'I') {
                if (message[2] == '&') {

                    timeStart = millis();
                    connect = 0;
                    timer = 1;
                    zround = 1;
                    initiate_timer();
                }
            }
        }

        delay(50);

    }

}

// **********************************************************************************

void initiate_timer() {

    while (zround == 1) {
        while (Serial.available() > 0) {
            for (int i = 0; i < 3; i++) {
                message[i] = Serial.read();
                delay(50);
            }
        }

        led_status = 4;
        led_indicators();

        timeStart = millis();
        timer = 1;

        while (timer == 1) {

            time = millis() - timeStart;
            m = time / 60000;
            mu = m % 10;
            md = (m-mu) / 10;
            s = (time/1000) - (m*60);
            su = s % 10;
            sd = (s-su) / 10;
            l = time - (s*1000) - (m*60000);
            lu = l % 10;
            ld = ((l-lu) / 10) % 10;
            lc = (l - (ld*10) - lu) / 100;


            if ( su == 0) {

                if (lu == 0 && ld == 0 && lc == 0) {
                    Serial.print("%T");
                    Serial.print(time,HEX);
                    Serial.println("&");
                }

            }

            if (su == 5) {

                if (lu == 0 && ld == 0 && lc == 0) {
                    Serial.print("%T");
                    Serial.print(time,HEX);
                    Serial.println("&");
                }

            }

            if (irrecv.decode(&results)) {
                lap_counter();
                irrecv.resume();
            }

            while (Serial.available() > 0) {

                for (int i = 0; i < 3; i++) {
                    message[i] = Serial.read();
                    delay(50);
                }

            }

            // Check if Practice or Race has Ended
            if (message[0] == '%') {

                if (message[1] == 'F') {

                    if (message[2] == '&') {
                        timer = 0;
                        digitalWrite(redLed,LOW);
                        digitalWrite(greenLed,LOW);
                        connect = 1;
                        zround = 0;

                        led_status = 3;

                        connect_Zround();
                    }
                }
            }

        }

        delay(10);

    }
}

// **********************************************************************************

void lap_counter() {
  
    check_transponder();
    if (tx!=0) {
        digitalWrite(redLed, HIGH);
        Serial.print("%L");
        Serial.print(tx, HEX);
        Serial.print(",");
        Serial.print(time, HEX);
        Serial.print("&");
        Serial.println();
        digitalWrite(redLed, LOW);
        tx=0;
    }
}

// **********************************************************************************

void led_indicators() {

    switch (led_status) {

        case 1: // Standby
            digitalWrite(redLed,HIGH);
            digitalWrite(greenLed,LOW);
            delay(200);
            digitalWrite(redLed,LOW);
            digitalWrite(greenLed,LOW);
            delay(700);
            break;
        case 2: { // Connecting
                int blink = 0;
                while (blink <= 5) {
                    digitalWrite(redLed,HIGH);
                    delay(200);
                    digitalWrite(redLed,LOW);
                    delay(200);
                    blink++;
                }
                digitalWrite(redLed,HIGH);
                digitalWrite(greenLed,LOW);
                led_status = 3;
                break;
            }
        case 3: // Connected
            digitalWrite(redLed,HIGH);
            digitalWrite(greenLed,LOW);
            break;
        case 4: // Race
            digitalWrite(redLed,LOW);
            digitalWrite(greenLed,HIGH);
            break;
    }

}

// **********************************************************************************

void check_transponder() {

    // Backward compatibility
    // Keeping this here in case you don't want to re flash your existing transponder.
    if (results.value >= 0xFFFF01 && results.value <= 0xFFFF12) {
        switch (results.value) {
            case 0x00FFFF01: tx=23; break;
            case 0x00FFFF02: tx=24; break;
            case 0x00FFFF03: tx=25; break;
            case 0x00FFFF04: tx=26; break;
            case 0x00FFFF05: tx=27; break;
            case 0x00FFFF06: tx=28; break;
            case 0x00FFFF07: tx=29; break;
            case 0x00FFFF08: tx=30; break;
            case 0x00FFFF09: tx=31; break;
            case 0x00FFFF0A: tx=32; break;
            case 0x00FFFF0B: tx=33; break;
            case 0x00FFFF0C: tx=34; break;
            case 0x00FFFF0D: tx=35; break;
            case 0x00FFFF0E: tx=36; break;
            case 0x00FFFF0F: tx=37; break;
            case 0x00FFFF10: tx=38; break;
            case 0x00FFFF11: tx=39; break;
            case 0x00FFFF12: tx=40; break;
        }
    
    // New transponder codes
    // The transponder codes are a 2 byte HEX code which
    // can range from 0x1000 to 0xFFFF
    //
    } else if (results.value >= 0x1000 && results.value <= 0xFFFF) {
      tx = results.value;
    }

    irrecv.resume();
}
