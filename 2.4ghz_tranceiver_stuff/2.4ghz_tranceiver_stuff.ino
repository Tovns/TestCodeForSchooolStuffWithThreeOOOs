#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

#define N 128 

uint8_t values[N];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
}

void loop() {
  memset(values,0,sizeof(values));       // Clear measurement "values" by setting to "0"                     
    int i = N;
    while (i--) {
        radio.setChannel(i);
        radio.startListening();
        delayMicroseconds(128);           // can set 256, ...  not sure what is better ...        
        radio.stopListening(); 
        if(radio.testCarrier()){
          ++i;
          Serial.println(i); 
        }
  }
}