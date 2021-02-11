#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>


const int LED   = 1; // Assigning Pin 1 as the name LED
String ssid;
String pass;

void setup ()  
{
    delay(3000);
    Serial.begin(9600);    
    Serial.println("Connecting to wifi");
    Serial.print("SSID: ");
    char incomingByte = 0;
    
    while(1) {
        if (Serial.available() > 0) {
            incomingByte = Serial.read();
            if(incomingByte == 13) break;
            Serial.print(incomingByte);
            ssid.concat(static_cast<char>(incomingByte));
        }
    }

    Serial.println();
    delay(1000);
    Serial.print("PASS: ");
    incomingByte = 0;
    while (Serial.available() > 0) incomingByte = Serial.read();        //clean the Serial Buffer

    while(1) {
        if (Serial.available() > 0) {
            incomingByte = Serial.read();
            if(incomingByte == 13) break;
            Serial.print("*");
            pass.concat(static_cast<char>(incomingByte));
        }
    }
    
    WiFi.begin(ssid,pass);

    Serial.print("\nConnecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    
}



void loop () // Code under this loop runs forever.
{
    //digitalWrite (LED, HIGH); // Making LED High.
    delay(1000);              // Some Delay
    //digitalWrite (LED, LOW);  // Making LED LOW.
    //delay(2000);              // Some Delay
    Serial.println("Looping");  
}