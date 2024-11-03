#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
#define BUTTON_PIN 4

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int Button_state = digitalRead(BUTTON_PIN);
  const char text[] = "Hello World";
  if (Button_state == 0) {
    radio.write(&text, sizeof(text));
    Serial.println("button");
  } 
  delay(1000);
}