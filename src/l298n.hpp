#ifndef L298N_H
#define L298N_H

#include <Arduino.h>

/**
 * @brief L298N Motor Driver Library
 * 
 * This library provides an interface to control DC motors using the L298N motor driver.
 * Supports forward, backward, brake, and coast operations with PWM speed control.
 * Compatible with Arduino Uno, ESP32, and other Arduino-compatible boards.
 */
class L298N {
public:
    /**
     * @brief Construct a new L298N motor driver object for a single motor
     * 
     * @param in1 Input 1 pin (direction control)
     * @param in2 Input 2 pin (direction control)
     * @param en Enable pin (PWM speed control)
     */
    L298N(uint8_t in1, uint8_t in2, uint8_t en);

    /**
     * @brief Construct a new L298N motor driver object without enable pin
     * 
     * @param in1 Input 1 pin (direction control)
     * @param in2 Input 2 pin (direction control)
     * 
     * @note When constructed without enable pin, the motor runs at full speed
     *       when moving forward or backward.
     */
    L298N(uint8_t in1, uint8_t in2);

    /**
     * @brief Initialize the motor driver pins
     * 
     * Sets up the pin modes and initializes the motor to a stopped state.
     */
    void begin();

    /**
     * @brief Move the motor forward at specified speed
     * 
     * @param speed Speed value (0-255), where 255 is maximum speed
     */
    void forward(uint8_t speed = 255);

    /**
     * @brief Move the motor backward at specified speed
     * 
     * @param speed Speed value (0-255), where 255 is maximum speed
     */
    void backward(uint8_t speed = 255);

    /**
     * @brief Stop the motor with active braking
     * 
     * Active braking shorts both motor terminals, providing quick stopping.
     * This method applies maximum resistance to motor rotation.
     */
    void brake();

    /**
     * @brief Stop the motor by coasting
     * 
     * Coast mode disconnects power and lets the motor spin freely to a stop.
     * This is a gradual stop with no active braking force.
     */
    void coast();

    /**
     * @brief Stop the motor (alias for brake)
     * 
     * Provides a simple stop() method that performs active braking.
     */
    void stop();

    /**
     * @brief Set the motor speed
     * 
     * @param speed Speed value (0-255), where 0 stops the motor and 255 is maximum
     * 
     * @note This changes speed without changing direction. If motor is not moving,
     *       this will have no effect until forward() or backward() is called.
     */
    void setSpeed(uint8_t speed);

    /**
     * @brief Get the current motor speed setting
     * 
     * @return uint8_t Current speed (0-255)
     */
    uint8_t getSpeed() const;

    /**
     * @brief Check if motor is currently moving
     * 
     * @return true if motor is running in any direction
     * @return false if motor is stopped
     */
    bool isRunning() const;

private:
    uint8_t _in1;           // Input 1 pin
    uint8_t _in2;           // Input 2 pin
    uint8_t _en;            // Enable pin (PWM)
    bool _hasEnablePin;     // Flag to indicate if enable pin is used
    uint8_t _speed;         // Current speed setting
    bool _running;          // Motor running state

    /**
     * @brief Update the motor speed on the enable pin
     */
    void _updateSpeed();
};

#endif // L298N_H
