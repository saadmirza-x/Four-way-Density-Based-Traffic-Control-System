4-Way Density-Based Traffic Control System

Team

Saad Mirza — 2023498
Hashim Gull — 2023232
Maham Imran — 2023289

Overview
A 4-way density-based traffic control system built using a Master-Slave Arduino architecture. The system reads real-time density data and controls traffic signals accordingly across four lanes.
Architecture
The Master Arduino is connected to the density sensors and is responsible for reading traffic data and making decisions. The Slave Arduino receives those decisions over I2C and controls the LEDs accordingly. SDA and SCL lines are used for communication between the two, ensuring time synchronization and data synchronization across the system.
Hardware Used

2x Arduino Uno (1 Master, 1 Slave)
Ultrasonic Sensors (connected to Master)
LEDs(connected to Slave)
I2C bus via SDA and SCL lines

How It Works

Master reads density values from all four lane sensors
Master determines which lane gets priority
Master sends the decision to the Slave over I2C
Slave receives the instruction and controls the LEDs for the corresponding lane
Process repeats in real time

Communication Protocol
I2C was used for Master-Slave communication. SDA carries the data and SCL keeps both Arduinos synchronized on timing.
