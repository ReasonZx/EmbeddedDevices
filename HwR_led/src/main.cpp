#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>
#include <FirebaseESP8266.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define ON HIGH
#define OFF LOW

const int LED0   = 0; // Assigning Pin 1 as the name LED

String ssid = "YOUR WLAN";
String pass = "YOUR WLAN PASSW";

#define FIREBASE_DATABASE_URL "https://homewithreason-default-rtdb.firebaseio.com/"
#define FIREBASE_KEY "YOUR FIREBASE KEY"

static const String devId =  "light";
static const String lightPath = "/light/OnOff/on";

bool OnOffvalue;

FirebaseData firebaseData1;


void setup ()  
{
    delay(3000);
    //Serial.begin(9600);    

    pinMode(LED0, OUTPUT);
    
    //Serial.println("Connecting to wifi");
    // // Serial.print("SSID: ");
    // // char incomingByte = 0;
    
    // // while(1) {
    // //     if (Serial.available() > 0) {
    // //         incomingByte = Serial.read();
    // //         if(incomingByte == 13) break;
    // //         Serial.print(incomingByte);
    // //         ssid.concat(static_cast<char>(incomingByte));
    // //     }
    // // }

    // // Serial.println();
    // // delay(1000);
    // // Serial.print("PASS: ");
    // // incomingByte = 0;
    // // while (Serial.available() > 0) incomingByte = Serial.read();        //clean the Serial Buffer

    // // while(1) {
    // //     if (Serial.available() > 0) {
    // //         incomingByte = Serial.read();
    // //         if(incomingByte == 13) break;
    // //         Serial.print("*");
    // //         pass.concat(static_cast<char>(incomingByte));
    // //     }
    // // }
    
    WiFi.begin(ssid,pass);

    //Serial.print("\nConnecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        //Serial.print(".");
    }
    //Serial.println();

    //Serial.print("Connected, IP address: ");
    //Serial.println(WiFi.localIP());


    Firebase.begin(FIREBASE_DATABASE_URL, FIREBASE_KEY);
    Firebase.reconnectWiFi(true);

    if (!Firebase.beginStream(firebaseData1, lightPath))
    {
        //Serial.println("Could not begin stream");
        //Serial.println("REASON: " + firebaseData1.errorReason());
        //Serial.println();
    }
    else{
        //Serial.println("Began stream");
    }

    //Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
    
    digitalWrite (LED0, LOW);
    
}

bool Pstate = true;
bool Cstate = true;

void loop () // Code under this loop runs forever.
{
    
    // digitalWrite (LED0, HIGH); // Making LED High.
    // delay(1000);              // Some Delay
    // digitalWrite (LED0, LOW);  // Making LED LOW.
    // delay(2000);                // Some Delay
    if (Firebase.getBool(firebaseData1, lightPath)){
        //Serial.println("Data was read from firebase");
        Cstate = firebaseData1.boolData();
        if(Cstate == Pstate){
            //Serial.println("data = true");
        } 
        else{
            Pstate = Cstate;
            //Serial.println("data = false");
            if(Cstate == true){
                digitalWrite(LED0, ON);
            }
            else{
                digitalWrite(LED0, OFF);
            } 
        } 
    }
    else {
        // Serial.print("Error in getbool, ");
        // Serial.println(firebaseData1.errorReason());
    }
    //Serial.println("Looping");  
}