#include <Arduino.h>
#include <ESP8266WiFi.h>

const int LED   = 1; // Assigning Pin 4 as the name LED
const int LED2  = 4; // Assigning Pin 4 as the name LED
void setup ()  
{
     pinMode (LED, OUTPUT); // Declaring LED pin as an output.
     pinMode (LED2, OUTPUT); // Declaring LED pin as an output.   
     //Serial.begin(115200);  
}



void loop () // Code under this loop runs forever.
{
    digitalWrite (LED, HIGH); // Making LED High.
    digitalWrite (LED2, HIGH); // Making LED High. 
    //Serial.println("HI ");  
    delay(1000);              // Some Delay
    digitalWrite (LED, LOW);  // Making LED LOW.
    digitalWrite (LED2, LOW); // Making LED High.
    //Serial.println("LO ");  
    delay(2000);              // Some Delay
}