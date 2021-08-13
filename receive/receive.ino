#include <RCSwitch.h>

#define rInt 0 // 接收模块interrput引脚，i0对应p2,i1对应p3

RCSwitch rSwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rSwitch.enableReceive(rInt);  // Receiver on interrupt 0 => that is pin #2
//  tSwitch.enableTransmit(6);/

}

void loop() {
  // put your main code here, to run repeatedly:
  if (rSwitch.available()) {
    output(rSwitch.getReceivedValue(), rSwitch.getReceivedBitlength(), rSwitch.getReceivedDelay(), rSwitch.getReceivedRawdata(), rSwitch.getReceivedProtocol());
    rSwitch.resetAvailable();
  }
}
