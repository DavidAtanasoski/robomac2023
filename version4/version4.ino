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

// Color sensor variables
// Define color sensor pins
#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define sensorOut 3

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 24; // Red minimum value
int redMax = 273; // Red maximum value
int greenMin = 23; // Green minimum value
int greenMax = 270; // Green maximum value
int blueMin = 18; // Blue minimum value
int blueMax = 200; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

// 0 - white; 1 - green; 2 - red; 3 - black
int prevColorState = 0;

int countGreen = 0;
int countRed = 0;

void setup() {
  
  // Motors pinMode
  pinMode(enableMotorA, OUTPUT);
  pinMode(enableMotorB, OUTPUT);
  pinMode(motorAIn1, OUTPUT);
  pinMode(motorAIn2, OUTPUT);
  pinMode(motorBIn1, OUTPUT);
  pinMode(motorBIn2, OUTPUT);

  // Color Sensor pinMode
  pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

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

  // Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(10);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(10);

  int currentColorState = getCurrentColorState(redValue, greenValue);
  Serial.println(currentColorState);

  if(currentColorState == 1 && prevColorState != 1 && countGreen < 2)
  {
    digitalWrite(13, LOW);
    countGreen++;
  }
  else if(currentColorState == 2 && countGreen == 2)
  {
    while(true)
    {
      digitalWrite(13, HIGH);
      digitalWrite(motorAIn1, LOW);
      digitalWrite(motorAIn2, LOW);
      digitalWrite(motorBIn1, LOW);
      digitalWrite(motorBIn1, LOW);
    }
  }
  else if(currentColorState == 2 && countGreen < 2)
  {
    digitalWrite(13, HIGH);
    countGreen = 0;
  }

  prevColorState = currentColorState;
}

//
// Methods:
//

int getCurrentColorState(int redVal, int greenVal)
{
  if(redVal > 235 && greenVal > 235)
  {
    // white
    return 0;
  }
  if(greenVal > redVal && greenVal > 200)
  {
    // green
    return 1;
  }
  if(redVal > greenVal && redVal > 240)
  {
    // red
    return 2;
  }
  if(redVal < 40 && greenValue < 40)
  {
    // black
    return 3;
  }
}

// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

bool checkWhite(int red, int green)
{
  if(red > 230 && green > 230)
  {
    // it is white
    return true;
  }
  return false;
}

int checkState()
{
  	// Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(10);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(10);

  if(checkWhite(redValue, greenValue))
  {
    // white
    Serial.println("WHITE");
    return 0;
  }
  else if(greenValue > redValue)
  {
    // green
    return 1;
  }
  else if(redValue > greenValue)
  {
    // red
    return 2;
  }
  else if(greenValue < 40 && redValue < 40)
  {
    // black
    return 3;
  }
}

void sequence()
{
  int currentColorState = checkState();

  if(prevColorState == 0 && currentColorState == 1 && countGreen < 2)
  {
    countGreen++;
    while(currentColorState == 1)
    {
      Serial.print("GREEN: ");
      Serial.print(countGreen);
      Serial.print(" STATE: ");
      Serial.println(currentColorState);
      currentColorState = checkState();
    }
    return;
  }

  currentColorState = checkState();
  delay(20);
  if(prevColorState == 0 && currentColorState == 2 && countGreen == 2)
  {
    Serial.println("STOP");
    return;
  }
}

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

