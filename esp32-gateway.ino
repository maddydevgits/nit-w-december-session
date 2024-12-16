#include<DHT.h>
#include<WiFi.h>
#include<HTTPClient.h>

String apiGateway="https://mlew-api-iot.onrender.com";

const char* ssid="Purna";
const char* password="Galla4446";

DHT dht(23,DHT11);

void setup() {
  dht.begin();
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");
}

void loop() {
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)) {
    Serial.println("Error: DHT11 issue with Data");
    return;
  }

  Serial.print("#"); // # -> Start of Frame
  Serial.print(","); // , -> Seperator
  Serial.print(h); // h -> Humidity Value
  Serial.print(","); 
  Serial.print(t);
  Serial.print(",");
  Serial.println("~"); // ~ -> End of Frame

  sendDataToDashboard(apiGateway+"/store?label=Humidity&value="+String(h));
  delay(2000);

  sendDataToDashboard(apiGateway+"/store?label=Temperature&value="+String(t));
  delay(2000);
}

void sendDataToDashboard(String api){
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    http.begin(api);
    int responseCode=http.GET();
    if(responseCode>0){
      String response=http.getString();
      Serial.println(response);
      http.end();
    }
  }
}
