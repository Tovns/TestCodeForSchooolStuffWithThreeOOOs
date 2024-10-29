#include<Wire.h>
#include<paj7620.h>
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  uint8_t error = paj7620Init();
  if (error) {
    Serial.print("sensor error 0x");
    Serial.println(error, HEX);
    for (;;);
  }
  Serial.println("Go");
}
void loop() {
  //see the examples for more complete code
  uint8_t data = 0;
  paj7620ReadReg(0x43, 1, &data); 
  // Read Bank_0_Reg_0x43/0x44 for gesture result
  if (data == GES_LEFT_FLAG) {
    digitalWrite(13, LOW);
    Serial.println("LEFT");
  }
  else if (data == GES_RIGHT_FLAG)
  {
    digitalWrite(13, HIGH);
    Serial.println("RIGHT");
  }
  else if (data == GES_CLOCKWISE_FLAG)
  {
    Serial.println("CLOCKWISE");
  }
  else if (data == GES_FORWARD_FLAG)
  {
    Serial.println("FOWARD");
  }
  else if (data == GES_BACKWARD_FLAG)
  {
    Serial.println("BACKWARD");
  }
  else if (data == GES_UP_FLAG)
  {
    Serial.println("UP");
  }
   else if (data == GES_DOWN_FLAG)
  {
    Serial.println("DOWN");
  }
   else if (data == GES_WAVE_FLAG)
  {
    Serial.println("WAVE");
  }
   else if (data == GES_COUNT_CLOCKWISE_FLAG)
  {
    Serial.println("COUNCLOCKWISE");
  }
} 