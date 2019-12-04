#include <M5StickC.h>

void setup() {
    M5.begin(); // M5オブジェクトを初期化する
    M5.Lcd.setRotation(3); //左側を上にする
    M5.Lcd.setCursor(0,0,2); //表示位置とフォントを指定
    M5.Lcd.print("Hello World");
}

void loop(){
}
