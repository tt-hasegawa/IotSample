#include "M5Atom.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
time_t t;
struct tm *tm;

void setup() {
  M5.begin(true,true,true);     // 基板を初期化
  WiFi.begin("w1flsp0t", "1q2w3e4r"); // WIFI接続
  Serial.println(WiFi.localIP()); // シリアルにIP出力
  dht.begin();        // センサー初期化
}
void loop() {
  if((WiFi.status() == WL_CONNECTED)) {
    // 現在時刻を取得
    time(&t);
    tm = localtime(&t);
    char now[32];
    sprintf(now,"%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);
    
    // センサーから温度／湿度を取得
    float humid = dht.readHumidity();
    float temp = dht.readTemperature();
    if(!isnan(humid) && !isnan(temp)){
      Serial.printf("[DHT11] %s %f (c) %f (%)\r\n",now,humid,temp); 
  
      // JSONドキュメントを生成
      StaticJsonDocument<JSON_OBJECT_SIZE(4)> json;
      char txt[255];
      json["now"] = now;
      json["val1"] = humid;
      json["val2"]  = temp;
      serializeJson(json,txt,sizeof(txt));
  
      // http送信
      HTTPClient http;
      http.begin("http://<PCのIPアドレス>:5000/add");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST((uint8_t *)txt, strlen(txt));
      Serial.printf("[http] %s send ok %i [%s]\r\n",now,httpCode,txt);
      http.end();
    }
  }
  delay(10000); // 10秒待機
}
