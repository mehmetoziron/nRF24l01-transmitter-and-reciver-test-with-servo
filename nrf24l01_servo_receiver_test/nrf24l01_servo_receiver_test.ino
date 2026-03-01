#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo myServo;
int angle = 90;
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "nrF01";
void setup() {
  Serial.begin(9600);
  myServo.attach(3);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    char text[32] = "";//print only 32 characters
    int xL, yL, xR, yR;
    radio.read(&text, sizeof(text));
    sscanf(text, "L-X:%d Y:%d R-X:%d Y:%d", &xL, &yL, &xR, &yR);

    // Artık değişkenlerde rakamlar var
    Serial.print("xL = "); Serial.print(xL);
    Serial.print(" yL = "); Serial.print(yL);
    Serial.print(" xR = "); Serial.print(xR);
    Serial.print(" yR = "); Serial.println(yR);
    angle = 9*(-(xR-10));
    myServo.write(angle);
    //Serial.println(text);
  }
}
