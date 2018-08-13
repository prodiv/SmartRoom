#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include<Servo.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "15dff993a13840a39487a8d02ecc6097";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BATMAN";
char pass[] = "12345678";
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int pin=16;
int button;
void setup()
{
  // Debug console
  Serial.begin(9600);
myservo.attach(pin);  // attaches the servo on pin 0 to the servo object 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
BLYNK_WRITE(V3) {  
  button = param.asInt();  
  if(button==1)
  {
   for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  
  }
 else if(button==0)
  {
   // for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  //{                                
    myservo.write(10);              // tell servo to go to position in variable 'pos' 
   // delay(15);                       // waits 15ms for the servo to reach the position 
  //} }
 }
}  
 
void loop()
{
  Blynk.run();
}
