#include <ArduinoJson.h>

void setup() {

  Serial.begin(9600);

  while (!Serial) continue;

  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();

  root["id"] = ;
  root["temperature"] = ;
 root["humidity"] = "gps";
  root["date_time"] = 1351824120;
 root["longitude"] = "gps";
  root["latitude"] = 1351824120;
 root["satlites"] = "gps";
  root["speed"] = 1351824120;

  root.printTo(Serial);
  // This prints:
  // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}

  Serial.println();

  root.prettyPrintTo(Serial);
  // This prints:
  // {
  //   "sensor": "gps",
  //   "time": 1351824120,
  //   "data": [
  //     48.756080,
  //     2.302038
  //   ]
  // }
}

void loop() {
  // not used in this example
}
