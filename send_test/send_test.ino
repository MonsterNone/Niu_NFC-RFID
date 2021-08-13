#include <RCSwitch.h>

#define tPin 6 // 发射模块data引脚

int code = '你的遥控码';
int pulseLength = '脉冲长度';

RCSwitch tSwitch = RCSwitch();
RCSwitch rSwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:

  // 车边测试
  tSwitch.enableTransmit(tPin);
  tSwitch.setPulseLength(pulseLength);
  tSwitch.send(code, 24);
}

void loop() {
  // put your main code here, to run repeatedly:
}
