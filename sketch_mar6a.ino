//GLOBAL VARIABLES
//Yellow -- 3350 - 3450

int _analogPin = A0;
int curr = 0;
int avg = 0;


//PIN FUNCTIONS

void setPins(int arr[], int size, bool dir) {
  for (int i = 0; i < size; i++) {
    pinMode(arr[i], dir);
  }
}

//LED FUNCTIONS

void setPattern(int led[], int size, int pattern, int del) {
  for (int i = 0; i < size; i++) {
    digitalWrite(led[i], (pattern >> i) & 1);
    delay(del);
  }
}

void flicker(int led[], int size, int count, int del) {
  for (int i = 0; i < count; i++) {
    setPattern(led, size, i % 2 * 15, 0);
    delay(del);
  }
}

//ANALOG FUNCTIONS

int poll(int pin, int times, int del) {
  int sum = 0;
  for (int i = 0; i < times; i++) {
    sum += analogRead(pin);
  }
  return sum / times;
}

void setup() {
  analogReadResolution(12);
}

void loop() {
  int readVal = analogRead(_analogPin);

  avg += readVal / 1024;
  if (!(curr++ % 1024)) {
    Serial.print(readVal);
    Serial.println();
  }
}
