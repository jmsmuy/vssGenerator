/**
   This is a VSS emulator for some BMW DMEs that need it to allow to rev to the rev limiter and also enables a low idle
   850hz freq
   5v on, 0v off, 200mv mean, duty cycle = 2%
*/

#define PIN_VSS 1
#define PIN_TPS 1
#define PIN_TPS_THRESH 3

#define DUTY_CYCLE 2
#define PW_FREQ 850

#define TPS_CHECK_CYCLE_COUNT 1000

float const totalDelay = (1000000 / 850);
float const delayOn = (totalDelay * DUTY_CYCLE) / 100;
float const delayOff = totalDelay - delayOn;
int counterForTPSCheck = 0;
boolean enableVss = false;

void setup() {6

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN_VSS, OUTPUT);

  digitalWrite(PIN_VSS, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PIN_VSS, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(PIN_VSS, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PIN_VSS, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

int readTPS() {
  return analogRead(PIN_TPS);
}

int readTPSThresh() {
  return analogRead(PIN_TPS_THRESH);
}

boolean shouldEnableVssOutput() {
  int tpsValue = readTPS();
  int tpsThresh = readTPSThresh();
  return tpsValue > tpsThresh;
}

void loop() {
  if (enableVss) {
    digitalWrite(PIN_VSS, HIGH);
    delayMicroseconds(delayOn);
    digitalWrite(PIN_VSS, LOW);
    delayMicroseconds(delayOff);
  }
  counterForTPSCheck++;
  if (counterForTPSCheck > TPS_CHECK_CYCLE_COUNT) {
    counterForTPSCheck = 0;
    enableVss = shouldEnableVssOutput();
  }
}
