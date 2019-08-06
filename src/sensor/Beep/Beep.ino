int sig = 7;
int highval = 8;
int cnt = 0;

void setup() {
  pinMode(highval, OUTPUT);
  pinMode(sig, OUTPUT);
//  pinMode(, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    digitalWrite(highval, HIGH);
    Serial.println("En HigH");
    delay(5000);
    Serial.println("Transmit Tone");
    while(true) {
      
      digitalWrite(sig, HIGH);
      delay(1);
      digitalWrite(sig, LOW);
      delay(1);
    }
}
