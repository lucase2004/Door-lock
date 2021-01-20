#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; //radio address
Servo servo; // names servo
const int servoPin = 3; //sets servo pin to a const int (won't change)
const int ledPin = 2; //sets LED pin


void setup() {
  Serial.begin(9600);
  radio.begin();
  pinMode (ledPin, OUTPUT); //sets LED pin to output
  radio.openReadingPipe(0, address); //turns on ability to receive signals
  radio.setPALevel(RF24_PA_MIN); //?
  radio.startListening(); //turns on listening for signals function 
  servo.attach(servoPin); //sets up servo to pin 3
}
void loop() {
  if (radio.available()) {
    boolean state; //?
    radio.read(&state, sizeof(state)); 
    /* & returns the address (physical location) of a variable. Here, &state returns the location of state.     
       * sizeof is an operator (+, -, *, /, %, OR, AND, XOR, etc) that returns the size in bytes of something */
    Serial.println(state);
    
    if (state == 1) {
      digitalWrite (ledPin, HIGH); //turn on LED 
      Serial.println("Working");
      servo.write(180);
      delay (1000);
      digitalWrite(ledPin, LOW); //turn off LED after 1 sec
    }
    else{
      servo.write(20);
      Serial.println("not working"); //r u sure its not working on this else?? cuz im not
      
      digitalWrite(ledPin, HIGH); 
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
  }
}
