#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices

#define SS_PIN 10 // RC522 sda
#define RST_PIN 9 // RC522 rst

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
}

void print_uid(byte a[]) {
    for (uint8_t i = 0; i < 4; i++) {
        Serial.print(a[i] < 0x10 ? " 0" : " ");
        Serial.print(a[i], HEX);
    }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  mfrc522.PICC_HaltA(); // Stop reading

  print_uid(mfrc522.uid.uidByte);
}
