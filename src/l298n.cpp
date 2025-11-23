#include "l298n.hpp"

// Constructor with enable pin
L298N::L298N(uint8_t in1, uint8_t in2, uint8_t en)
    : _in1(in1), _in2(in2), _en(en), _hasEnablePin(true), _speed(255), _running(false) {
}

// Constructor without enable pin
L298N::L298N(uint8_t in1, uint8_t in2)
    : _in1(in1), _in2(in2), _en(0), _hasEnablePin(false), _speed(255), _running(false) {
}

void L298N::begin() {
    // Set pin modes
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    
    if (_hasEnablePin) {
        pinMode(_en, OUTPUT);
        
        // Configure PWM for ESP32
        #ifdef ESP32
            // Use LEDC PWM on ESP32
            // We'll use channel 0 with 5kHz frequency and 8-bit resolution
            ledcSetup(0, 5000, 8);  // channel 0, 5kHz, 8-bit resolution
            ledcAttachPin(_en, 0);   // attach enable pin to channel 0
        #endif
    }
    
    // Initialize motor to stopped state
    stop();
}

void L298N::forward(uint8_t speed) {
    _speed = speed;
    _running = true;
    
    // Set direction: IN1 HIGH, IN2 LOW
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    
    // Set speed
    _updateSpeed();
}

void L298N::backward(uint8_t speed) {
    _speed = speed;
    _running = true;
    
    // Set direction: IN1 LOW, IN2 HIGH
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    
    // Set speed
    _updateSpeed();
}

void L298N::brake() {
    _running = false;
    _speed = 0;
    
    // Active braking: both inputs HIGH
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, HIGH);
    
    // Disable PWM or set to 0
    _updateSpeed();
}

void L298N::coast() {
    _running = false;
    _speed = 0;
    
    // Coast: both inputs LOW
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    
    // Disable PWM or set to 0
    _updateSpeed();
}

void L298N::stop() {
    // Default stop uses active braking
    brake();
}

void L298N::setSpeed(uint8_t speed) {
    _speed = speed;
    
    // Only update if motor is running
    if (_running) {
        _updateSpeed();
    }
}

uint8_t L298N::getSpeed() const {
    return _speed;
}

bool L298N::isRunning() const {
    return _running;
}

void L298N::_updateSpeed() {
    if (_hasEnablePin) {
        #ifdef ESP32
            // Use LEDC PWM for ESP32
            ledcWrite(0, _speed);
        #else
            // Use standard analogWrite for Arduino
            analogWrite(_en, _speed);
        #endif
    }
    // If no enable pin, motor runs at full speed (hardware enable connected to Vcc)
}
