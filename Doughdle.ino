#define led1 2
#define led2 3
#define led3 4
#define switch1 8
#define switch2 9
#define switch3 10
#define analog1 A3
#define analog2 A4
#define analog3 A5
#define button 13

int resistances_max[] = {500, 400, 250, 300, 600};
int resistances_min[] = {450, 300, 200, 250, 500};
int numDough = 5;
bool gameOver = false;
int buttonState = false;
int score = 0;
double temp = 0;

double r1 = 0;           // reading 1
double r2 = 0;           // reading 2
double r3 = 0;           // reading 3
int Vin = 5;

// reads an analog signal corresponding the resistance between the two aluminum foil plates
int readResistance(int input) {

  if(input == 1) {
    digitalWrite(switch1, HIGH);
    int reading = analogRead(analog1);
    digitalWrite(switch1, LOW);
    return reading;
  }

  if(input == 2) {
  digitalWrite(switch2, HIGH);
  int reading = analogRead(analog2);
  digitalWrite(switch2, LOW);
  return reading;
  }

  if(input == 3) {
  digitalWrite(switch3, HIGH);
  int reading = analogRead(analog3);
  digitalWrite(switch3, LOW);
  return reading;
  }

  return 0;

}

// Oscillate LEDs in a patter for celebration
void win() {
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  for(int i = 0; i < 10; i++) {
    digitalWrite(led1, HIGH);
    delay(50);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(50);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(50);
    digitalWrite(led3, LOW);
  }

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

}

// R1-R3 are the analog readings
// R4-R6 are the number, 1-5, of the correct doughs for each spot
// controlLED changes the LED states to on if the dough matches the correct one
// and it turns the LEDs off if they do not match. If all 3 are correct, then
// set gameOver to true to end the game. 
bool controlLED(int R1, int R2, int R3, int R4, int R5, int R6) {

  bool gameOver = true;
 
  if(R1 < resistances_max[R4-1] && R1 > resistances_min[R4-1]) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
    gameOver = false;
  }

  if(R2 < resistances_max[R5-1] && R2 > resistances_min[R5-1]) {
    digitalWrite(led2, HIGH);
  } else {
    digitalWrite(led2, LOW);
    gameOver = false;
  }

  if(R3 < resistances_max[R6-1] && R3 > resistances_min[R6-1]) {
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led3, LOW);
    gameOver = false;
  }

  return gameOver;

}

/*void findResistances() {
  r1 = readResistance(1);
  delay(10);
  r2 = readResistance(2);
  delay(10);
  r3 = readResistance(3);

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
  }

  controlLED(r1, r2, r3);

  delay(100);
}*/

void setup() {

  Serial.begin(9600);

  pinMode(button, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(switch1, OUTPUT);
  pinMode(switch2, OUTPUT);
  pinMode(switch3, OUTPUT);

  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);

  randomSeed(analogRead(A3));

}

void loop() {

  Serial.println("Starting Game");

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);

  // generate 3 different random doughs that are tied to specific inputs
  int dough[] = { random(1,6), random(1,6), random(1,6) };

  while(dough[1] == dough[0]) {
    dough[2] = random(1,6);
  } 

  while(dough[2] == dough[0] || dough[2] == dough[1]) {
    dough[3] = random(1,6);
  }

  delay(1000);
  // loop guesses until the game is over
  while(!gameOver) {

    // wait for button input to check is the guess is correct
    buttonState = digitalRead(button);
    
    if(buttonState) {

      score = score + 1;

      /*temp = 0;
      for(int i = 0; i < 100; i++) {
        temp = temp + readResistance(1) / 100;
      }
      r1 = temp * 5/4;

      delay(100);

      temp = 0;
      for(int i = 0; i < 100; i++) {
        temp = temp + readResistance(2) / 100;
      }
      r2 = temp * 5/4;

      delay(100);

      temp = 0;
      for(int i = 0; i < 100; i++) {
        temp = temp + readResistance(3) / 100;
      }
      r3 = temp * 5/4; */

      r1 = readResistance(1);
      delay(100);
      r2 = readResistance(2);
      delay(100);
      r3 = readResistance(3);

      Serial.print(r1);
      Serial.print("   ");
      Serial.print(r2);
      Serial.print("   ");
      Serial.println(r3);

      Serial.print(readResistance(1));
      Serial.print("   ");
      Serial.print(readResistance(2));
      Serial.print("   ");
      Serial.println(readResistance(3));

      Serial.print(dough[0]);
      Serial.print("   ");
      Serial.print(dough[1]);
      Serial.print("   ");
      Serial.println(dough[2]);

      gameOver = controlLED(r1, r2, r3, dough[0], dough[1], dough[2]);

    }

    delay(10);

  }

  Serial.println(score);
  score = 0;

  win();

  gameOver = false;

}





















