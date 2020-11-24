#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees
#define SLOUCH_ANGLE        15.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         3000      // allowable slouch time (secs) 
#define LED_PIN             6       // pin NeoPixel is connected to
#define VIBRATE_PIN         1         // pin vibrator is connected to

#define REST_TIME           1200000
#define STRETCH_TIME        5400000

#define LED_COUNT 1

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;

unsigned long stretchTimer;
bool stretch;

unsigned long restTimer;
bool rest;

int Countdown;



void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

  targetAngle = 0;

  pinMode(VIBRATE_PIN, OUTPUT);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
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
      digitalWrite(VIBRATE_PIN, HIGH);
      Serial.println("hi");
    }
  }
  else {
    digitalWrite(VIBRATE_PIN, LOW);
  }

  // Rest every 20 mininte for 20 sec
  if (!rest) {
    restTimer = millis();
    rest = true;
  }

  if (rest == true) {
    if (millis() - restTimer > REST_TIME) {

      for (int i = 0; i < 3; i ++) {
        digitalWrite(VIBRATE_PIN, HIGH);
        colorWipe(strip.Color(  0, 255,   0), 100); // Green
        delay(200);
        digitalWrite(VIBRATE_PIN, LOW);
        colorWipe(strip.Color(  0,   0, 0), 100); // BLACK
        delay(100);
      }
      rest = false;
    }
  }

  //take a break every 90 min
  if (!stretch) {
    stretchTimer = millis();
    stretch = true;
  }

  if (stretch == true) {
    if (millis() - stretchTimer > STRETCH_TIME) {
      for (int i = 0; i < 5; i ++) {
        digitalWrite(VIBRATE_PIN, HIGH);
        colorWipe(strip.Color(  255, 255,   255), 100); // White
        CircuitPlayground.playTone(i * 200, 300);
        delay(300);
        digitalWrite(VIBRATE_PIN, LOW);
        colorWipe(strip.Color(  0,   0, 0), 100); // BLACK
        delay(100);
      }
      stretch = false;
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
