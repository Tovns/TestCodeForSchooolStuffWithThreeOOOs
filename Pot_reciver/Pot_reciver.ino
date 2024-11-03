#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "FastLED.h"  

#define LED_DT 4
#define COLOR_ORDER GRB                                       
#define LED_TYPE WS2812                                       
#define NUM_LEDS 13   

uint8_t max_bright = 255;
int led_point = 0;
int potVal = 0;

RF24 radio(7, 8); // CE, CSN
CRGB leds[NUM_LEDS]; 

const byte address[6] = "10100";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(55);  
}

void loop() {
  if (radio.available()) {
    radio.read(&potVal, sizeof(potVal));
    int led_point = map(potVal, 0, 1000, -1, 12);
    leds[led_point] = CRGB::Red;
    FastLED.show();
    for (int i = -1 ;i < led_point; i++)
    {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for (int i = 13;i > led_point; i--)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    Serial.println(led_point);
  }
}