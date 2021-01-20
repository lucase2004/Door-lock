
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001"; //sets address to a constant byte
const int ledPin = 4; //const won't change
const int buttonPin = 2;

int buttonState = 0;  //variable for reading the pushbutton status
bool power; //?

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); //set buttonpin as input
  pinMode(ledPin, OUTPUT); //set LED pin to output
  radio.begin(); //begins NRF 
  radio.openWritingPipe(address); //opens ability to send data
  radio.setPALevel(RF24_PA_MIN); //?
  radio.stopListening(); //transmitter doesnt need to listen (needs to be changed for new communciation method)
}
void loop() {
  buttonState = digitalRead(buttonPin); //reads button value 
  if (buttonState == HIGH){ // check if button is pressed
    if (power) { //?
      power = false; //??
      Serial.println("Unlocked");
      digitalWrite(ledPin, HIGH); //turn LED on
      boolean state = 0;
      radio.write(&state, sizeof(state));
      /* & returns the address (physical location) of a variable. Here, &state returns the location of state.     
       * sizeof is an operator (+, -, *, /, %, OR, AND, XOR, etc) that returns the size in bytes of something */
      delay(1000);
      digitalWrite(ledPin, LOW); // turn off LED after 1 sec
    }
    else {
      digitalWrite(ledPin, HIGH); //turn LED on
      power = true;
      Serial.println("Locked");
      boolean state = 1;
      radio.write(&state, sizeof(state)); //sends signal to receiver to control servo
      delay(1000);
      digitalWrite(ledPin, LOW); //turn off LED after 1 sec
      //Im pushing a comment to github bcuz Dylan is testing me
    }
  }
}
