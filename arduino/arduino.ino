#define trigPin 13
#define echoPin 12
#include <LiquidCrystal.h>
int Contrast = 100;

LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  distance = (duration / 2) * 0.034;

  /// getting data from QT
  String user;
  int etat = 0;
  char data;

  bool test = false;

  
  user = Serial.readString();
  lcd.setCursor(0, 0);
  lcd.print(user);

/*if(user.charAt(0)=='*'){
  lcd.setCursor(0, 0);
  lcd.print(user);
  etat=1;
}*/
  
  data = Serial.read();



  if (data == '1') {
    if (distance >= 150 || distance <= 0)
    {
      Serial.write('1');
      digitalWrite(13, HIGH);
      test = true;
    }
  }
  if (test) {
    lcd.setCursor(1, 1);
    lcd.print("a deconnecte");
  }
  delay(500);
}
