//L293D
//Motor A
const int motorPin1  = 2;  // Pin 14 of L293
const int motorPin2  = 4;  // Pin 10 of L293
//Motor B
const int motorPin3  = 7; // Pin  7 of L293
const int motorPin4  = 8;  // Pin  2 of L293

const int enable1 = 5; //Pin En1
const int enable2 = 6; //pin En2

//This will run only one time.
void setup(){
 
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);  
    pinMode(enable1, OUTPUT);
    pinMode(enable2, OUTPUT);
}


void loop(){

  // Motor 1 (left)
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);

  analogWrite(enable1, 255);
  analogWrite(enable2, 255);
}
