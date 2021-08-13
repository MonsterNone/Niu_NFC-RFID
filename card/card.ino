#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices
#include <RCSwitch.h>

RCSwitch rSwitch = RCSwitch();
RCSwitch tSwitch = RCSwitch();

#define SS_PIN 10 // RC522 sda
#define RST_PIN 9 // RC522 rst
#define T_PIN 6 // 315发送
#define R_INTERPUT 0 // 315接收，interupt 0, pin 2
#define BEEP 4 // 蜂鸣器

int pulseLength = '你的脉冲长度';
int code = '你的遥控码'; // 10进制
byte MYUID[] = {0xFA, 0xA7, 0x32, 0xB3}; // 你的ID卡的UID

MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);

  rSwitch.enableReceive(R_INTERPUT);
  tSwitch.enableTransmit(T_PIN);
  tSwitch.setPulseLength(pulseLength);

  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme

  pinMode(BEEP, OUTPUT);
}

bool checkTwo ( byte a[], byte b[] ) {
  for ( uint8_t k = 0; k < 4; k++ ) {   // Loop 4 times
    if ( a[k] != b[k] ) {     // IF a != b then false, because: one fails, all fail
      return false;
    }
  }
  return true;
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

  if (checkTwo(mfrc522.uid.uidByte, MYUID)) { // 验证成功
    Serial.println("OK");
    tSwitch.send(code, 24);
    digitalWrite(BEEP, HIGH);
    delay(80);
    digitalWrite(BEEP, LOW);
    delay(100);
    digitalWrite(BEEP, HIGH);
    delay(80);
    digitalWrite(BEEP, LOW);
  }
  else { // 验证失败
    Serial.println("False");
    digitalWrite(BEEP, HIGH);
    delay(500);
    digitalWrite(BEEP, LOW);
    for ( uint8_t i = 0; i < 4; i++) {
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
  }
}
