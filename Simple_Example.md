# HC-12 Si4438 433MHz Module

HC-12_Si4438_433MHz_Module

AT-Commands
```C++
// See SoftwareSerial example 
// https://www.arduino.cc/en/tutorial/SoftwareSerialExample

#include <SoftwareSerial.h>;
#define RX 2 //Connect to the TX pin of the HC-12
#define TX 3 //Connect to the RX pin of the HC-12
SoftwareSerial mySerial(RX, TX);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
```

RX
```C++
void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if(Serial.available() > 0)
    {
        String input = Serial.readString();
        if(input == "Hello World")
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }

}
```

TX
```C++
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Hello World");
  delay(2000);
}
```

Links
- [Si4438 Chip](https://www.silabs.com/wireless/proprietary/ezradiopro-sub-ghz-ics/device.si4438)
- [Original board](https://make.net.za/product/hc12-si4438-433mhz-module/)
- [Fake board](https://botshop.co.za/products/hc-12-si4463-wireless-serial-module-433-mhz-1000m)
- [Fake board distance fix](https://www.instructables.com/HC-12-Distance-Problems/)
