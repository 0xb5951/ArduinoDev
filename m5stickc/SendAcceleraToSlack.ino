#include <M5StickC.h>

// 加速度
float accX_g = 0;
float accY_g = 0;
float accZ_g = 0;

void setup() {
  // Initialize the M5StickC object
  M5.begin();
  //初期設定開始 LED ON
  pinMode(10, OUTPUT);
  // 6軸センサ初期化
  M5.MPU6886.Init();
  // LCD display
  M5.Lcd.setRotation(1);  // ボタンBが上になる向き
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.MPU6886.getAccelData(&accX_g,&accY_g,&accZ_g);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.printf("Acc : %.2f  %.2f  %.2f   ", accX_g, accY_g, accZ_g);
  delay(100);
}
