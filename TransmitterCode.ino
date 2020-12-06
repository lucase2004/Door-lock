
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
bool power;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  int val = digitalRead(2);
  if (val == HIGH){
    if (power) {
      power = false;
      Serial.println("Off");
      boolean state = 0;
      radio.write(&state, sizeof(state));
      delay(1000);
      }
  else {
    //add LED command here to lightup for one second
    power = true; 
    Serial.println("On");
    boolean state = 1;
    radio.write(&state, sizeof(state));
    delay(1000);
  }
  }
}
