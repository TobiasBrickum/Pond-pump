#include <Arduino.h>

// put function declarations here:
int pinWaterSensor = A0;
//int pinWaterSensor = 7;
int pinPumpRelai = 4;

unsigned  int waterLevel = 0;
unsigned  long pumpRelaiTime = 1000;
unsigned  long pumpRelaiDelay = 1500;

void setup() // put your setup code here, to run once:
{
  Serial.begin(9600);

  pinMode(pinWaterSensor, INPUT);
  pinMode(pinPumpRelai, OUTPUT);
}

void turnPumpOn()
{
  Serial.println("");
  Serial.println("Pump water for "); Serial.println(pumpRelaiTime); Serial.println(" seconds.");
  Serial.println("");
  digitalWrite(pinPumpRelai, HIGH); // activate pump 2 seconds
  delay(pumpRelaiTime);
  digitalWrite(pinPumpRelai,LOW); // deactivate pump 
}

void checkWaterLevel()
{
  int counter = 10;
  for(int i=0; i<counter; i++)
  { 
    Serial.print(counter - i);
    Serial.println(" s");
    waterLevel = analogRead(pinWaterSensor);
    //waterLevel = digitalRead(pinWaterSensor);
    Serial.print("Water lvl: ");
    Serial.println(waterLevel);

    //if(waterLevel >800){break;}

    Serial.println("#################");
    delay(1000);
  }
}

void loop() // put your main code here, to run repeatedly:
{
  turnPumpOn();
  checkWaterLevel();
}