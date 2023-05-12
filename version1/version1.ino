// Motor Enable pins
#define enableMotorA 5
#define enableMotorB 6

// Motor 1 - A
// Explanation: 'In' means the input pin on the motor driver
// it's not input pin on the Arduino (it's actually an output)
#define motorAIn1 2 // left
#define motorAIn2 4

// Motor 2 - B
#define motorBIn1 8 // right
#define motorBIn2 7

#define leftIR A5 // A0 pin
#define middleIR A3 // A1 pin
#define rightIR A4 // 19-A5 pin

// Motor variables
int turnSpeed = 10;
int motorSpeed = 255;

void setup() {
  
  // Motors pinMode
  pinMode(enableMotorA, OUTPUT);
  pinMode(enableMotorB, OUTPUT);
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorBIn1, OUTPUT);
  pinMode(motorBIn2, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int leftSensorVal = discretize(readLeftSensor());
  int midSensorVal = discretize(readMidSensor());
  int rightSensorVal = discretize(readRightSensor());
  
  if ((leftSensorVal == 0 && midSensorVal == 1 && rightSensorVal == 0))
  {
    setCarSpeed(motorSpeed);
    moveAStraight();
    moveBStraight();
  }

  if ((leftSensorVal == 0 && midSensorVal == 0 && rightSensorVal == 1) || (leftSensorVal == 0 && midSensorVal == 1 && rightSensorVal == 1))
  {
    // vrti desno
    setMotorSpeedA(turnSpeed); // uspori ova
    setMotorSpeedB(motorSpeed);

    moveBStraight();
    moveABack();
  }

  if ((leftSensorVal == 1 && midSensorVal == 0 && rightSensorVal == 0) || (leftSensorVal == 1 && midSensorVal == 1 && rightSensorVal == 0))
  {
    // vrti levo
    setMotorSpeedA(motorSpeed);
    setMotorSpeedB(turnSpeed); // uspori ova

    moveAStraight();
    moveBBack();
  }
}

//
// Methods:
//

void stopCar()
{
  setCarSpeed(0);
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, LOW);
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn1, LOW);
}

void setMotorSpeedA(int speed)
{
  analogWrite(enableMotorA, speed);
}

void setMotorSpeedB(int speed)
{
  analogWrite(enableMotorB, speed);
}

void setCarSpeed(int speed)
{
  analogWrite(enableMotorA, speed);
  analogWrite(enableMotorB, speed);
}

void moveAStraight()
{
  digitalWrite(motorAIn1, HIGH);
  digitalWrite(motorAIn2, LOW);
}

void moveABack()
{
  digitalWrite(motorAIn1, LOW);
  digitalWrite(motorAIn2, HIGH);
}

void moveBStraight()
{
  digitalWrite(motorBIn1, HIGH);
  digitalWrite(motorBIn2, LOW);
}

void moveBBack()
{
  digitalWrite(motorBIn1, LOW);
  digitalWrite(motorBIn2, HIGH);
}

int readLeftSensor()
{
  return analogRead(leftIR);
}

int readMidSensor()
{
  return analogRead(middleIR);
}

int readRightSensor()
{
  return analogRead(rightIR);
}

void printSensorsData()
{
  Serial.print("L: ");
  Serial.print(readLeftSensor());
  Serial.print(" M: ");
  Serial.print(readMidSensor());
  Serial.print(" R: ");
  Serial.println(readRightSensor());
}

int discretize(int val)
{
  if (val > 300)
  {
    return 1;
  }
  return 0;
}



