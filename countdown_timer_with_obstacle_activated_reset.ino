const int touchPin = 2;       
const int trigPin = 3;       
const int echoPin = 4;      
const int segments[] = {5, 6, 7, 8, 9, 10, 11}; 


int countdownValue = 9;     
const int minDistance = 10;  
const bool commonAnode = false;

const byte numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

void setup() {
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  displayDigit(countdownValue);  
}

void loop() {
  if (digitalRead(touchPin) == HIGH) {
    for (int i = countdownValue; i >= 0; i--) {
      if (isObstacleDetected()) {
        Serial.println("Obstacle detected! Resetting countdown.");
        i = countdownValue;  
      }

      displayDigit(i);
      delay(1000); 
    }

    displayError();
    delay(2000);  
    displayDigit(countdownValue); 
  }
}


void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {

    digitalWrite(segments[i], commonAnode ? !numbers[digit][i] : numbers[digit][i]);
  }
}

void displayError() {
  byte E[7] = {1, 0, 0, 1, 1, 1, 1};  
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], commonAnode ? !E[i] : E[i]);
  }
}
bool isObstacleDetected() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance <= minDistance && distance > 0;
}
