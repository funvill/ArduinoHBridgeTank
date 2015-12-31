/* 
 ESP8266 BlinkWithoutDelay by Simon Peter
 Blink the blue LED on the ESP-01 module
 Based on the Arduino Blink without Delay example
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses BUILTIN_LED to find the pin with the internal LED
*/

int ledState = LOW;     

unsigned long previousMillis = 0;
const long interval = 1000*3;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW) { 
      ledState = HIGH;  // Note that this switches the LED *off*
      Serial.print("1,3,0\n" );
    }
    else {
      ledState = LOW;   // Note that this switches the LED *on*
      Serial.print("1,1,255\n" );      
    }
    
    digitalWrite(BUILTIN_LED, ledState);
        
  }  
}
