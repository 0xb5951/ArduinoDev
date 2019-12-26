#include <ssl_client.h>
#include <WiFiClientSecure.h>

const char* Host = "https://slack.com/api/";
size_t BUF_SIZE = 1024;

void send_slack(uint8_t* image_data, size_t image_sz) {
  const char* slack_bot_token = get_slack_bot_token();
  const char* oauth_token = get_oauth_token();

  String path = "files.upload";
  String url = Host + path;

  WiFiClientSecure client;

  if (!client.connect(url, 443)) {
    Serial.println("connection failed");
    return;
  }

  if (image_data == NULL && image_sz == 0 ) {
    Serial.println("datafile nothing");
    return;
  }

  // header set
  client.print("POST " + url + " HTTP/1.1");
  client.println("Host: " + (String)Host);
  client.println("User-Agent: M5Stack");
  client.println("Connection: close");
  client.println("Content-Type: multipart/form-data;");
  client.println("Authorization: Bearer " + slack_bot_token);
  client.println("Content-Length: " + image_sz);
  client.print(header);
  
  // body
  String body = "token=" + oauth_token + "&channel=" + "#t_mizushima" + "&initial_comment=From M5stickV!";
  client.print(body);

  client.write(image_data, BUF_SIZE);

  bool Success_h = false;
  uint8_t line_try = 3;

  size_t BUF_SIZE = 1024;
  if ( image_data != NULL) {
    
    uint8_t *temp = image_data;
    size_t sz = image_sz;

    // バッファサイズごとに記述
    while ( temp != NULL && sz) {
      if ( sz >= BUF_SIZE) {
        client.write(temp, BUF_SIZE);
        temp += BUF_SIZE; sz -= BUF_SIZE;
      } else {
        client.write(temp, sz);
        temp += sz; sz = 0;
      }
    }
  }

  while ( client.connected() && !client.available()) delay(10);
  
  if ( client.connected() && client.available() ) {
    String resp = client.readStringUntil('\n');
    httpCode    = resp.substring(resp.indexOf(" ") + 1, resp.indexOf(" ", resp.indexOf(" ") + 1)).toInt();
    Success_h   = (httpCode == 200);
    Serial.println(resp);
  }

  client.stop();
}




// void send_slack(File *file) {
//   const char* slack_bot_token = get_slack_bot_token();
//   const char* oauth_token = get_oauth_token();
  
//   HTTPClient http;
//   String url = "https://slack.com/api/files.upload";

//   const int capacity = JSON_OBJECT_SIZE(4);
//   StaticJsonDocument<capacity> json_request;
//   json_request["token"] = oauth_token;
//   json_request["channel"] = "#t_mizushima";
//   json_request["filename"] = "From M5stickV!";
//   json_request["initial_comment"] = "From M5stickV!";
//   json_request["file"] = file->read();

//   http.begin(url);
//   http.addHeader("Content-Type", "application/json");
//   http.addHeader("Authorization", String("Bearer ") + slack_bot_token);

//   serializeJson(json_request, buffer, sizeof(buffer));
//   unsigned int responseCode = http.POST((uint8_t*)buffer, strlen(buffer));
//   String payload = http.getString();

//   // M5.Lcd.printf("status code: %d", responseCode);
//   // M5.Lcd.printf("payload: %s", payload.c_str());
// }