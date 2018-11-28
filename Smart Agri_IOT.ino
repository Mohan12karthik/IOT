#include <Wire.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const char* ssid = "ESPsoftAP_01";
const char* password = "12345678";
WiFiClient client;
unsigned long myChannelNumber =  632961;
const char * myWriteAPIKey = "9EQAAYD8L82TBVGX";
int moist=1;

int state = 1;


void setup() {
  Serial.begin(115200);
  pinMode(D6,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
    pinMode(D7,OUTPUT);
  digitalWrite(D7,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  if(!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);


  Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
// Print the IP address
Serial.println(WiFi.localIP());
ThingSpeak.begin(client);
}
 

void loop() {
  
  digitalWrite(D7,LOW);
    sensors_event_t event; 
  accel.getEvent(&event);
 
float a=(event.acceleration.z)/9.8;
  if(digitalRead(D5)== LOW)
  {
     
    Serial.println(analogRead(A0));
  if(analogRead(A0)>500) // put your main code here, to run repeatedly:

    { 
      if(a<0.0)
      {
          Serial.println("up");
          digitalWrite(D7,HIGH);
          delay(300);
          digitalWrite(D7,LOW);
           delay(300);
           digitalWrite(D7,HIGH);
          delay(300);
          digitalWrite(D7,LOW);
           delay(300);
           digitalWrite(D7,HIGH);
          delay(300);
          digitalWrite(D7,LOW);
           delay(300);
           digitalWrite(D7,HIGH);
          delay(300);
          digitalWrite(D7,LOW);
      }
  else
  {
  Serial.println("down");
   digitalWrite(D7,LOW);
  }
  delay(10);
      Serial.println("BRIGHT");
      if(analogRead(A0)>900)
    {
      digitalWrite(D6,HIGH);
      digitalWrite(D3,LOW);
      digitalWrite(D4,LOW);
      
    }

    else if(analogRead(A0)>600)
    {
       digitalWrite(D6,HIGH);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,LOW);
      
    }
    else
    {
      digitalWrite(D6,LOW);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,HIGH);
    
    }
    }
    else
    {
    Serial.println("Moisture level is perfect");
       digitalWrite(D6,LOW);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,LOW);
    }
    
  }
  else
  Serial.println("Dark");


  if (state==1) {
    moist=analogRead(A0);
ThingSpeak.writeField(myChannelNumber, 1, moist, myWriteAPIKey);
state = state+1;
 // val1 prints a set of odd numbers
Serial.println(state);
Serial.println("Channel 1 transmitted");
}
Serial.println(state);
delay(10000);

}
