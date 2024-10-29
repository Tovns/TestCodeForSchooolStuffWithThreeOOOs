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

bool Turning_off = false;
bool Turning_on = false;
int Light_point = -1;

int Buzzer = 11;
bool Light_state = false;

CRGB leds[NUM_LEDS]; 

void setup() {


  pinMode(Buzzer, OUTPUT);
  pinMode(13, OUTPUT);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);      
 
  FastLED.setBrightness(15);         

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


void led_on_off(){
  delay(200);
  if (Turning_on and Turning_off){
    Turning_on = false;
    Turning_off = false;
  }
  else if (Turning_on){
    leds[Light_point + 1] = CRGB::Red;
    if (Light_point < NUM_LEDS - 1){  // you need that -1 or it breaks DONT REMOVE IT
      Light_point++;
    }
    else {
      Turning_on = false;
      Serial.println("sdlfkj");
    }
    FastLED.show();
  }
  else if (Turning_off){
    leds[Light_point] = CRGB::Black;
    if (Light_point > -1){
      Light_point--;
    }
    else {
      Turning_off = false;
      Serial.println("poo poo bum bumn");
    }
    FastLED.show();
  }
}

void loop() {
  int i;
  //see the examples for more complete code
  uint8_t data = 0;

  paj7620ReadReg(0x43, 1, &data); 

  if (data == GES_LEFT_FLAG) {
    Turning_off = true;
    Serial.println("LEFT");
  }
  else if (data == GES_RIGHT_FLAG)
  {
    Turning_on = true;
    Serial.println("RIGHT");
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

  led_on_off();
}