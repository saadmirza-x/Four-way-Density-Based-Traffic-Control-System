#include <Wire.h>

const int numDirections = 4;  // Number of directions being monitored
int triggerPins[numDirections] = {2, 3, 4, 5};
int echoPins[numDirections] = {6, 7, 8, 9};

const int I2C_SLAVE_ADDRESS = 8;  // I2C address of the slave Arduino

void setup() {
    Serial.begin(9600);
    Wire.begin();  // Initialize I2C communication as a master

    // Initialize trigger pins as outputs
    for (int i = 0; i < numDirections; i++) {
        pinMode(triggerPins[i], OUTPUT);
    }

    // Initialize echo pins as inputs
    for (int i = 0; i < numDirections; i++) {
        pinMode(echoPins[i], INPUT);
    }
}

long measureDistance(int triggerPin, int echoPin) {
    // Send a 10 microsecond pulse to the trigger pin
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    
    // Read the pulse duration from the echo pin
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance in centimeters
    long distance = (duration / 2) / 29.1;
    return distance;
}

void loop() {
    long distances[numDirections];
    
    // Measure distances in each direction
    for (int i = 0; i < numDirections; i++) {
        distances[i] = measureDistance(triggerPins[i], echoPins[i]);
        Serial.print("Direction ");
        Serial.print(i);
        Serial.print(": Distance = ");
        Serial.print(distances[i]);
        Serial.println(" cm");
    }

    // Calculate traffic light times based on distances
    int greenTimes[numDirections];
    for (int i = 0; i < numDirections; i++) {
        if (distances[i] <= 10) {  // Object within 10 cm
            greenTimes[i] = 10;  // Increase green light time to 10 seconds
        } else {
            greenTimes[i] = 5;  // Default green light time 5 seconds
        }
        Serial.print("Direction ");
        Serial.print(i);
        Serial.print(": Green Time = ");
        Serial.println(greenTimes[i]);
    }
    
    // Send the green times to the slave Arduino via I2C
    Wire.beginTransmission(I2C_SLAVE_ADDRESS);
    for (int i = 0; i < numDirections; i++) {
        Wire.write(greenTimes[i]);  // Send green time for each direction
    }
    Wire.endTransmission();
    
    // Delay before next loop
    delay(1000); // Wait 1 second before re-measuring
}
