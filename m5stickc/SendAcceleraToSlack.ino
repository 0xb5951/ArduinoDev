#include <M5StickC.h>

// 加速度(単位が重力加速度[g])
float accX_g = 0;
float accY_g = 0;
float accZ_g = 0;

// 加速度(単位が加速度[m/s2])
float accX = 0;
float accY = 0;
float accZ = 0;

// 角速度
float GyroX = 0;
float GyroY = 0;
float GyroZ = 0;

void setup() {
  // Initialize the M5StickC object
  M5.begin();
  // 6軸センサ初期化
  M5.MPU6886.Init();
  // LED初期化   
  pinMode(10, OUTPUT);
  // LCD display
  M5.Lcd.setRotation(1);  // ボタンBが上になる向き
  M5.Lcd.fillScreen(BLACK);
  digitalWrite(10, HIGH);
}

void loop() {
  digitalWrite(10, HIGH);
  M5.MPU6886.getAccelData(&accX_g,&accY_g,&accZ_g);
  M5.MPU6886.getGyroData(&GyroX,&GyroY,&GyroZ);
  M5.Lcd.setCursor(0, 30);
  accX = accX_g * 9.8;
  accY = accY_g * 9.8;
  accZ = accZ_g * 9.8;
  M5.Lcd.printf("Acc : %.2f  %.2f  %.2f   ", accX, accY, accZ);
  M5.Lcd.printf("Gyro : %.2f  %.2f  %.2f   ", GyroX, GyroY, GyroZ);

  if (abs(accX + accY + accZ) > 19.6) {
    digitalWrite(10, LOW);
  }
  delay(500);
}
