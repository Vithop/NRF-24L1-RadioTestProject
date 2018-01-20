#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const int radioON = 2;
const int testLED = 3;

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  pinMode(radioON, OUTPUT);
  pinMode(testLED, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  char text[32] = "";
  digitalWrite(testLED, HIGH);

  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    if (transData == "nrftest") {
      digitalWrite(radioON, HIGH);
      delay(500);
      digitalWrite(radioON, LOW);
    }
  }
  delay(250);
  digitalWrite(testLED, LOW);
  delay(250);
}
