#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
String dataEmployee;
char data;
int i;

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
int nb_tours = 0;
#define SS_PIN 10
#define RST_PIN 9
byte lock = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);//declaration rfid
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    servo.attach(3);
    /*
    lcd.begin(16, 2);

    */
    lcd.begin(16,2);
    lcd.print("Scanner la carte..");
    SPI.begin();     // Initiate  SPI bus (lire les donne)
    mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop()
{

    /*
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Put your card ");
    lcd.setCursor(5, 1);
    */
    //delay(300);


    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    String content = "";
    String msg = "";
    byte letter;

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    msg = content + "#";
    //send data
    //delay (5000);

    for (i = 0; i < msg.length(); i++)
    {
        Serial.write(msg[i]);
        delay (100);
    }

    if (Serial.available() > 0)
    {
        dataEmployee=Serial.readString();

        //data=Serial.read();
        if(dataEmployee!="ERROR")
        {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Carte Scanner..");

            if ( lock == 0 ) {
                    servo.write(0);
                    delay(350);
                    servo.write(90);
                    delay(350);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Porte verrouillee");
                    delay(1500);
                    lcd.clear();
                    lock = 1;
                  } else if (lock == 1 ) {
                    servo.write(90);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Porte ouverte");
                    delay(1500);
                    lcd.clear();
                    lock = 0;
                  }

        }
        else if (dataEmployee=="ERROR")
        {
            lcd.clear();
            lcd.setCursor(0, 0);

            lcd.print("employee n'existe pas");
            for (int positionCounter = 0; positionCounter < 24; positionCounter++)
            {
                // scroll one position right:
                lcd.scrollDisplayLeft();
                // wait a bit:
                delay(350);
            }
            lcd.clear();
            lcd.print("Scanner la carte..");
        }
    }
}
