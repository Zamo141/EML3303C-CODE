#include <Servo.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>


#define TRIGGER_PIN  8 
#define ECHO_PIN     9
#define MAX_DISTANCE 50 

Servo distanceMeter;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int tempPin = 0;
int pos = 0; 
int pos_offset = 65; //65 is upright, //165 is 90 degree angle. change in value is 100!

void setup() 
{
  distanceMeter.attach(10);
  Serial.begin(115200);

  lcd.init(); // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  
  distanceMeter.write(pos + pos_offset);
  delay(100);
}
void loop() {
  Serial.print("Ping: ");
  int sensorPing = sonar.ping_cm();
  
  Serial.print(sensorPing); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  lcd.setCursor(0, 1);
  lcd.print("    cm");
  lcd.setCursor(0,1);
  lcd.print(sensorPing);  

  if(sensorPing > pos){
    for(int i = pos; i < sensorPing; i++){
      pos = i;
      distanceMeter.write(2*i + pos_offset);
      delay(15);  
    } 
  }else if (sensorPing < pos){
    for(int i = pos; i > sensorPing; i--){
      pos = i;
      distanceMeter.write(2*i + pos_offset);
      delay(15);
    }
  
  }
  delay(200);
  
}

