#include <HTTPClient.h>
#include <MFRC522.h>                //library responsible for communicating with the module RFID-RC522
#include <SPI.h>                    //library responsible for communicating of SPI bus
#include <WiFi.h>
#include <LiquidCrystal.h>

#define SS_PIN          21
#define RST_PIN         22
#define SIZE_BUFFER     18

MFRC522::MIFARE_Key key;            //used in authentication
MFRC522::StatusCode status;         //authentication return status code
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Defined pins to module RC522

const int rs = 27, en = 14, d4 = 32, d5 = 33, d6 = 25, d7 = 26;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int httpResponseCode;
const char* ssid        =           "poc";
const char* password    =           "pocpocpoc";
const char* MASTER_KEY  =           "098A4A73";

void setup()
{
    pinMode(32, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(2, OUTPUT);
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("initialised!");
    lcd.begin(16, 2); // Print a message to the LCD.
    lcd.display();
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Scanner votre");
    lcd.setCursor(0, 1);
    lcd.print("Carte POC <3");
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(25, HIGH);
    } else {
        digitalWrite(25, LOW);
        if (!mfrc522.PICC_IsNewCardPresent())
            return;
        if (!mfrc522.PICC_ReadCardSerial())
            return;
        HTTPClient http;
        http.begin("http://192.168.0.134:5000/");
        for (int a = 0; a <= mfrc522.uid.size; a += 1)
            Serial.print(mfrc522.uid.uidByte[a]);
        httpResponseCode = http.POST((char *) mfrc522.uid.uidByte);
        char buffer[mfrc522.uid.size];
        array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, buffer);
        if (strcmp(buffer, MASTER_KEY) == 0)
            getState(200);
        if (httpResponseCode > 0){
            String response = http.getString();
            getState(httpResponseCode);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        for (int a = 0; a <= mfrc522.uid.size; a += 1)
            mfrc522.uid.uidByte[a] = 0;
        http.end();
    }
}

void getState(int code)
{
    Serial.println(code);
    lcd.clear();
    int timer = 60 * 60;
    if (code == 200) {
        digitalWrite(32, HIGH);
        digitalWrite(2, HIGH);
        while (timer > 0)
        {
            timer -= 1;
            lcd.setCursor(0, 0);
            lcd.print("Temps restant :");
            lcd.setCursor(0, 1);
            lcd.print(timer / 60);
            lcd.print("mn ");
            lcd.print(timer % 60);
            lcd.print("s");
            delay(1000);
        }
    } else if (code == 404) {
        lcd.setCursor(0, 0);
        lcd.print("Error");
        digitalWrite(33, HIGH);
        delay(1000);
    }
    lcd.clear();
    digitalWrite(2, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
}
