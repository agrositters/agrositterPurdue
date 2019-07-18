/*
#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
*/
#include <Ethernet.h>
#include <SPI.h>

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL
int i=0;
int t = 0; // TEMPERATURE VAR
int h = 0; // HUMIDITY VAR


byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x1B, 0x3B };
EthernetClient client;

void setup() {
  Serial.begin(9600);
 //pinMode(3, INPUT);      // sets the digital pin as output
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
//dht.begin();
  delay(1000); // GIVE THE SENSOR SOME TIME TO START

}
/*
int k(){
   if(digitalRead(3)){
        return 0;
       }else{
        return 1; 
       } 
       
}
int m(){
   if(analogRead(A0)<1022){
        return 1;
       }else{
        return 0; 
       } 
       
}
*/
void loop(){
  h = 1;//(int) dht.readHumidity();
  t = 2;//(int) dht.readTemperature();
  Serial.println("loop start");
  /*
  Serial.println(analogRead(A0));
  String a = String(k());
  String b = String(m());
  String data = "Temperature=";
  data.concat(t);
  data.concat("&Humidity=");
  data.concat(h);
  data.concat("&Door=");
  data.concat(a);
  data.concat("&intrusion=");
  data.concat(b);
*/

  String data = "test1=3333&test2=2222.22";
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
    
/*
    client.print("GET 192.168.2.72/test_post.php?"); // This
    client.print("test1="); // This
    client.print(1111); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
    client.print("&test2="); // This
    client.print(2222.22); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: 192.168.2.72"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie.Host: "www.yourwebpage.com")
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println("Connection: close");
*/
    client.flush();

    Serial.print("send data: ");
    Serial.println(data);
    
    delay(1000);
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    client.stop();

  }

  delay(6000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}
