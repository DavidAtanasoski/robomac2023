
// Motor Enable pins
#define enableMotorA 10
#define enableMotorB 11

// Motor 1
// Explanation: 'In' means the input pin on the motor driver
// it's not input pin on the Arduino (it's actually an output)
#define motorAIn1 2
#define motorAIn2 3

// Motor 2
#define motorBIn1 4 
#define motorBIn2 5

void setup() {

  pinMode(enableMotorA, OUTPUT);
  pinMode(enableMotorB, OUTPUT);
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorBIn1, OUTPUT);
  pinMode(motorBIn2, OUTPUT);
}

void setSpeedMotorA(int speed)
{
  analogWrite(enableMotorA, speed);
}

void setSpeedMotorB(int speed)
{
  analogWrite(enableMotorB, speed);
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

void loop() {
  // put your main code here, to run repeatedly:

}
