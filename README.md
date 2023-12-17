# Obstacle Avoidance Robot

## Description
This Arduino code implements an object avoidance mechanism using an ultrasonic sensor and a four-wheeled robot with individual motors. When an object is detected within 40 cm, the robot performs a predefined sequence: it scan using sensor and turn it's direction. Motor control is facilitated through the AFMotor library, while the distance calculation relies on the pulse duration from the ultrasonic sensor, and scaning is done by ultrasonic and servo.

## Components Used

- Ultrasonic Sensor
- Servo Motor
- Arduino Uno
- Motor Shield
- Four DC Motors (M1, M2, M3, M4)
