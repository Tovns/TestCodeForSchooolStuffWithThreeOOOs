#include<Wire.h>
#include<paj7620.h>
#include "FastLED.h" 

#define LED_DT 7                                     

#define COLOR_ORDER GRB                                       
#define LED_TYPE WS2812                                       
#define NUM_LEDS 13  

uint8_t max_bright = 255;                         

int led_point = 0;
int POT_PIN = A0;

int Buzzer = 11;
bool Light_state = false;

CRGB leds[NUM_LEDS]; 

void setup() {


  pinMode(Buzzer, OUTPUT);
  pinMode(13, OUTPUT);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);      
 
  FastLED.setBrightness(50);         

  Serial.begin(9600);
  uint8_t error = paj7620Init();
  if (error) {
    Serial.print("sensor error 0x");
    Serial.println(error, HEX);
    for (;;);
  }
  Serial.println("Go");
  FastLED.show();
}

void empty_space_fill() {
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

void fill_lights() {
  if (Light_state == true){
    for (int i = -1; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(150);
    }
  }
  if (Light_state == false){
    for (int i = NUM_LEDS + 1; i > -1; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(150);
    }
  }
}

void loop() {

  int i;
  //see the examples for more complete code
  uint8_t data = 0;

  paj7620ReadReg(0x43, 1, &data); 

  if (data == GES_LEFT_FLAG) {
    Light_state = false;
    digitalWrite(13, LOW);
    Serial.println("LEFT");
    fill_lights();
  }
  else if (data == GES_RIGHT_FLAG)
  {
    Light_state = true;
    digitalWrite(13, HIGH);
    Serial.println("RIGHT");
    fill_lights();
  }
  else if (data)
  {
    for (i = 0 ; i < 3 ; i++)
    {
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW); 
    delay(100);
    }
  }
  // Read Bank_0_Reg_0x43/0x44 for gesture result
}