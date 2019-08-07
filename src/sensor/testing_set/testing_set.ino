#include <ArduinoJson.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to

dht DHT;
int highval = 9;

// Connect the GPS TX (transmit) pin to Digital 8
// Connect the GPS RX (receive) pin to Digital 7
SoftwareSerial mySerial(7, 8);
Adafruit_GPS GPS(&mySerial);
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  false

void setup()
{
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  delay(5000);
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);

  Serial.begin(4800);
  Serial.println("C");
  delay(3);
  Serial.print("MW1AW\r\n");               //SET YOUR CALLSIGN HERE, HERE YOU SEE W1AW
  delay(10);                       
  Serial.print("PWIDE1-1,WIDE2-1\r\n");    //SET DIGIPATH HERE
  delay(10);
  pinMode(highval, OUTPUT);
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  char c = GPS.read(); 
  DHT.read11(dht_apin);

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (timer > millis())
    timer = millis();
  String date_time;

  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    
    date_time.concat("20");
    date_time.concat(GPS.year); date_time.concat('-');
    date_time.concat(GPS.month); date_time.concat('-');
    date_time.concat(GPS.day);
    date_time.concat(" ");
    
    if (GPS.hour < 10) {
      date_time.concat("0");
    }
    date_time.concat(GPS.hour);
    date_time.concat(":"); 
    
    if (GPS.minute < 10) {
      date_time.concat("0");
    }
    date_time.concat(GPS.minute);
    date_time.concat(":");
    
    if (GPS.seconds < 10) {
      date_time.concat("0");
    }
    date_time.concat(GPS.seconds);
  }
  
  StaticJsonDocument<200> doc;
  
  doc["id"] = "test01";
  doc["temperature"] = DHT.temperature;
  doc["humidity"] = DHT.humidity;
  doc["date_time"] = date_time;
  doc["longitude"] = GPS.longitude;
  doc["latitude"] = GPS.latitude;
  doc["satellites"] = (int)GPS.satellites;
  doc["gps_speed"] = GPS.speed;
//  serializeJsonPretty(doc, Serial);
  Serial.print("Location: ");
  Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
  Serial.print(", ");
  Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);

  Serial.print("Speed (knots): "); Serial.println(GPS.speed);
  Serial.print("Angle: "); Serial.println(GPS.angle);
  Serial.print("Altitude: "); Serial.println(GPS.altitude);
  Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
  
  Serial.println("C");
  delay(10);
  Serial.print("W");
  Serial.println("transmit data");  
// trasmit
  digitalWrite(highval, HIGH);
  Serial.print("!>");
  serializeJson(doc, Serial);
  Serial.print("\r\n");
  digitalWrite(highval, LOW);
  Serial.println("C");
  delay(10);
  Serial.print("W");
  Serial.println("data transmitted");
  delay(2000);
}
