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
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
}

void motorABack()
{
  digitalWrite(motorAIn1, HIGH);
  digitalWrite(motorAIn2, LOW);
}

void motorBStraigth()
{
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn2, HIGH);
}

void motorBBack()
{
  digitalWrite(motorBIn1, HIGH);
  digitalWrite(motorBIn2, LOW);
}

void motorAStop() {
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
}

void motorBStop() {
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn2, LOW);
}

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

void loop() {
  // put your main code here, to run repeatedly:
  // motorAstraight();
  // motorBStraigth();

  // delay(500);
  // motorAStop();
  // motorBStop();
  Serial.print("LeftIR: ");
  Serial.print(readLeftIR());

  Serial.print(" MidIR: ");
  Serial.print(readMiddleIR());

  Serial.print(" RightIR: ");
  Serial.println(readRightIR());

  delay(500);
}

