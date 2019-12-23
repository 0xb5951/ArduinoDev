#include <M5StickC.h>
#include <WiFi.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>

HardwareSerial serial_ext(2);

typedef struct {
  uint32_t length;
  uint8_t *buf;
} jpeg_data_t;

jpeg_data_t jpeg_data;
static const int RX_BUF_SIZE = 20000;
static const uint8_t packet_begin[3] = { 0xFF, 0xD8, 0xEA };

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 1);
  M5.Lcd.println("m5stick_uart_wifi_converter");

  setup_wifi();

  jpeg_data.buf = (uint8_t *) malloc(sizeof(uint8_t) * RX_BUF_SIZE);
  jpeg_data.length = 0;
  if (jpeg_data.buf == NULL) {
    Serial.println("malloc jpeg buffer 1 error");
  }

  serial_ext.begin(115200, SERIAL_8N1, 32, 33);
}

void loop() {
  M5.update();

  if (serial_ext.available()) {
    uint8_t rx_buffer[10];
    int rx_size = serial_ext.readBytes(rx_buffer, 10);
    if (rx_size == 10) {   //packet receive of packet_begin
      if ((rx_buffer[0] == packet_begin[0]) && (rx_buffer[1] == packet_begin[1]) && (rx_buffer[2] == packet_begin[2])) {
        //image size receive of packet_begin
        jpeg_data.length = (uint32_t)(rx_buffer[4] << 16) | (rx_buffer[5] << 8) | rx_buffer[6];
        int rx_size = serial_ext.readBytes(jpeg_data.buf, jpeg_data.length);

        M5.Lcd.drawBitmap(50,10,64,64,jpeg_data.buf);

      }
    }
  }
  vTaskDelay(10 / portTICK_RATE_MS);
}

void setup_wifi() {
  const char* ssid = get_ssid();
  const char* passwd = get_passwd();
  M5.Lcd.printf("ssid : %s", ssid);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  M5.Lcd.printf("WiFi connected");
  // M5.Lcd.printf("IP address: ");
  // M5.Lcd.printf(WiFi.localIP());
}