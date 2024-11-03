const int touchPin = 2;     
const int trigPin = 3;        
const int echoPin = 4;        
const int segments[] = {5, 6, 7, 8, 9, 10, 11}; 

const int distanceThreshold = 10;  

int counter = 0;  
bool lastObjectDetected = false; 
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
  
  displayCounter(counter);
}

void loop() {
  if (digitalRead(touchPin) == HIGH) { 
    counter = 0; 
    displayCounter(counter); 
    delay(500);
  }

  long distance = getDistance();
  
  bool objectDetected = distance < distanceThreshold;

  if (objectDetected && !lastObjectDetected) {
    counter++;
    displayCounter(counter); 
    Serial.print("Counter: ");
    Serial.println(counter);
    delay(500); 
  }
  
  lastObjectDetected = objectDetected; 
}

long getDistance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

void displayCounter(int count) {
  if (count >= 0 && count <= 9) {
    displayDigit(count); 
  } else {
    displayDigit(9); 
  }
}
void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], commonAnode ? !numbers[digit][i] : numbers[digit][i]);
  }
}
