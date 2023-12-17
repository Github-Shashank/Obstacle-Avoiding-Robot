#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

Servo angle;
const int trigo_pin = A1;
const int echo_pin = A2;

int o = 0;
float angSpd = 5;   // time taken to complete one round update from Sync.ino

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

long dist(int trigo_pin, int echo_pin) {
  digitalWrite(trigo_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigo_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigo_pin, LOW);
  return pulseIn(echo_pin, HIGH) / 29 / 2;
}

void obstacle(int trigo_pin, int echo_pin) {
  AFMS.getMotor(1)->run(BACKWARD);  // Break
  AFMS.getMotor(2)->run(BACKWARD);
  AFMS.getMotor(3)->run(BACKWARD);
  AFMS.getMotor(4)->run(BACKWARD);

  delay(2);
  AFMS.getMotor(1)->run(RELEASE);  // Stop moving
  AFMS.getMotor(2)->run(RELEASE);
  AFMS.getMotor(3)->run(RELEASE);
  AFMS.getMotor(4)->run(RELEASE);

  if (dist(trigo_pin, echo_pin) < 40) {  // Check distance is less than 100 cm
    angle.write(0);
    do {
      o += 1;
      angle.write(o);  // angle of servo
      delay(15);
      if (o == 180 ){
        AFMS.getMotor(1)->run(BACKWARD);  // turn right 
        AFMS.getMotor(2)->run(BACKWARD);
        AFMS.getMotor(3)->run(FORWARD);
        AFMS.getMotor(4)->run(FORWARD);
        delay(angSpd*180/360);   // Trun 180 deg
        break;
      }
    } while (dist(trigo_pin, echo_pin) > 50);  // Stops the servo and turn
    angle.write(90);

    if ( o < 90){
      AFMS.getMotor(1)->run(BACKWARD);  // turn right 
      AFMS.getMotor(2)->run(BACKWARD);
      AFMS.getMotor(3)->run(FORWARD);
      AFMS.getMotor(4)->run(FORWARD);
    }
    else {
      AFMS.getMotor(1)->run(FORWARD);  // turn left
      AFMS.getMotor(2)->run(FORWARD);
      AFMS.getMotor(3)->run(BACKWARD);
      AFMS.getMotor(4)->run(BACKWARD);
    }
    delay(angSpd*o/360);
  }
  AFMS.getMotor(1)->run(RELEASE);  // Stop turning
  AFMS.getMotor(2)->run(RELEASE);
  AFMS.getMotor(3)->run(RELEASE);
  AFMS.getMotor(4)->run(RELEASE);
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

void loop() {

  angle.write(90);// looking forward at 90 degree
  
  AFMS.getMotor(1)->run(FORWARD); // Forward
  AFMS.getMotor(2)->run(FORWARD);
  AFMS.getMotor(3)->run(FORWARD);
  AFMS.getMotor(4)->run(FORWARD);

  delay(2);
  obstacle(trigo_pin, echo_pin);  // Check obstacle at 100 cm ( line 22 )

  delay(100);
}
