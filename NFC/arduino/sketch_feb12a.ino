#include <HTTPClient.h>
#include <MFRC522.h> //library responsible for communicating with the module RFID-RC522
#include <SPI.h> //library responsible for communicating of SPI bus
#include <WiFi.h>
#define SS_PIN         21
#define RST_PIN        22
#define SIZE_BUFFER    18
//used in authentication
MFRC522::MIFARE_Key key;
//authentication return status code
MFRC522::StatusCode status;
// Defined pins to module RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
int httpResponseCode;
const char* ssid = "poc";
const char* password =  "pocpocpoc";

void setup()
{
    pinMode(32, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("initialised!");
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(25, HIGH);
    } else {
        digitalWrite(25, LOW);
        if (!mfrc522.PICC_IsNewCardPresent())
            return;
        if (!mfrc522.PICC_ReadCardSerial())
            return;
        HTTPClient http;
        http.begin("http://192.168.0.130:5000/");
        for (int a = 0 ; a <= mfrc522.uid.size ; a++)
            Serial.print(mfrc522.uid.uidByte[a]);
        int httpResponseCode = http.POST((char *) mfrc522.uid.uidByte);
        if (httpResponseCode > 0) {
            String response = http.getString();
            getState(httpResponseCode);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        for (int a = 0 ; a <= mfrc522.uid.size ; a++)
            mfrc522.uid.uidByte[a] = 0;
        http.end();
  }
}

void getState(int code) {
    Serial.println(code);
    if (code == 200) {
        digitalWrite(32, HIGH);
        digitalWrite(26, HIGH);
    } else if (code == 404) {
        digitalWrite(33, HIGH);
    }
    delay(1000);
    digitalWrite(26, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
}

