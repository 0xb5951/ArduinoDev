## 作ったものとその解説

### Hello World
最初にやった。環境構築が目的。
MtStickCの液晶にHello Worldと表示させる

### send Accelera to slack
Wifi接続するためのテスト。加速度センサの値を取得して、閾値を超えたらSlackにメッセージをpostする。
ついでに、LEDも光らせる。
 
### connect_to_m5stickc
M5StickCと接続して、wifi経由で接続するプログラム。
M5StickVで撮影した写真をグレースケールでSlackに送信する。
UART通信で受け取った画像をSlackに送信するところまでを担保する