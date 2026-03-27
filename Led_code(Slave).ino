#include <Wire.h>

const int numDirections = 4;  // Number of directions being monitored

// Define the pins for LEDs
const int redPins[] = {10, 11, 12, 13}; // Digital output pins for red LEDs
const int yellowPins[] = {4, 5, 6, 7}; // Digital output pins for yellow LEDs
const int greenPins[] = {8, 9, 2, 3}; // Digital output pins for green LEDs

const int I2C_SLAVE_ADDRESS = 8;  // I2C address of the slave Arduino

// Green times received from master
int greenTimes[numDirections] = {5, 5, 5, 5};

void setup() {
    Serial.begin(9600);
    Wire.begin(I2C_SLAVE_ADDRESS);  // Initialize I2C communication as a slave
    Wire.onReceive(receiveData);  // Set up the receive event

    // Initialize LED pins as outputs
    for (int i = 0; i < numDirections; i++) {
        pinMode(redPins[i], OUTPUT);
        pinMode(yellowPins[i], OUTPUT);
        pinMode(greenPins[i], OUTPUT);
        
        // Turn on red lights for all directions initially
        digitalWrite(redPins[i], HIGH);
        digitalWrite(yellowPins[i], LOW);
        digitalWrite(greenPins[i], LOW);
    }
}

void receiveData(int byteCount) {
    // Receive green times from the master
    for (int i = 0; i < numDirections; i++) {
        if (Wire.available()) {
            greenTimes[i] = Wire.read();
            Serial.print("Received green time for direction ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(greenTimes[i]);
        }
    }
}

void controlTraffic() {
    // Control traffic lights based on received green times
    for (int i = 0; i < numDirections; i++) {
        // Turn off red lights for all other directions and turn on the current direction's green light
        for (int j = 0; j < numDirections; j++) {
            if (j == i) {
                digitalWrite(redPins[j], LOW);  // Turn off red light
                digitalWrite(greenPins[j], HIGH);  // Turn on green light
                
                // Green light duration based on received value
                delay(greenTimes[j] * 1000);
                
                // Switch from green to yellow
                digitalWrite(greenPins[j], LOW);
                digitalWrite(yellowPins[j], HIGH);
                delay(2000);  // Yellow light duration 2 seconds
                
                // Switch from yellow to red
                digitalWrite(yellowPins[j], LOW);
                digitalWrite(redPins[j], HIGH);
            } else {
                // Keep red light on for all other directions
                digitalWrite(redPins[j], HIGH);
                digitalWrite(yellowPins[j], LOW);
                digitalWrite(greenPins[j], LOW);
            }
        }
    }
}

void loop() {
    controlTraffic();
}
