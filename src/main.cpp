#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// put function declarations here:
// arduino used pins
int testPinHighLow = 8; // for testing
int testPinOutLED = 13; // led
int pinInWaterSensor = A0; 
int pinOutPumpRelai = A1; 

unsigned  int waterLevel = 0; // 0 = water hight, 1 = water low because INPUT_PULLUP activated
unsigned  long timeWaterPumpOn  = 2000; // time ms
unsigned  long timeWaterPumpOff = 5000; // time ms
unsigned  long waitOneSecond    = 1000; // time ms

void setup() // put your setup code here, to run once:
{
  pinMode(testPinHighLow, INPUT_PULLUP);
  pinMode(testPinOutLED, OUTPUT); 
  pinMode(pinInWaterSensor, INPUT_PULLUP);
  pinMode(pinOutPumpRelai, OUTPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void testHighLowPin(int pin) // intern INPUT_PULLUP resistor not work on pins 7 & 8 by my arduino
{
  for(int i=0; i<100; i++)
  {    
    int pinState = digitalRead(pin);
    Serial.println("");Serial.print("Test high & low dtstr from pin: "); Serial.print(pin); Serial.print("=");Serial.println(pinState);  
    if(pinState == 1) digitalWrite(13,HIGH); else digitalWrite(13,LOW);
    delay(1000);
  }
}

void viewDisplayAndLog(String messageOne, int valueOne, String messageTwo, int valueTwo)
{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(messageOne); lcd.print(valueOne);
  lcd.setCursor(0, 1);
  lcd.print(messageTwo); lcd.print(valueTwo);

  Serial.println("");
  Serial.print(messageOne); Serial.println(valueOne); 
  Serial.print(messageTwo); Serial.println(valueTwo);
  Serial.println("");
}

int getkWaterState() {return digitalRead(pinInWaterSensor);}

void activateWaterPumpAndCheckWaterLevel()
{ 
  int counterWaterPumpOn = (int)timeWaterPumpOn/1000;
  int counterWaterPumpOff = (int)timeWaterPumpOff/1000;

  digitalWrite(pinOutPumpRelai, HIGH); digitalWrite(testPinOutLED, HIGH);
  for(int i=counterWaterPumpOn; i>=0; i--) // turn pump off fur 15 seconds
  { 
    viewDisplayAndLog("Pump on for ", i, "Water lvl: ", getkWaterState());
    delay(waitOneSecond);
  }
  digitalWrite(pinOutPumpRelai,LOW); digitalWrite(testPinOutLED, LOW);

  for(int i=counterWaterPumpOff; i>=0; i--) // turn pump on for 3 seconds
  {
    if(getkWaterState() == 0) break; // if water lvl is max, turn pump on before timer expires

    viewDisplayAndLog("Pump off for ", i, "Water lvl: ", getkWaterState());
    delay(waitOneSecond);
  }
}

void loop() // put your main code here, to run repeatedly:
{
  //testHighLowPin(testPinHighLow);
  activateWaterPumpAndCheckWaterLevel();
}