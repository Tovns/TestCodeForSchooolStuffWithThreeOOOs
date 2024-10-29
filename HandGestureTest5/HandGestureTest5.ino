#include<Wire.h>
#include<paj7620.h>

int MOTOR_PIN = 9;
int Buzzer = 11;
bool Light_state = false;

void setup() {

  pinMode(Buzzer, OUTPUT);
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
  int i;
  //see the examples for more complete code
  uint8_t data = 0;
  paj7620ReadReg(0x43, 1, &data); 
  // Read Bank_0_Reg_0x43/0x44 for gesture result
  if (data == GES_LEFT_FLAG) {
    Light_state = false;
    analogWrite(MOTOR_PIN, 0);
    digitalWrite(13, LOW);
    Serial.println("LEFT");
  }
  else if (data == GES_RIGHT_FLAG)
  {
    Light_state = true;
    analogWrite(MOTOR_PIN, 100);
    digitalWrite(13, HIGH);
    Serial.println("RIGHT");
  }
  else if (data)
  {
    for (i = 0 ; i < 3 ; i++)
    {
    digitalWrite(13, HIGH);
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW); 
    digitalWrite(13, LOW);
    delay(100);
    }
    if (Light_state == true)
    {
      digitalWrite(13, HIGH);
    }
  }
}