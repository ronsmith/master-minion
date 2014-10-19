/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

#define RELAY_PIN 8

// the setup routine runs once when you press reset:
void setup() {                
   Serial.begin(9600);
   pinMode(RELAY_PIN, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
   Serial.println("Turn ON");
   digitalWrite(RELAY_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(10000);                  // wait for 10 seconds
   Serial.println("Turn OFF");
   digitalWrite(RELAY_PIN, LOW);  // turn the LED off by making the voltage LOW
   delay(10000);                  // wait for 10 seconds
}

