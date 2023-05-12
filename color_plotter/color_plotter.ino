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

// 0 - white; 1 - green; 2 - red
int lastColorState = 0;

int countGreen = 0;
int countRed = 0;

int sostojba = 0;

void setup() {
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT); // interrupt pin

  // attachInterrupt(digitalPinToInterrupt(sensorOut), funkcija, CHANGE);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);



	// Setup Serial Monitor
	Serial.begin(9600);
}

void loop() {

  redPW = getRedPW();
  redValue = map(redPW, redMin, redMax, 255, 0);

  greenPW = getGreenPW();
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	blueValue = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(200);

  Serial.print("Blue:");
  Serial.print(blueValue);
  Serial.print(",");
  Serial.print("Red:");
  Serial.print(redValue);
  Serial.print(",");
  Serial.print("Green:");
  Serial.println(greenValue);

}

void funkcija()
{
  // Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);

  if(redValue > 230 && greenValue > 230)
  {
    sostojba = 0;
    return;
  }
  else if(redValue > greenValue)
  {
    sostojba = 1;
    return;
  }
  else if(redValue < greenValue)
  {
    sostojba = 2;
    return;
  }
}

void sequence()
{
  int currentColorState = checkState();

  if(lastColorState == 0 && currentColorState == 1 && countGreen < 2)
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

  if(lastColorState == 0 && currentColorState == 2 && countGreen == 2)
  {
    Serial.println("STOP");
    return;
  }
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