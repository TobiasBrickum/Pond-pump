#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// put function declarations here:
//int pinWaterSensor = A0; // arduino pin
int pinWaterSensor = 7; // arduino pin
int pinPumpRelai = 4; // arduino pin

unsigned  int waterLevel = 0; // 0 = water hight, 1 = water low cause INPUT_PULLUP
unsigned  long pumpRelaiTime = 1000; // time in ms
unsigned  long pumpRelaiDelay = 10; // time in s
unsigned  long oneSecond = 1000; 

void setup() // put your setup code here, to run once:
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(pinWaterSensor, INPUT_PULLUP); 
  //pinMode(pinWaterSensor, INPUT);
  pinMode(pinPumpRelai, OUTPUT);
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

int checkWaterSensor()
{
  waterLevel = digitalRead(pinWaterSensor);
  //waterLevel = analogRead(pinWaterSensor);
}

void turnPumpOn()
{ 
  digitalWrite(pinPumpRelai, HIGH);
  int counter = pumpRelaiTime/1000;// ms in seconds
  while(counter >=0)
  {
    viewDisplayAndLog("Pump on: ", counter, "Water lvl: ", checkWaterSensor());
    delay(oneSecond);
    counter --;
  }
  digitalWrite(pinPumpRelai,LOW);
}

void checkWaterLevel()
{
  for(int i=0; i<pumpRelaiDelay; i++)
  { 
    viewDisplayAndLog("Pump wait: ", pumpRelaiDelay - i, "Water lvl: ", checkWaterSensor());
    if(waterLevel == 0){break;}
    delay(1000);
  }
}

void loop() // put your main code here, to run repeatedly:
{
  turnPumpOn();
  checkWaterLevel();
}