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
  if(cnt == 6){
    digitalWrite(highval, HIGH);
    Serial.println("En HigH");
  }
  else if(cnt > 12){
    cnt = 0;
    digitalWrite(highval, LOW);
    Serial.println("En Low");

  }
  digitalWrite(sig, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);         
  cnt++;
  Serial.println("TXD HIGH");
  digitalWrite(sig, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  cnt++;
  Serial.println("TXD LOW");
}
