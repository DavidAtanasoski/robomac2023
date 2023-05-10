// int pButton=0;

void setup() {

  Serial.begin(9600);

  // pinMode(pButton,INPUT);

}

void loop(){

  double sensorRead = analogRead(A0);

  Serial.println(sensorRead);

  delay(500);
}
