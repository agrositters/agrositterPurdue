#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to

dht DHT;
uint32_t timer = millis();
int highval = 9;
int count = 0;

// Connect the GPS TX (transmit) pin to Digital 8
// Connect the GPS RX (receive) pin to Digital 7
SoftwareSerial mySerial(7, 8);
Adafruit_GPS GPS(&mySerial);

void setup()
{
  // OPEN Serial port for GPS
  Serial.begin(115200);
  delay(5000);
  
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // SET Update rate to 1 Hz
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA); 

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);

  Serial.begin(4800);
  Serial.println("C");
  delay(3);
  //SET CALLSIGN
  Serial.print("MKD9NDI-1\r\n");               
  delay(10);
  //SET DIGIPATH                    
  Serial.print("PWIDE1-1,WIDE2-1\r\n");    
  delay(10);
  pinMode(highval, OUTPUT);
  delay(10);
}

void loop() 
{

  char c = GPS.read(); 
  DHT.read11(dht_apin);

  if (timer > millis())
    timer = millis();

  String date_time;

  // Make date_time string
  if (millis() - timer > 2000) {
    timer = millis(); 
    
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
  
  String data = "";
  count++;

  // Make contents to put into sending packet
  data = data + "test"+(String)count + ", ";
  data = data + (String)DHT.temperature + ", ";
  data = data + (String)DHT.humidity + ", ";
  data = data + date_time + ", ";
  data = data + (String)GPS.longitude + ", ";
  data = data + (String)GPS.latitude + ", ";
  int sate = (int)GPS.satellites;
  data = data + (String)sate + ", ";
  data = data + (String)GPS.speed;
  
  // Trasmitting
  
  // Pull up
  digitalWrite(highval, HIGH);
  
  // Send string
  Serial.print("!");
  Serial.print(data);
  Serial.print("\r\n");
  
  //Wait 3s until send whole packet
  delay(3000);
  
  // Pull down
  digitalWrite(highval, LOW);

  // Print LCD count 
  Serial.println("C");
  delay(10);
  Serial.print("W");
  Serial.println(count);
  delay(10000);
}
