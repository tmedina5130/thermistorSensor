//PT Systems Thermistor Fault/No Fault Indicator
// firmware version 1.1

//Analog read pins
const int therm1 = 13; //thermistor 1 use pin 13
const int therm2 = 12; //thermistor 2 use pin 12
const int therm3 =27; //thermistor 3 use pin 27
const int therm4 = 33; //thermistor 4 use pin 33
const int therm5 = 15; //thermistor 5 use pin 15

//Digital output pins for LED toggle
const int therm1_greenLed= 32; //thermistor 1 green led
const int therm1_redLed = 14; //thermistor 1 red led
const int therm2_greenLed = 22; //thermistor 2 green led
const int therm2_redLed = 23; //thermistor 2 red led
const int therm3_greenLed = 4; //thermistor 3 green led
const int therm3_redLed = 5; //thermistor 3 red led
const int therm4_greenLed = 18; //thermistor 4 green led
const int therm4_redLed = 19; //thermistor 4 red led
const int therm5_greenLed = 16; //thermistor 5 green led
const int therm5_redLed = 17; //thermistor 5 red led

//Digital input for LED bulb check
const int ledBulbCheckSwitch = 34;

//Analog Voltage Range
const int offset = 200; //200mV offset
const float validAnalogUpperRange = 2060 + offset; //1.780V upper range
const float validAnalogLowerRange = 1330 + offset; //1.124V lower range

int therm1_analogRead = 0; //initialize thermistor 1 analog read
int therm2_analogRead = 0; //initialize thermistor 2 analog read
int therm3_analogRead = 0; //initialize thermistor 3 analog read
int therm4_analogRead = 0; //initialize thermistor 4 analog read
int therm5_analogRead = 0; //initialize thermistor 5 analog read

void setup() {
  Serial.begin(9600); //Initialize baud rate for serial comm debugging purposes
  pinMode(therm1_greenLed, OUTPUT); //Initialize pin 32 as an output
  pinMode(therm1_redLed, OUTPUT); //Initialize pin 14 as an output
  pinMode(therm2_greenLed, OUTPUT); //Initialize pin 22 as an output
  pinMode(therm2_redLed, OUTPUT); //Initialize pin 23 as an output
  pinMode(therm3_greenLed, OUTPUT); //Initialize pin 4 as an output
  pinMode(therm3_redLed, OUTPUT); //Initialize pin 5 as an output
  pinMode(therm4_greenLed, OUTPUT); //Initialize pin 18 as an output
  pinMode(therm4_redLed, OUTPUT); //Initialize pin 19 as an output
  pinMode(therm5_greenLed, OUTPUT); //Initialize pin 16 as an output
  pinMode(therm5_redLed, OUTPUT); //Initialize pin 17 as an output
  pinMode(ledBulbCheckSwitch, INPUT_PULLUP); //Initialize pin 34 as an output, use board internal pullup
}

void loop() {
  bulbCheck();
  readThermistor1(); 
  readThermistor2();
  readThermistor3();
  readThermistor4();
  readThermistor5();
}  

//No Fault Function - GREEN ON, RED OFF
void noFault(int greenLED, int redLED){
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED, HIGH);
}

//Fault Function - GREEN OFF, RED ON
void fault(int greenLED, int redLED){
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
}

//Bulb check intialize LEDs off
void off(int greenLED, int redLED){
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);  
}

//Read thermistor 1 function
void readThermistor1(){
  therm1_analogRead = analogRead(therm1);
  Serial.print("Thermistor ONE: ");
  Serial.println(therm1_analogRead);
  if(therm1_analogRead >= validAnalogLowerRange && therm1_analogRead <= validAnalogUpperRange){
    noFault(therm1_greenLed,therm1_redLed);
  } else{
    fault(therm1_greenLed,therm1_redLed);
  }
}

//Read thermistor 2 function
void readThermistor2(){
  therm2_analogRead = analogRead(therm2);
  Serial.print("Thermistor TWO: ");
  Serial.println(therm2_analogRead);
  if(therm2_analogRead >= validAnalogLowerRange && therm2_analogRead <= validAnalogUpperRange){
    noFault(therm2_greenLed,therm2_redLed);
  } else{
    fault(therm2_greenLed,therm2_redLed);
  }
}

//Read thermistor 3 function
void readThermistor3(){
  therm3_analogRead = analogRead(therm3);
  Serial.print("Thermistor THREE: ");
  Serial.println(therm3_analogRead);
  if(therm3_analogRead >= validAnalogLowerRange && therm3_analogRead <= validAnalogUpperRange){
    noFault(therm3_greenLed,therm3_redLed);
  } else{
    fault(therm3_greenLed,therm3_redLed);
  }
}

//Read thermistor 4 function
void readThermistor4(){
  therm4_analogRead = analogRead(therm4);
  Serial.print("Thermistor FOUR: ");
  Serial.println(therm4_analogRead);
  if(therm4_analogRead >= validAnalogLowerRange && therm4_analogRead <= validAnalogUpperRange){
    noFault(therm4_greenLed,therm4_redLed);
  } else{
    fault(therm4_greenLed,therm4_redLed);
  }
}

//Read thermistor 5 function
void readThermistor5(){
  therm5_analogRead = analogRead(therm5);
  Serial.print("Thermistor FIVE: ");
  Serial.println(therm5_analogRead);
  if(therm5_analogRead >= validAnalogLowerRange && therm5_analogRead <= validAnalogUpperRange){
    noFault(therm5_greenLed,therm5_redLed);
  } else{
    fault(therm5_greenLed,therm5_redLed);
  }
}

//Bulb check function. Needs pull up
void bulbCheck(){
  int ledBulbCheckState = digitalRead(ledBulbCheckSwitch);
  Serial.println(ledBulbCheckState);
  if(ledBulbCheckState == LOW){
    off(therm1_greenLed,  therm1_redLed);
    off(therm2_greenLed,therm2_redLed);
    off(therm3_greenLed,therm3_redLed);
    off(therm4_greenLed,therm4_redLed);
    off(therm5_greenLed,therm5_redLed);
    delay(1500);
    noFault(therm1_greenLed,therm1_redLed); //ON GREEN LED
    noFault(therm2_greenLed,therm2_redLed);
    noFault(therm3_greenLed,therm3_redLed);
    noFault(therm4_greenLed,therm4_redLed);
    noFault(therm5_greenLed,therm5_redLed); 
    delay(3000);
    fault(therm1_greenLed,therm1_redLed); //ON RED LED
    fault(therm2_greenLed,therm2_redLed);
    fault(therm3_greenLed,therm3_redLed);
    fault(therm4_greenLed,therm4_redLed);
    fault(therm5_greenLed,therm5_redLed);
    delay(3000);
    off(therm1_greenLed,therm1_redLed);
    off(therm2_greenLed,therm2_redLed);
    off(therm3_greenLed,therm3_redLed);
    off(therm4_greenLed,therm4_redLed);
    off(therm5_greenLed,therm5_redLed);
    delay(1500);
  }
}
