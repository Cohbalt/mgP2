#define led1 13
#define led2 12
#define led3 11
#define analog1 A0
#define analog2 A1
#define analog3 A2

int r1 = 0;           // reading 1
int r2 = 0;           // reading 2
int r3 = 0;           // reading 3
int Vin = 5;
float Vout1 = 0;
float Vout2 = 0;
float Vout3 = 0;
float R = 1000000;    // known resistance
float R1 = 0;         // unknown resistance
float R2 = 0;         // unknown resistance
float R3 = 0;         // unknown resistance
float buffer = 0;

void readInput(float R1, float R2, float R3) {
 
  if(R1 < 1000) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }

  if(R2 < 1000) {
    digitalWrite(led2, HIGH);
  } else {
    digitalWrite(led2, LOW);
  }

  if(R3 < 1000) {
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led3, LOW);
  }

  /*if (R2 > 350 && R2 < 450) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if (R2 > 1500 && R2 < 2000) {
    digitalWrite(led2, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if (R2 > 500 && R2 < 800) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }*/
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {

  r1 = analogRead(analog1);
  r2 = analogRead(analog2);
  r3 = analogRead(analog3);

  Serial.print(r1);
  Serial.print("   ");
  Serial.print(r2);
  Serial.print("   ");
  Serial.println(r3);

  /*if(reading) {
    buffer = reading * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R2 = R1 * buffer / 10000;
    //Serial.println(R2);
  }*/

  readInput(r1, r2, r3);

  delay(100);

}