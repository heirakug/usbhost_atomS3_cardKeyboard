#define 

#include <M5Unified.h>
#include <Wire.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define CARDKB_ADDR 0x5F
#define SDA_PIN 13 //stomS3:2,stampS3:13
#define SCL_PIN 15 //stomS3:1,stampS3:15

void setup() {
  auto cfg = M5.config();
  cfg.external_spk = false;  // 外部スピーカーを無効化
  M5.begin(cfg);

  Wire.begin(SDA_PIN, SCL_PIN);  // SDA, SCL ピンの指定（M5AtomS3 LiteのG1とG2ピン / m5stampS3の13と15）
  Serial.begin(115200);

  Keyboard.begin();
  USB.begin();
}

void loop() {
  Wire.requestFrom(CARDKB_ADDR, 1);
  while (Wire.available()) {
    char c = Wire.read();
    /*
    // debug
    if (c != 0) {
      // 受信したデータを16進数形式で出力
      Serial.print("Received data in hex: 0x");
      Keyboard.print("Received data in hex: 0x");
      if (c < 0x10) {
        Serial.print("0");  // 1桁の場合は0を追加
        Keyboard.print("0");
      }
      Serial.println(c, HEX);
      Keyboard.println(c, HEX);
    }
    */

    if (c != 0) {

      if (c == '\r') {
        // CR（キャリッジリターン）を受信したら改行を出力
        Serial.println();
        Keyboard.println();
      } else if (c == '\n') {
        // LF（改行）を受信したら何もしない（CRとのペアで処理される）
      } else if (c == 0x1B) {
        // ESCキーを受信した場合
        Keyboard.write(KEY_ESC);  // ESCキーを送信
      } else {
        Serial.print(c);  // シリアルモニタにキーボードの入力を出力
        Keyboard.print(c);
        // キーボード入力に応じて追加の処理を行うことができます
      }
    }
  }
  delay(10);
}
