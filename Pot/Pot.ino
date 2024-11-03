int potPin = A0;        // Input pin from the potentiometer      // Output pin to the LED
int potVal = 0;          // A variable to store the potentiometer value

void setup()          // Runs once when sketch start
{     
  Serial.begin(9600);
}

void loop()          // Runs repeatedly
{
  //read from the pot pin, and store it into potval
  potVal = analogRead(potPin);

  //"map" the brightness, so that potval (0->1023)
  // corresponds with a value between (0->255)

 Serial.println(potVal);
}