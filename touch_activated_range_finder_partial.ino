// Pin assignments
const int trigPin = 9;      // TRIG pin of ultrasonic sensor
const int echoPin = 10;     // ECHO pin of ultrasonic sensor
const int buttonPin = 2;    // Push button pin
const int segA = 3;         // 7-segment display pins
const int segB = 4;
const int segC = 5;
const int segD = 6;
const int segE = 7;
const int segF = 8;
const int segG = 11;
const int segDP = 12;       // Decimal point (optional)

// 7-segment digit patterns for numbers 0-9 (for a common cathode display)
const byte digitPatterns[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Function to display a digit on the 7-segment display
void displayDigit(int digit) {
  byte pattern = digitPatterns[digit];
  digitalWrite(segA, bitRead(pattern, 0));
  digitalWrite(segB, bitRead(pattern, 1));
  digitalWrite(segC, bitRead(pattern, 2));
  digitalWrite(segD, bitRead(pattern, 3));
  digitalWrite(segE, bitRead(pattern, 4));
  digitalWrite(segF, bitRead(pattern, 5));
  digitalWrite(segG, bitRead(pattern, 6));
}

// Function to clear the 7-segment display
void clearDisplay() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

// Setup function
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor for button

  // Set 7-segment display pins as outputs
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT); // Optional

  clearDisplay(); // Clear display initially
  Serial.begin(9600);  // Start Serial Monitor
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Convert duration to distance in cm
  return distance;
}

// Main loop
void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Button pressed
    long distance = measureDistance();
    
    // Display distance on Serial Monitor
    Serial.print("Measured Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Show the last digit of the distance on the 7-segment display
    int displayValue = distance % 10;   // Get the last digit
    displayDigit(displayValue);         // Show it on the display

    delay(5000);                        // Hold the display and Serial output for 5 seconds
    clearDisplay();                     // Clear display after 5 seconds
  }
}