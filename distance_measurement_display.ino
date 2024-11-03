int segmentA = 2;
int segmentB = 3;
int segmentC = 4;
int segmentD = 5;
int segmentE = 6;
int segmentF = 7;
int segmentG = 8;

// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Function to display a number (0-9) on the 7-segment display
void displayDigit(int number) {
    // Segment patterns for numbers 0-9 (1 = ON, 0 = OFF)
    // a b c d e f g
    bool digits[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    digitalWrite(segmentA, digits[number][0]);
    digitalWrite(segmentB, digits[number][1]);
    digitalWrite(segmentC, digits[number][2]);
    digitalWrite(segmentD, digits[number][3]);
    digitalWrite(segmentE, digits[number][4]);
    digitalWrite(segmentF, digits[number][5]);
    digitalWrite(segmentG, digits[number][6]);
}

void setup() {
    // Set segment pins as output
    pinMode(segmentA, OUTPUT);
    pinMode(segmentB, OUTPUT);
    pinMode(segmentC, OUTPUT);
    pinMode(segmentD, OUTPUT);
    pinMode(segmentE, OUTPUT);
    pinMode(segmentF, OUTPUT);
    pinMode(segmentG, OUTPUT);

    // Set ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
}

void loop() {
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo pin
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance in cm
    int distance = duration * 0.034 / 2;

    // Limit distance to a single digit (0-9) for display
    int displayDistance = distance % 10;

    // Display distance on the 7-segment display
    displayDigit(displayDistance);

    // Print distance to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500);
}