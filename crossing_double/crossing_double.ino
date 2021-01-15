#include <HardwareSerial.h>
#include <ESP32Servo.h>
#include <DFRobotDFPlayerMini.h>
#include "RailSwitch.h"

const int sw_in1Pin = 25;
const int sw_out1Pin = 26;
const int sw_in2Pin = 32;
const int sw_out2Pin = 33;
const int serial_rx = 14;
const int serial_tx = 15;
const int led_1lPin = 18;
const int led_1rPin = 19;
const int led_2lPin = 22;
const int led_2rPin = 23;
const int servoPin1 = 2;
const int servoPin2 = 4;

#define LED_L 1
#define LED_R 2
#define DF_VOLUME 29

Servo sv1, sv2;
RailSwitch sw_in1(sw_in1Pin), sw_out1(sw_out1Pin), sw_in2(sw_in2Pin), sw_out2(sw_out2Pin);
DFRobotDFPlayerMini myDFPlayer;
HardwareSerial hs(2);
int angle, led_ctr, led_lr;
bool is_passing1, is_passing2, is_passing_first;

void setup() {
  Serial.begin(115200);

  // スイッチ初期化
  sw_in1.begin();
  sw_out1.begin();
  sw_in2.begin();
  sw_out2.begin();

  // サーボモーター初期化
  angle = 90;
  sv1.attach(servoPin1);
  sv2.attach(servoPin2);
  sv1.write(angle);
  sv2.write(angle);

  // DFPlayer初期化
  hs.begin(9600, SERIAL_8N1, serial_rx, serial_tx);
  int count = 0;
  while (count < 10) {
    delay(3000);
    if (!myDFPlayer.begin(hs)) {
      count++;
      Serial.print("DFPlayer initialize attempt ");
      Serial.println(count);
    }
    else {
      break;
    }
  }

  // LED初期化
  pinMode(led_1lPin, OUTPUT);
  pinMode(led_1rPin, OUTPUT);
  pinMode(led_2lPin, OUTPUT);
  pinMode(led_2rPin, OUTPUT);

  // DFPlayer初期化状態出力
  if (count < 10) {
    Serial.println("DFPlayer Initialized.");
    myDFPlayer.volume(DF_VOLUME);
    myDFPlayer.play(2);
    delay(2000);
  }
  else {
    Serial.println("DFPlayer Error.");
    digitalWrite(led_1lPin, HIGH);
    digitalWrite(led_1rPin, HIGH);
    digitalWrite(led_2lPin, HIGH);
    digitalWrite(led_2rPin, HIGH);
    delay(2000);
  }

  // LED消灯
  digitalWrite(led_1lPin, LOW);
  digitalWrite(led_1rPin, LOW);
  digitalWrite(led_2lPin, LOW);
  digitalWrite(led_2rPin, LOW);
  is_passing1 = false;
  is_passing2 = false;
  is_passing_first = true;
}
 
void loop(){
  // 1組み目のスイッチに列車が進入した？
  if (sw_in1.is_pushed()) {
    is_passing1 = true;
  }
  // 1組目のスイッチから列車が出た？
  else if (sw_out1.is_pushed()) {
    is_passing1 = false;
  }
  // 2組目のスイッチに列車が進入した？
  if (sw_in2.is_pushed()) {
    is_passing2 = true;
  }
  // 2組目のスイッチから列車が出た？
  else if (sw_out2.is_pushed()) {
    is_passing2 = false;
  }
  // どちらかに列車が進入した？
  if (is_passing1 || is_passing2) {
    // 進入直後の場合
    if (is_passing_first) {
      is_passing_first = false;
      // LEDの状態を初期化
      led_ctr = 20;
      led_lr = LED_L;
      // 警告音を再生
      myDFPlayer.play(1);
    }
    // 遮断桿が下り切っていない？
    if (angle < 180) {
      // 遮断桿を1度ずつ下す
      angle++;
      sv1.write(angle);
      sv2.write(angle);
    }
    // 変数led_lrの値に応じて左右どちらかのLEDを点灯
    digitalWrite(led_1lPin, led_lr == LED_L ? HIGH : LOW);
    digitalWrite(led_1rPin, led_lr == LED_R ? HIGH : LOW);
    digitalWrite(led_2lPin, led_lr == LED_L ? HIGH : LOW);
    digitalWrite(led_2rPin, led_lr == LED_R ? HIGH : LOW);
    // loop関数を20回実行したら点灯するLEDの左右を切り替え
    led_ctr--;
    if (led_ctr == 0) {
      led_ctr = 20;
      led_lr = (led_lr == LED_L) ? LED_R : LED_L;
    }
  }
  // 両方から列車が出ていて、かつ遮断桿が上り切っていない？
  else if (!is_passing1 && !is_passing2 && angle > 90) {
    is_passing_first = true;
    // 遮断桿を1度ずつ上げる
    angle--;
    sv1.write(angle);
    sv2.write(angle);
    // 警告音を止める
    myDFPlayer.pause();
    // LEDを消灯する
    digitalWrite(led_1lPin, LOW);
    digitalWrite(led_1rPin, LOW);
    digitalWrite(led_2lPin, LOW);
    digitalWrite(led_2rPin, LOW);
  }
  delay(20);
}
