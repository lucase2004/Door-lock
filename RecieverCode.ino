#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Servo servo;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo.attach(3);
}
void loop() {
  if (radio.available()) {
    boolean state;
    radio.read(&state, sizeof(state));
    Serial.println(state);
    if (state == 1) {
      //add LED command here (to make lightup for 1 second)
      Serial.println("Working");
      servo.write(180);
    }
  else {
    servo.write(20);
    Serial.println("not working");
  }
  }
}
