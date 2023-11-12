#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


void setup() {
  pinMode(13,OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);


  Serial.println("Enter AT commands:");

  mySerial.begin(38400);
  //AT+RESET
  mySerial.write(int('A'));
  mySerial.write(int('T'));
  mySerial.write(int('+'));
  mySerial.write(int('R'));
  mySerial.write(int('E'));
  mySerial.write(int('S'));
  mySerial.write(int('E'));
  mySerial.write(int('T'));
  mySerial.write(13); // CR
  mySerial.write(10); // NL
  while (!mySerial.available()) {}
  while (mySerial.available()) {
    Serial.println(mySerial.readString());
  }
  //AT+INIT
  mySerial.write(int('A'));
  mySerial.write(int('T'));
  mySerial.write(int('+'));
  mySerial.write(int('I'));
  mySerial.write(int('N'));
  mySerial.write(int('I'));
  mySerial.write(int('T'));
  mySerial.write(13); // CR
  mySerial.write(10); // NL

  while (!mySerial.available()) {}
  while (mySerial.available()) {
    Serial.println(mySerial.readString());
  }

  //AT+IAC=9e8b33
  mySerial.write(int('A'));
  mySerial.write(int('T'));
  mySerial.write(int('+'));
  mySerial.write(int('I'));
  mySerial.write(int('A'));
  mySerial.write(int('C'));
  mySerial.write(int('='));
  mySerial.write(int('9'));
  mySerial.write(int('e'));
  mySerial.write(int('8'));
  mySerial.write(int('b'));
  mySerial.write(int('3'));
  mySerial.write(int('3'));
  mySerial.write(13); // CR
  mySerial.write(10); // NL

  while (!mySerial.available()) {}
  while (mySerial.available()) {
    Serial.println(mySerial.readString());
  }

  //AT+CLASS=0
  mySerial.write(int('A'));
  mySerial.write(int('T'));
  mySerial.write(int('+'));
  mySerial.write(int('C'));
  mySerial.write(int('L'));
  mySerial.write(int('A'));
  mySerial.write(int('S'));
  mySerial.write(int('S'));
  mySerial.write(int('='));
  mySerial.write(int('0'));
  mySerial.write(13); // CR
  mySerial.write(10); // NL

  while (!mySerial.available()) {}
  while (mySerial.available()) {
    Serial.println(mySerial.readString());
  }

  //AT+INQM=1,9,48

  mySerial.write(int('A'));
  mySerial.write(int('T'));
  mySerial.write(int('+'));
  mySerial.write(int('I'));
  mySerial.write(int('N'));
  mySerial.write(int('Q'));
  mySerial.write(int('M'));
  mySerial.write(int('='));
  mySerial.write(int('1'));
  mySerial.write(int(','));
  mySerial.write(int('9'));
  mySerial.write(int(','));
  mySerial.write(int('4'));
  mySerial.write(int('8'));
  mySerial.write(13); // CR
  mySerial.write(10); // NL

  while (!mySerial.available()) {}
  while (mySerial.available()) {
    Serial.println(mySerial.readString());
  }
}


unsigned int hexToDec(String hexString) {

  unsigned int decValue = 0;
  int nextInt;

  for (int i = 0; i < hexString.length(); i++) {

    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);

    decValue = (decValue * 16) + nextInt;
  }

  return decValue;
}


int OK = 1;


void loop()

{  
  if (OK) {
    mySerial.write(int('A'));
    mySerial.write(int('T'));
    mySerial.write(int('+'));
    mySerial.write(int('I'));
    mySerial.write(int('N'));
    mySerial.write(int('Q'));
    mySerial.write(13); // CR
    mySerial.write(10); // NL
    OK = 0;
  }
  while (!mySerial.available()) {}
  while (mySerial.available()) {
    
    String x = String(mySerial.readString());
    int slashn = x.indexOf("\n");
    int nod = 0;
    int xlen = x.length()/(slashn+1);
    if (x.endsWith("OK\r\n")) {
      x = x.substring(0, x.length() - 4);
      OK = 1;
    }
    for (int i = 0; i < xlen; i++) {
      if (i != 0) {
        x = x.substring(slashn+1);
      }
      slashn = x.indexOf("\n");
      String rssi = x.substring(slashn-5, slashn-1);
      int decNO = hexToDec(rssi);

      if (x.substring(5,9) == "5C17" || x.substring(5,9) == "98D3") {
        if (decNO < -60 || decNO == 0) {
          digitalWrite(13,HIGH);
          digitalWrite(12, HIGH);
          Serial.write("1");
        }
        else {
          digitalWrite(13,LOW);
          digitalWrite(12, LOW);
          Serial.write("2");
        }
        Serial.println(decNO);
        Serial.print("RSSI:" + String(decNO));
        Serial.println(x.substring(5,slashn-11));
    }
  }
  delay(1);
}}
