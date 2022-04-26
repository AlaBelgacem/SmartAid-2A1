#include <LiquidCrystal.h>

#define trigPin 13
#define echoPin 12


int Contrast = 100;
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // setting up the lcd

  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  
}
void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  /// getting data from QT

  char data;
  data = Serial.read();
  if(data=='1'){
    if (distance >= 400 || distance <=0)
    {
      //Serial.println("Out of range");
      Serial.write('1');
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("   Disconnected   ");
      lcd.setCursor(0, 1);
      lcd.print(" successfully  ");
    }
    else 
    {
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
  delay(500);
}
