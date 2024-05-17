#include <M5Unified.h>
#include <Wire.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define CARDKB_ADDR 0x5F
#define SDA_PIN 2
#define SCL_PIN 1

void setup() {
  auto cfg = M5.config();
  cfg.external_spk = false;  // 外部スピーカーを無効化
  M5.begin(cfg);

  Wire.begin(SDA_PIN, SCL_PIN);  // SDA, SCL ピンの指定（M5AtomS3 LiteのG1とG2ピン）
  Serial.begin(115200);

  Keyboard.begin();
  USB.begin();
}

void loop() {
    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available()) {
      char c = Wire.read();
      if (c != 0) {
        Serial.print(c);  // シリアルモニタにキーボードの入力を出力
        Keyboard.print(c);
        // キーボード入力に応じて追加の処理を行うことができます
      }
    }
  delay(10);
}
