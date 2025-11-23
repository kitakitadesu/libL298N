/**
 * ESP32 - L298N Motor Driver Basic Example
 * 
 * This example demonstrates basic motor control using the L298N motor driver
 * with an ESP32. It shows forward, backward, braking, and coasting.
 * The ESP32 uses LEDC PWM which is automatically configured by the library.
 * 
 * Hardware Connections:
 * ---------------------
 * L298N Pin    | ESP32 Pin
 * -------------|----------------
 * IN1          | GPIO 33
 * IN2          | GPIO 25
 * ENA (Enable) | GPIO 32 (PWM capable)
 * GND          | GND
 * 12V          | External 12V power supply
 * 5V           | 5V (optional, for L298N logic)
 * 
 * Motor Connections:
 * ------------------
 * Connect your DC motor to OUT1 and OUT2 on the L298N module
 * 
 * Power Supply:
 * -------------
 * - Connect external 12V (or motor voltage) to 12V terminal
 * - Connect GND of power supply to L298N GND and ESP32 GND
 * - Remove the 5V jumper on L298N and connect 5V pin to ESP32 5V or VIN
 * 
 * Note:
 * -----
 * ESP32 uses LEDC PWM (channel 0, 5kHz, 8-bit) automatically configured
 * by the library. Any PWM-capable pin can be used for the enable pin.
 */

#include <Arduino.h>
#include <l298n.hpp>

// Pin definitions are configured in platformio.ini
// Default pins for ESP32:
// MOTOR_IN1 = 33
// MOTOR_IN2 = 25
// MOTOR_EN = 32

#ifndef MOTOR_IN1
#define MOTOR_IN1  33
#endif
#ifndef MOTOR_IN2
#define MOTOR_IN2  25
#endif
#ifndef MOTOR_EN
#define MOTOR_EN   32  // Must be PWM-capable pin
#endif

// Create motor object
L298N motor(MOTOR_IN1, MOTOR_IN2, MOTOR_EN);

void setup() {
  Serial.begin(115200);
  delay(1000);  // Wait for serial to initialize
  
  Serial.println("\n\nL298N Motor Driver Test - ESP32");
  Serial.println("=================================");
  
  // Initialize the motor driver
  motor.begin();
  
  Serial.println("Motor initialized with LEDC PWM!");
  Serial.println("PWM: Channel 0, 5kHz, 8-bit resolution");
  delay(1000);
}

void loop() {
  // Move forward at full speed
  Serial.println("Moving forward at full speed...");
  motor.forward(255);
  delay(2000);
  
  // Move forward at half speed
  Serial.println("Moving forward at half speed...");
  motor.forward(128);
  delay(2000);
  
  // Active brake
  Serial.println("Applying brake...");
  motor.brake();
  delay(1000);
  
  // Move backward at full speed
  Serial.println("Moving backward at full speed...");
  motor.backward(255);
  delay(2000);
  
  // Move backward at 75% speed
  Serial.println("Moving backward at 75% speed...");
  motor.backward(192);
  delay(2000);
  
  // Coast to stop
  Serial.println("Coasting to stop...");
  motor.coast();
  delay(1000);
  
  // Demonstrate speed change while running
  Serial.println("Forward with speed ramping...");
  motor.forward(50);
  delay(500);
  
  for (int speed = 50; speed <= 255; speed += 10) {
    motor.setSpeed(speed);
    Serial.printf("Speed: %d, Running: %s\n", speed, motor.isRunning() ? "Yes" : "No");
    delay(200);
  }
  
  // Stop with brake
  Serial.println("Stopping with brake...");
  motor.stop();
  delay(2000);
  
  Serial.println("Cycle complete!\n");
  delay(1000);
}
