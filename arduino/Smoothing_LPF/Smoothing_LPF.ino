/*This code is to reduce noise and smooth out input data using low pass
  filter. This is done using fixed point arithmetic by shifting code
*/
const int numReadings = 32;

int readings[numReadings];
float smoothData[numReadings]; //In case of Beta1 int gives diff value
//signed long smoothData[numReadings];
int readIndex = 1;
float Beta1 = 0.0625; //dec it to inc smoothness
int Beta2 = 4;

int inputPin = A0;
int outputPin = 13;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
    smoothData[i] = 0;
  }

  pinMode(outputPin, OUTPUT);
  Serial.println("<Arduino is ready>");
}

void loop() {
  readings[readIndex] = analogRead(inputPin);
  Serial.print(readings[readIndex]);
  Serial.print(",");
  /*reading = analogRead(inputPin);
    Serial.print(reading);
    Serial.print(" ");*/

  reduceNoise();
  Serial.print(smoothData[readIndex]);
  Serial.print(",");

  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // Serial.println(millis());
  Serial.print("\n");
  delay(1);
}
void reduceNoise() {
  if (readIndex > 0 && readIndex < 32) {
    smoothData[readIndex] = Beta1 * readings[readIndex] \
                            + (1 - Beta1) * smoothData[readIndex - 1];
  }
  else if (readIndex == 0) {
    smoothData[readIndex] = Beta1 * readings[readIndex] \
                            +(1 - Beta1) * smoothData[31];
  }
}

/*
void reduceNoise1() {
  if (readIndex > 0 && readIndex < 32) {
    smoothData[readIndex] = (smoothData[readIndex - 1] << 4) \
                            - smoothData[readIndex - 1];
    smoothData[readIndex] += readings[readIndex];
    smoothData[readIndex] >>= 4;
  } else if (readIndex == 0) {
    smoothData[readIndex] = (smoothData[31] << 4) \
                            - smoothData[31];
    smoothData[readIndex] += readings[readIndex];
    smoothData[readIndex] >>= 4;
  }
}*/
