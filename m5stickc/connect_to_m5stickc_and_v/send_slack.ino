
size_t BUF_SIZE = 1024;
int httpCode = 404;

void send_slack(uint8_t* image_data, size_t image_sz) {
  const char* slack_bot_token = get_slack_bot_token();
  const char* oauth_token = get_oauth_token();

  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  if (image_data == NULL && image_sz == 0 ) {
    Serial.println("datafile nothing");
    return;
  }

  // header set
  client.print("POST " + url + " HTTP/1.1");
  client.print("Host: " + (String)Host);
  client.print("User-Agent: M5Stack");
  client.print("Connection: close");
  client.print("Content-Type: multipart/form-data; boundary=----WebKitFormBoundarySXkTMrIra0APbTor");
  client.print("Authorization: Bearer " + String(slack_bot_token));
  client.print("Content-Length: " + String(image_sz));

  bool Success_h = false;
  uint8_t line_try = 3;
  while (!Success_h && line_try-- > 0) {
    if (image_sz > 0) {
      size_t BUF_SIZE = 1024;
      if ( image_data != NULL) {
        uint8_t *p = image_data;
        size_t sz = image_sz;
        while ( p != NULL && sz) {
          if ( sz >= BUF_SIZE) {
            client.write( p, BUF_SIZE);
            p += BUF_SIZE; sz -= BUF_SIZE;
          } else {
            client.write( p, sz);
            p += sz; sz = 0;
          }
        }
      }

      while ( client.connected() && !client.available()) delay(10);
      if ( client.connected() && client.available() ) {
        String resp = client.readString();
        httpCode    = resp.substring(resp.indexOf(" ") + 1, resp.indexOf(" ", resp.indexOf(" ") + 1)).toInt();
        Success_h   = (httpCode == 200);
        Serial.println(resp);
      }
      delay(10);
    }
  }
  client.stop();
}



// void send_slack(uint8_t* image_data) {
//   const char* slack_bot_token = get_slack_bot_token();
//   const char* oauth_token = get_oauth_token();
  
//   HTTPClient http;
//   String url = "https://slack.com/api/files.upload";

  

//   const int capacity = JSON_OBJECT_SIZE(6);
//   StaticJsonDocument<capacity> json_request;
//   json_request["token"] = oauth_token;
//   json_request["channel"] = "#t_mizushima";
//   json_request["filename"] = "From M5stickV!";
//   json_request["initial_comment"] = "From M5stickV!";
//   json_request["file"] = image_data;

//   http.begin(url);
//   http.addHeader("Content-Type", "application/json");
//   http.addHeader("Authorization", String("Bearer ") + slack_bot_token);

//   serializeJson(json_request, buffer, sizeof(buffer));
//   unsigned int responseCode = http.POST((uint8_t*)buffer, strlen(buffer));
//   String payload = http.getString();

//   M5.Lcd.printf("status code: %d", responseCode);
//   M5.Lcd.printf("payload: %s", payload.c_str());
// }