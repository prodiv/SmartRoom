#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <SimpleTimer.h>
#define DHTTYPE DHT11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);
SimpleTimer timer;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6b9c7b13e8ec419b8b72ce1b90d633c6";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BATMAN"; //wifi name
char pass[] = "12345678"; //wifi password

int light = 13;
int fan = 12;
const int trigPin = 5; //D1
const int echoPin = 4; //D2
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  long duration;
int distance;

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(fan, OUTPUT);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(light, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2000, sendUptime);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
void sendUptime(){
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.println("Humidity and Temperature \n\n");
  Serial.print("Current Humidity = ");
  Serial.print(h);
  Serial.print(" & ");
  Serial.print("temperature = ");
  Serial.print(t);
  Blynk.virtualWrite(V0, t);
   Blynk.virtualWrite(V1, h);
}
void loop()
{

    float t=dht.readTemperature();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance : ");
  Serial.println(distance);
  if(distance < 6)
  {
    digitalWrite(light, HIGH);
    digitalWrite(fan, HIGH);
    
    Serial.print("Door has been LOCKED so power has been cut down/n");
     delay(500);
  }
  else
  {
   
    digitalWrite(light, LOW);
 
    if( t > 30)
    {
      
    digitalWrite(fan, LOW);
  
    Serial.print("Temperature is above 30 so FAN has been switched ON./n");
    delay(500);
    }
    else
    {
     
    digitalWrite(fan, LOW);
    digitalWrite(fan, HIGH);
      
    Serial.print("Temperature is below 30 so FAN has been switched OFF./n");
    }
    
     delay(500);
  }
  delay(500);
  
  
  Blynk.run();
  timer.run();
  
}
