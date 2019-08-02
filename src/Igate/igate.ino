#include <Ethernet.h>
#include <SPI.h>

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 4000;//900000; // READING INTERVAL 15m

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x1B, 0x3B };
EthernetClient client;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  } 
  delay(1000); // GIVE THE SENSOR SOME TIME TO START
}

void loop(){

  // String data = "data=";
  String data = "data={\"id\":\"test01\", \"temperature\":\"23\", \"humidity\":\"88.3\", \"date_time\":\"2019-07-12 12:15:15\", \"longitude\":\"4025.1234W\", \"latitude\":\"4025.1234W\", \"satellites\":\"5\",\"speed\":\"12.1\"}"; 
  
  int checkblock;
  if (checkblock = client.connect("192.168.2.123",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /test/parsing.php HTTP/1.1");//REPLACE WITH YOUR URLS
    client.println("Host: 192.168.2.123");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection:close");
    client.print("Content-Length:");
    client.println(data.length());
    client.println();
    client.print(data);
    
    client.flush();

    Serial.print("send data: ");
    Serial.println(data);
    
    delay(1000);
    // Check response
    /*while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    */
    client.stop();

  }

  delay(6000); // WAIT 6s BEFORE SENDING AGAIN
}
