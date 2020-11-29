#include <Servo.h>

int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];

int pos = 0;
int pos_offset = 65;

Servo dial;

void setup()
{
  dial.attach(2);
  dial.write(pos + pos_offset);
  delay(50);
  Serial.begin(9600);
}

void calculateDepth(int analog)
{
  //double depth = -.28486675980736 * (sqrt(450.00604081799 - analog) - 13.038636463142);
  //Serial.println(depth);
  
  if(analog >= 280 && analog < 367)
  {
    depth = (analog / 87.000) - (280.000/87.000);
    Serial.println(depth);
  }else if(analog >= 367 && analog < 410)
  {
    depth = (analog / 43.000) - (324.000/43.000); //LINEAR EXTRAPOLATION TO DETERMINED DEPTH IN CM
    Serial.println(depth);
  }else if(analog >= 410 && analog < 441)
  {
    depth = (analog / 31.000) - (348.000/32.000);
    Serial.println(depth);
  }else if(analog >= 441 && analog < 460)
  {
    depth = (analog / 19.000) - (384.000/19.000);
    Serial.println(depth);
  }else
  {
    Serial.println("DEPTH unable to be caculated!");  
  }
  
}

void loop()
{ 
  //0-5 = Dry
  
  //280 = 0 cm
  //367 = 1cm
  //410 2 cm
  //441 = 3 cm
  //451 = 4 cm
     
    //int value = analogRead(adc_id); // get adc value
   // Serial.println(value);
    //calculateDepth(value);
    delay(50);

    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      Serial.print(printBuffer);
      HistoryValue = value;
      
      int value = analogRead(adc_id); // get adc value
      Serial.println(value);
      calculateDepth(value);

    }
   
}   
