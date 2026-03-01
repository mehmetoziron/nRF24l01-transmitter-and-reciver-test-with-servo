#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "nrF01";

int xRPin = A0;  
int yRPin = A1;
int xLPin = A2;  
int yLPin = A3;

const int DEADZONE = 20;   
const int STEPS = 10;       
const int CENTER = 512;    // joystick merkez değeri
char text[30];
int toStep(int val) {
  int offset = val - CENTER;

  if (abs(offset) < DEADZONE) return 0;

  int stepSize = (512 - DEADZONE) / STEPS;
  int step = offset / stepSize;

  if (step > STEPS) step = STEPS;
  if (step < -STEPS) step = -STEPS;

  return step;
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop() {
  // yönleri senin test kodundaki gibi korudum
  int xLVal = toStep(1023 -analogRead(xLPin));
  int yLVal = toStep( analogRead(yLPin));
  int xRVal = toStep(analogRead(xRPin));
  int yRVal = toStep(1023 - analogRead(yRPin));

  sprintf(text, "L-X:%2d Y:%2d R-X:%2d Y:%2d", xLVal, yLVal, xRVal, yRVal);
Serial.println(text);
  // RF24 ile gönder
  radio.write(&text, sizeof(text));
  delay(200);
}
