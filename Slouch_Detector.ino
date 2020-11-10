#include <Adafruit_CircuitPlayground.h>

#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees
#define SLOUCH_ANGLE        15.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         3000      // allowable slouch time (secs) 
#define WATER_TIME          90000     // time to drink water


float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
unsigned long waterTimer;
bool water;



void setup() {
  Serial.begin(9600);
  // Initialize Circuit Playground
  CircuitPlayground.begin();
  targetAngle = 0;
}


void loop() {
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);

  // set target angle on button press
  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900, 100);
    delay(100);
    CircuitPlayground.playTone(900, 100);
    delay(100);
  }

  // Check for slouching
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) slouchStartTime = millis();
    slouching = true;
  } else {
    slouching = false;
  }

  // If we are slouching
  if (slouching) {
    // Check how long we've been slouching
    if (millis() - slouchStartTime > SLOUCH_TIME) {
      // Play a tone
      CircuitPlayground.playTone(800, 500);
    }
  }

  //Drink water every 90 min
  if (!water) {
    waterTimer = millis();
    water = true;
  }

  if (water == true) {
    if (millis() - waterTimer > WATER_TIME) { s
      for (int i = 0; i < 10; i ++) {
        CircuitPlayground.setPixelColor(i, 0, 0, 255);
      }
      CircuitPlayground.playTone(800, 500);
      delay(100);
      CircuitPlayground.playTone(800, 500);
      delay(100);
      CircuitPlayground.playTone(800, 500);
      delay(500);

      for (int i = 0; i < 10; i ++) {
        CircuitPlayground.setPixelColor(i, 0, 0, 0);
      }
      water = false;
    }
  }
}
