#include <M5Unified.h>
#include <Wire.h>

#define CARDKB_ADDR 0x5F
#define SDA_PIN 2
#define SCL_PIN 1

void setup() {
  auto cfg = M5.config();
  cfg.external_spk = false;
  M5.begin(cfg);
  
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);
}

void loop() {
  Wire.requestFrom(CARDKB_ADDR, 1);
  while (Wire.available()) {
    char c = Wire.read();
    if (c != 0) {
      Serial.print(c);  // シリアルモニタにキーボードの入力を出力

      // キーボード入力に応じて追加の処理を行うことができます
    }
  }
  delay(10);
}
