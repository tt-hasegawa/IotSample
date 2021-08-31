#include <M5StickC.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

/* グローバル変数の宣言 */
HTTPClient http; // HTTPアクセスクライアント
DynamicJsonDocument json_request(500); // JSON
char buffer[1024]; // 送信文字列
time_t t; // 現在時刻
struct tm *tm; // 現在時刻の構造体

/* 初期処理 */
void setup() {
  // M5デバイスの初期化
  M5.begin();
  M5.Lcd.setRotation(3);
  // WiFi接続
  WiFi.begin("honeyspot", "11111111");
  M5.Lcd.print("\nConnecting Wifi...\n");
}

/* メインループ */
void loop() {
  M5.Lcd.setCursor(0,0); //Set the cursor at (0,0).
  if((WiFi.status() == WL_CONNECTED)) {
    M5.Lcd.print("[HTTP] begin...\n");
    // HTTP送信先を記述
    http.begin("https://immense-badlands-61064.herokuapp.com/add");
    http.addHeader("Content-Type","application/json");    
    M5.Lcd.print("[HTTP] POST...\n");

    // 現在時刻を取得
    t = time(NULL);
    tm = localtime(&t);
    char now[32];
    sprintf(now,"%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);

    // JSONデータに埋めていく
    json_request["time"]=now;
    json_request["val1"]="あああ";
    json_request["val2"]=20;
    // JSONを文字列に変換
    serializeJson(json_request, buffer, sizeof(buffer));
    Serial.println(buffer);
    // JSONを変換した文字列をPOSTで送信
    int httpCode = http.POST((uint8_t*) buffer,strlen(buffer));
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    http.end();
  }else{
    M5.Lcd.print("connect failed");
  }
  // 10秒待機
  delay(10*1000);
  M5.Lcd.fillRect(0,0,160,80,BLACK); //clear the screen.
}
