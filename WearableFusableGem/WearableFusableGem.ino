#include <Adafruit_CircuitPlayground.h>

int presets[4][2][4] = {
  {{255,192,203},{139,0,139}},
  
  {{0,0,255},{255,255,0}},
  
  {{255,0,0},{128,128,128}},
  
  {{255,0,0},{0,255,0}}
};

int preset = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:

  float acc = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
  if (acc > 30) {
    preset = rand() % 4;
  }

  
  for (int i=0; i<10; i++) {
    CircuitPlayground.setPixelColor(
      i,presets[preset][i%2][0],presets[preset][i%2][1],presets[preset][i%2][2]);
  }
  
  delay(10);
}
