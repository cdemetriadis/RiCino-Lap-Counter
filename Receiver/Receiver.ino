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
// Receiver
//
// **********************************************************************************


#include <IRremote.h>
#include <IRremoteInt.h>

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
        
        // Message: Disconnect from Zround "%D&"
        if (message[0] == '%') {
            if (message[1] == 'D') {
                if (message[2] == '&') {

                    led_status = 1;

                    message[0] = ('0');
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

    tx = results.value;
    if (tx != 0) {
        Serial.print("%L");
        Serial.print(tx, HEX);
        Serial.print(",");
        Serial.print(time, HEX);
        Serial.print("&");
        Serial.println();
        tx = 0;
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
