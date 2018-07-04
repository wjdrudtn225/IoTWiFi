#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char * ssid = "jks";
const char * password = "jks763500";
String VAR_ID = "5b3c6302c03f9720a420e34d";
String TOKEN = "A1E-arUwNe9tVKZO44AcZHeIe4mdiugzrl";


void setup () {
  Serial.begin(115200);// PC 시리얼 통신
  WiFi.begin(ssid,password);// WiFi 접속

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..\n");
    
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //WiFi가 연결되어 있는 경우 HTTP 접속
    HTTPClient http; //HTTPClient 클래스의 오브젝트 선언
    String ubidots = "http://things.ubidots.com/api/v1.6/variables/";
    ubidots += VAR_ID;
    ubidots += "/values/?token=";
    ubidots += TOKEN;
    http.begin(ubidots);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{\"value\":\"25\"}");

    if(httpCode > 0) {
      String payload = http.getString();//응답을 수신
      Serial.println(payload);// 수신된 데이터 출력
    }
    http.end();//HTTP 접속 종료
  }
  delay(30000);
}

