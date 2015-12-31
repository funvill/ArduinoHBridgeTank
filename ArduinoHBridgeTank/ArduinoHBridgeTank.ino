
const int SETTING_BAUD_RATE                 = 9600 ; 

const unsigned char MOTOR_A_PIN_I1        = 5 ; 
const unsigned char MOTOR_A_PIN_I2        = 6 ; 
const unsigned char MOTOR_A_PIN_SPEED     = 4 ; 
const unsigned char MOTOR_B_PIN_I1        = 8 ; 
const unsigned char MOTOR_B_PIN_I2        = 7 ; 
const unsigned char MOTOR_B_PIN_SPEED     = 3 ; 

#define DEBUG_SERAL   Serial 

class CMotor {
  private: 
    unsigned char speedPin ; 
    unsigned char i1Pin ;
    unsigned char i2Pin ; 

    unsigned char currentSpeed; 
    unsigned char motorDirection ; 

    void Run() {
      // Set the direction. 
      switch( this->motorDirection ) {
        case FORWARD: {
            digitalWrite(this->i1Pin,HIGH); // DC motor rotates clockwise
            digitalWrite(this->i2Pin,LOW);          
          break ; 
        }
        case BACKWARD: {
            digitalWrite(this->i1Pin,LOW); // DC motor rotates counter-clockwise
            digitalWrite(this->i2Pin,HIGH);          
          break ; 
        }        
        default: 
        case STOP: {
            digitalWrite(this->i1Pin,LOW); // DC motor stop 
            digitalWrite(this->i2Pin,LOW);          
          break ; 
        }
      }
      // Set the speed. 
      analogWrite(this->speedPin,currentSpeed);       
    }
  
  public:

    enum {
       FORWARD = 1,
       BACKWARD = 2,
       STOP = 3 
    };
  
    void Init( unsigned char speedPin, unsigned char i1Pin, unsigned char i2Pin ) {
      this->speedPin = speedPin ; 
      this->i1Pin = i1Pin ; 
      this->i2Pin = i2Pin ; 

      pinMode(this->speedPin,OUTPUT);
      pinMode(this->i1Pin,OUTPUT); 
      pinMode(this->i2Pin,OUTPUT);

      this->SetSpeed( 255 ) ; 
      this->SetDirection( FORWARD ); 
    }

    void SetSpeed( unsigned char newSpeed ) {
      this->currentSpeed = newSpeed ; 
    }

    void SetDirection( unsigned char motorDirection ) {
      this->motorDirection = motorDirection ; 
    }

    void Go( unsigned char motorDirection, unsigned char newSpeed ){
      this->SetDirection(motorDirection);
      this->SetSpeed(newSpeed);      
      this->Run(); 
    }

    void Go( unsigned char motorDirection ){
      this->SetDirection(motorDirection);
      this->Run(); 
    }
    void Go() {
      this->Run(); 
    }


}; 

CMotor motorA;
CMotor motorB;

static unsigned char inputState ; 

void setup() {
  Serial.begin(SETTING_BAUD_RATE); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }  
  DEBUG_SERAL.println("FYI: Starting....");
  
  motorA.Init( MOTOR_A_PIN_SPEED, MOTOR_A_PIN_I1, MOTOR_A_PIN_I2 ) ; 
  motorB.Init( MOTOR_B_PIN_SPEED, MOTOR_B_PIN_I1, MOTOR_B_PIN_I2 ) ; 

  inputState = 0 ; 
}

// Input via serial 
//    motor, Direction, speed, \n
// 
// Example: 
//    "1,1,255\n" == Motor 1, Forward, full speed 
//    "1,2,255\n" == Motor 1, Backward, full speed 
//    "1,3,255\n" == Motor 1, Stop
//    "2,1,255\n" == Motor 2, Forward, full speed 
//    "2,2,255\n" == Motor 2, Backward, full speed 
//    "2,3,255\n" == Motor 2, Stop

void loop()
{
  CheckInput();   
}

void CheckInput() {
  while (Serial.available() > 0) {
    int motorID = Serial.parseInt();
    int motorDirection = Serial.parseInt();
    int motorSpeed = Serial.parseInt();
    DEBUG_SERAL.println("FYI: Set Motor ID="+ String( motorID ) + ", Direction="+  String( motorDirection )+", Speed=" + String( motorSpeed ) );

    if (Serial.read() == '\n') {
      switch( motorID ) {
        case 1: {
          motorA.Go( motorDirection, motorSpeed ); 
          break ; 
        }
        case 2: {
          motorB.Go( motorDirection, motorSpeed ); 
          break ; 
        }
        default: {
          DEBUG_SERAL.println("Error: unknown motorID="+String(motorID) );         
          break ; 
        }
      }
    }
  }
}
