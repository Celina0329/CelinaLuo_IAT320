#include <Adafruit_CircuitPlayground.h>
int vals[7] = {3, 2, 0, 1, 6, 9, 10};
float c = 261.626;
float d = 293.665;
float e = 329.628;
float f = 349.228;
float g = 391.995;
float a = 440.0;
float b = 493.883;
float highc = 523.251;
float no = 0.0;
float twinkle[15] = {c, c, g, g, a, a, g, no, f, f, e, e, d, d, c};
float mary [15] = {e, d, c, d, e, e, e, no, e, d, d, e, d, no, c};
float macdonal [13] = {g, g, g, d, e, e, d, no, b, b, a, a, g};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  for (int i = 0; i < 7; i++) {
    int c = CircuitPlayground.readCap(vals[i]);
    if (c > 500) {
      if (vals[i] == 2) {
        for (int i = 0; i < 15; i ++) {
          CircuitPlayground.playTone(twinkle[i] , 180);
        }
      }
      if (vals [i] == 0) {
        for ( int i = 0; i < 15; i ++) {
          CircuitPlayground.playTone(mary[i], 180);
        }
      }
      if (vals [i] == 1) {
        for (int i = 0; i < 13; i ++) {
          CircuitPlayground.playTone(macdonal[i], 180);
        }
      }
    }
  }
  delay(100);
}
