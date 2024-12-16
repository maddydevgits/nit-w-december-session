#include<DHT.h>

DHT dht(23,DHT11);

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)) {
    Serial.println("Error: DHT11 issue with Data");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(",Temperature: ");
  Serial.println(t);
  delay(4000);
}