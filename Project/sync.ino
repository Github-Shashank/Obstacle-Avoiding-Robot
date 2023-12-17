#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

Servo angle;
const int trigo_pin = A1;
const int echo_pin = A2;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

long dist(int trigo_pin, int echo_pin) {
  digitalWrite(trigo_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigo_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigo_pin, LOW);
  return pulseIn(echo_pin, HIGH) / 29 / 2;
}

void setup() {
  Serial.begin(9600);

  AFMS.begin();  // Motor shield initialization
  
  AFMS.getMotor(1)->setSpeed(255);  // Set speed for DC motors
  AFMS.getMotor(2)->setSpeed(255);
  AFMS.getMotor(3)->setSpeed(255);
  AFMS.getMotor(4)->setSpeed(255);
  
  angle.attach(10); // Attach the servo to pin 10
  pinMode(trigo_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop(){
  angle.write(90);
  Serial.print('Distance is ');
  Serial.println(dist(trigo_pin, echo_pin));
  AFMS.getMotor(1)->run(BACKWARD);  // turn right 
  AFMS.getMotor(2)->run(BACKWARD);
  AFMS.getMotor(3)->run(FORWARD);
  AFMS.getMotor(4)->run(FORWARD);
}