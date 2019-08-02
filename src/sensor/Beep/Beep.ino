int sig = 7;
int highval = 8;
int cnt = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(highval, OUTPUT);
  pinMode(sig, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
//  if(cnt == 6){
//    digitalWrite(highval, HIGH);
//    Serial.println("En HigH");
//    delay(10000);
//  }
//  else if(cnt > 12){
//    cnt = 0;
//    digitalWrite(highval, LOW);
//    Serial.println("En Low");
//    delay(5000);
//  }
  digitalWrite(highval, HIGH);
  Serial.println("En HigH");

  while(true){
    digitalWrite(sig, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("TXD HIGH");
    delay(10000);
    digitalWrite(sig, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("TXD LOW");
    delay(5000);
  }
  delay(10000);
//  cnt++;

//  digitalWrite(highval, LOW);
//  Serial.println("En Low");
//  delay(5000);
//  cnt++;
  
}
