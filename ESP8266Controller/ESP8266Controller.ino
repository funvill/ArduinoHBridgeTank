#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YOUR_AUTHCODE"; // Put your Auth Token here. (see Step 3 above)
char ssid[] = "YOUR_SSID";
char password[] = "YOUR_PASSWORD!";

int ledState = LOW;  
unsigned long previousMillis = 0;
const long interval = 1000*1;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  
  Serial.print("1,3,0\n2,3,0\n"); // Stop 
}

void loop()
{
  Blynk.run(); 

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW) { 
      ledState = HIGH;  // Note that this switches the LED *off*
    } else {
      ledState = LOW;   // Note that this switches the LED *on*
    }    
    digitalWrite(BUILTIN_LED, ledState);        
  }
}

// Speed and direction 
BLYNK_WRITE(V0) {
  int y = param.asInt();

  if( y > 100 && y < 150  ) {
    // Stop 
    Serial.print("1,3,0\n");
  } else {
    unsigned char motorSpeed = y ; 
    unsigned char motorDirection = 1 ; // Forward 
    
    if( y > 128 ) { 
      motorSpeed = map(y, 128, 255, 0, 255 ); 
      motorDirection = 1 ; // Forward 
    } else {
      motorSpeed = map(y, 128, 0, 0, 255 ); 
      motorDirection = 2 ; // backwards  
    }
    Serial.print("1,"+ String(motorDirection) +","+ String(motorSpeed) +"\n");
  }
}

// Speed and direction 
BLYNK_WRITE(V1) {
  int y = param.asInt();

  if( y > 100 && y < 150  ) {
    // Stop 
    Serial.print("2,3,0\n");
  } else {
    unsigned char motorSpeed = y ; 
    unsigned char motorDirection = 1 ; // Forward 
    
    if( y > 128 ) { 
      motorSpeed = map(y, 128, 255, 0, 255 ); 
      motorDirection = 1 ; // Forward 
    } else {
      motorSpeed = map(y, 128, 0, 0, 255 ); 
      motorDirection = 2 ; // backwards  
    }
    Serial.print("2,"+ String(motorDirection) +","+ String(motorSpeed) +"\n");
  }
}
