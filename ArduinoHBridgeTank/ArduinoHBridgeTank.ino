
const int SETTING_BAUD_RATE                 = 9600 ; 

const unsigned char MOTOR_A_PIN_I1        = 5 ; 
const unsigned char MOTOR_A_PIN_I2        = 6 ; 
const unsigned char MOTOR_A_PIN_SPEED     = 4 ; 
const unsigned char MOTOR_B_PIN_I1        = 7 ; 
const unsigned char MOTOR_B_PIN_I2        = 8 ; 
const unsigned char MOTOR_B_PIN_SPEED      = 3 ; 

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
            digitalWrite(this->i1Pin,LOW); // DC motor rotates clockwise
            digitalWrite(this->i2Pin,HIGH);          
          break ; 
        }
        case BACKWARD: {
            digitalWrite(this->i1Pin,HIGH); // DC motor rotates counter-clockwise
            digitalWrite(this->i2Pin,LOW);          
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

void setup() {
  motorA.Init( MOTOR_A_PIN_SPEED, MOTOR_A_PIN_I1, MOTOR_A_PIN_I2 ) ; 
  motorB.Init( MOTOR_B_PIN_SPEED, MOTOR_B_PIN_I1, MOTOR_B_PIN_I2 ) ; 
}

void loop()
{
  motorA.Go( CMotor::FORWARD ); 
  motorB.Go( CMotor::FORWARD );  
  delay(1000);

  motorA.Go( CMotor::BACKWARD ); 
  motorB.Go( CMotor::BACKWARD );  
  delay(1000);

  motorA.Go( CMotor::FORWARD ); 
  motorB.Go( CMotor::BACKWARD );  
  delay(1000);

  motorA.Go( CMotor::STOP ); 
  motorB.Go( CMotor::STOP );  
  delay(1000);
 
}
