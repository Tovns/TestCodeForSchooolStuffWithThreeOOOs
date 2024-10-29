#include "FastLED.h"                                 

#define LED_DT 7                                     

#define COLOR_ORDER GRB                                       
#define LED_TYPE WS2812                                       
#define NUM_LEDS 13                                 
 
uint8_t max_bright = 255;                         

int led_point = 0;
int POT_PIN = A0;

CRGB leds[NUM_LEDS]; 
 
void setup() {

  Serial.begin(115200);
 
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);      
 
  FastLED.setBrightness(55);         
 
} // setup()
 
 
 
void loop () {
  int potVal = analogRead(POT_PIN);	
  int led_point = map(potVal, 0, 900, -1, 13);
  leds[led_point] = CRGB::Red;
  FastLED.show();
  Serial.println(potVal);
  for (int i = -1 ;i < led_point; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  for (int i = 13;i > led_point; i--)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}