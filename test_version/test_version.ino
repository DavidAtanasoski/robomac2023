// #define leftMotorPin1 2 // Motor Driver pin 
// #define leftMotorPin2 4 // Motor Driver pin 
// #define rightMotorPin1 8 // Motor Driver pin
// #define rightMotorPin2 7 // Motor Driver pin

// #define leftEnable 5 // for the left Motor 
// #define rightEnable 6 // for the right Motor

// Motor Enable pins
#define enableMotorA 5
#define enableMotorB 6

// Motor 1
// Explanation: 'In' means the input pin on the motor driver
// it's not input pin on the Arduino (it's actually an output)
#define motorAIn1 2 // left
#define motorAIn2 4

// Motor 2
#define motorBIn1 8 // right
#define motorBIn2 7

#define leftIR A5 // A0 pin
#define middleIR A3 // A1 pin
#define rightIR A4 // 19-A5 pin

void setup() {
  pinMode(enableMotorA, OUTPUT);
  pinMode(enableMotorB, OUTPUT);
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorBIn1, OUTPUT);
  pinMode(motorBIn2, OUTPUT);

  Serial.begin(9600);
}

// Methods for reading IR sensors data
double readLeftIR() {
  double leftsensorRead = analogRead(leftIR);
  return leftsensorRead;
}

double readMiddleIR() {
  double midsensorRead = analogRead(middleIR);
  return midsensorRead;
}

double readRightIR() {
  double rightsensorRead = analogRead(rightIR);
  return rightsensorRead;
}

void setSpeedMotorA(int speed)
{
  analogWrite(enableMotorA, speed); // speed > 80
}

void setSpeedMotorB(int speed)
{
  analogWrite(enableMotorB, speed); // speed > 80
}

void motorAStraigth()
{
  digitalWrite(motorAIn1, HIGH);
  digitalWrite(motorAIn2, LOW);
}

void motorABack()
{
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
}

void motorBStraigth()
{
  digitalWrite(motorBIn1, HIGH);
  digitalWrite(motorBIn2, LOW);
}

void motorBBack()
{
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn2, HIGH);
}

void motorAStop() {
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
}

void motorBStop() {
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn2, LOW);
}

void printSensorData()
{
  Serial.print("LeftIR: ");
  Serial.print(discretize(readLeftIR()));

  Serial.print(" MidIR: ");
  Serial.print(discretize(readMiddleIR()));

  Serial.print(" RightIR: ");
  Serial.println(discretize(readRightIR()));
}

int discretize(int val)
{
  if (val > 300) 
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void turnRight() 
{
  motorABack();
  motorBStraigth(); 
  setSpeedMotorA(255); // -speed
  setSpeedMotorB(255); // (+speed)
}

void turnLeft() 
{
  motorAStraigth();
  motorBBack(); 
  setSpeedMotorA(255); // +speed
  setSpeedMotorB(255); // (-speed)
}

void setSpeed(int speed)
{  
  setSpeedMotorA(speed);
  setSpeedMotorB(speed);
}

void carStop()
{
  motorAStop();
  motorBStop();
}

void loop() {
  // put your main code here, to run repeatedly:

  int leftSensorData = discretize(readLeftIR());
  int midSensorData = discretize(readMiddleIR());
  int rightSensorData = discretize(readRightIR());

  printSensorData();
  
  // setSpeed(150);

  // if(leftSensorData == 0 && midSensorData == 1 && rightSensorData == 0)
  // {
  //   motorAStraigth();
  //   motorBStraigth();
  // }
  // else if((leftSensorData == 1 && midSensorData == 0 && rightSensorData == 0) || (leftSensorData == 1 && midSensorData == 1 && rightSensorData == 0))
  // {
  //   // motor 1 nazad
  //   setSpeedMotorA(100);
  //   digitalWrite(motorAIn1, LOW);
  //   digitalWrite(motorAIn2, HIGH); 

  //   // motor 2 napred
  //   setSpeedMotorB(150);
  //   digitalWrite(motorBIn1, HIGH);
  //   digitalWrite(motorBIn2, LOW); 
  // }
  // else if((leftSensorData == 0 && midSensorData == 0 && rightSensorData == 1) || (leftSensorData == 0 && midSensorData == 1 && rightSensorData == 1))
  // {
  //   setSpeedMotorA(150);
  //   digitalWrite(motorAIn1, HIGH);
  //   digitalWrite(motorAIn2, LOW); 

  //   // motor 2 napred
  //   setSpeedMotorB(100);
  //   digitalWrite(motorBIn1, LOW);
  //   digitalWrite(motorBIn2, HIGH); 
  // } 

  // }

  if (midSensorData == 1 && leftSensorData == 0 && rightSensorData == 0)
  {
    motorAStraigth();
    motorBStraigth();
    return;
  }
  else if (leftSensorData == 1 && midSensorData == 0 && rightSensorData == 0)
  {
    carStop();
    turnLeft();
  }
  else if (rightSensorData == 1 && midSensorData == 0 && leftSensorData == 0)
  {
    carStop();
    turnRight();
  }
  else 
  {
    carStop();
  }

  // setSpeedMotorA(100);
  // setSpeedMotorB(200);

  // motorAStraigth();
  // motorBStraigth();
}

