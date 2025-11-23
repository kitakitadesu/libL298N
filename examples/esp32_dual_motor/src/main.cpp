/**
 * ESP32 - L298N Dual Motor Driver Example
 * 
 * This example demonstrates controlling two DC motors (front and rear) using
 * two L298N motor driver modules with an ESP32. Perfect for robot cars or
 * differential drive systems.
 * 
 * Hardware Connections:
 * ---------------------
 * 
 * Driver 1 (Front Motor Controller):
 * L298N Pin    | ESP32 Pin
 * -------------|----------------
 * ENA          | GPIO 32
 * IN1          | GPIO 33
 * IN2          | GPIO 25
 * IN3          | GPIO 26
 * IN4          | GPIO 27
 * ENB          | GPIO 14
 * GND          | GND
 * 12V          | External 12V Power Supply
 * 
 * Driver 2 (Rear Motor Controller):
 * L298N Pin    | ESP32 Pin
 * -------------|----------------
 * ENA          | GPIO 13
 * IN1          | GPIO 16
 * IN2          | GPIO 17
 * IN3          | GPIO 18
 * IN4          | GPIO 19
 * ENB          | GPIO 23
 * GND          | GND
 * 12V          | External 12V Power Supply
 * 
 * Motors:
 * -------
 * Front Left Motor  -> Driver 1: OUT1 and OUT2
 * Front Right Motor -> Driver 1: OUT3 and OUT4
 * Rear Left Motor   -> Driver 2: OUT1 and OUT2
 * Rear Right Motor  -> Driver 2: OUT3 and OUT4
 * 
 * Power Supply:
 * -------------
 * - Connect external 12V (or motor voltage) to both L298N 12V terminals
 * - Connect all GNDs together (ESP32, both L298N, power supply)
 * - Remove 5V jumpers on L298N modules
 * 
 * Note:
 * -----
 * Pin definitions are configured in platformio.ini for easy customization.
 * This example creates 4 independent motor objects for full control.
 */

#include <Arduino.h>
#include <l298n.hpp>

// Pin definitions are configured in platformio.ini
// Fallback to default pins if not defined

// Front Motor Controller (Driver 1)
#ifndef ENA_FRONT
#define ENA_FRONT 32
#endif
#ifndef IN1_FRONT
#define IN1_FRONT 33
#endif
#ifndef IN2_FRONT
#define IN2_FRONT 25
#endif
#ifndef IN3_FRONT
#define IN3_FRONT 26
#endif
#ifndef IN4_FRONT
#define IN4_FRONT 27
#endif
#ifndef ENB_FRONT
#define ENB_FRONT 14
#endif

// Rear Motor Controller (Driver 2)
#ifndef ENA_REAR
#define ENA_REAR 13
#endif
#ifndef IN1_REAR
#define IN1_REAR 16
#endif
#ifndef IN2_REAR
#define IN2_REAR 17
#endif
#ifndef IN3_REAR
#define IN3_REAR 18
#endif
#ifndef IN4_REAR
#define IN4_REAR 19
#endif
#ifndef ENB_REAR
#define ENB_REAR 23
#endif

// Create motor objects
// Driver 1: Front motors
L298N motorFrontLeft(IN1_FRONT, IN2_FRONT, ENA_FRONT);
L298N motorFrontRight(IN3_FRONT, IN4_FRONT, ENB_FRONT);

// Driver 2: Rear motors
L298N motorRearLeft(IN1_REAR, IN2_REAR, ENA_REAR);
L298N motorRearRight(IN3_REAR, IN4_REAR, ENB_REAR);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nL298N Dual Motor Driver Test - ESP32");
  Serial.println("======================================");
  
  // Initialize all motors
  motorFrontLeft.begin();
  motorFrontRight.begin();
  motorRearLeft.begin();
  motorRearRight.begin();
  
  Serial.println("All motors initialized!");
  Serial.println("Front Left, Front Right, Rear Left, Rear Right ready");
  delay(2000);
}

void moveForward(uint8_t speed = 255) {
  Serial.printf("Moving forward at speed %d\n", speed);
  motorFrontLeft.forward(speed);
  motorFrontRight.forward(speed);
  motorRearLeft.forward(speed);
  motorRearRight.forward(speed);
}

void moveBackward(uint8_t speed = 255) {
  Serial.printf("Moving backward at speed %d\n", speed);
  motorFrontLeft.backward(speed);
  motorFrontRight.backward(speed);
  motorRearLeft.backward(speed);
  motorRearRight.backward(speed);
}

void turnLeft(uint8_t speed = 200) {
  Serial.printf("Turning left at speed %d\n", speed);
  // Left side backward, right side forward
  motorFrontLeft.backward(speed);
  motorFrontRight.forward(speed);
  motorRearLeft.backward(speed);
  motorRearRight.forward(speed);
}

void turnRight(uint8_t speed = 200) {
  Serial.printf("Turning right at speed %d\n", speed);
  // Left side forward, right side backward
  motorFrontLeft.forward(speed);
  motorFrontRight.backward(speed);
  motorRearLeft.forward(speed);
  motorRearRight.backward(speed);
}

void stopAllMotors() {
  Serial.println("Stopping all motors (brake)");
  motorFrontLeft.brake();
  motorFrontRight.brake();
  motorRearLeft.brake();
  motorRearRight.brake();
}

void coastAllMotors() {
  Serial.println("Coasting all motors");
  motorFrontLeft.coast();
  motorFrontRight.coast();
  motorRearLeft.coast();
  motorRearRight.coast();
}

void loop() {
  // Test sequence for robot movement
  
  // Move forward at full speed
  moveForward(255);
  delay(2000);
  
  // Brake
  stopAllMotors();
  delay(1000);
  
  // Move backward
  moveBackward(200);
  delay(2000);
  
  // Brake
  stopAllMotors();
  delay(1000);
  
  // Turn left
  turnLeft(200);
  delay(1500);
  
  // Brake
  stopAllMotors();
  delay(1000);
  
  // Turn right
  turnRight(200);
  delay(1500);
  
  // Coast to stop
  coastAllMotors();
  delay(2000);
  
  // Speed ramping demo - forward
  Serial.println("Speed ramping demo...");
  for (int speed = 100; speed <= 255; speed += 20) {
    moveForward(speed);
    delay(500);
  }
  
  // Brake
  stopAllMotors();
  delay(2000);
  
  Serial.println("Cycle complete!\n");
  delay(2000);
}
