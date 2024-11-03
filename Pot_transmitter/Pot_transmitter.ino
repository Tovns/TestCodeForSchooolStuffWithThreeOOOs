#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "10100";

int potPin = A0;        // Input pin from the potentiometer      // Output pin to the LED
int potVal = 0;          // A variable to store the potentiometer value

void setup()          // Runs once when sketch start
{     
  Serial.begin(9600);
  radio.begin();             
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()          // Runs repeatedly
{
  //read from the pot pin, and store it into potval
  potVal = analogRead(potPin);
  radio.write(&potVal, sizeof(potVal));
  Serial.println(map(potVal, 0, 1000, -1, 12));
  delay(500);
}