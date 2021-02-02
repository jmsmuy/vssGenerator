/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

int counter = 0;
int newPulsePercentage = 512;
int newPulseSpeed = 256;
int delayOn = 1;
int delayOff = 1;

void recalculateDelays() {
  // Here we calculate in microseconds the delays
  long totalDelay = (((float)(newPulseSpeed) * (float)14250) / 1024) + (float)750;
  int delayPercentageOn = ((float)(newPulsePercentage) * (float)100) / (float)1023;
  delayOn = (totalDelay * delayPercentageOn) / 100;
  delayOff = (totalDelay * (100 - delayPercentageOn)) / 100;
}

void loop() {
  if (counter > 300) {
    newPulsePercentage = analogRead(3);
    counter = 0;
  } else if (counter > 150) {
    newPulseSpeed = analogRead(2);
  }
  digitalWrite(1, HIGH);
  delayMicroseconds(delayOn);
  digitalWrite(1, LOW);
  delayMicroseconds(delayOff);

  if (counter == 0) {
    recalculateDelays();
  }
  counter++;
}
