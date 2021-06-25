#include <SPI.h>
#include <LoRa.h>


int loopcounter = 0;


void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  analogReference(INTERNAL);
  Serial.begin(9600);
  while (!Serial);



  if (!LoRa.begin(433E6)) {
    Serial.println("LoRaError");
    while (1);
  }

  //LoRa.setSignalBandwidth(Bandwidth);   // signal bandwidth in Hz, defaults to 125E3
  //LoRa.setSpreadingFactor(8);           // ranges from 6-12,default 7 see API docs
  LoRa.setSyncWord(0xF3);               // byte value to use as the sync word, defaults to 0x12
  LoRa.enableCrc();                     // Enable or disable CRC usage, by default a CRC is not used
  LoRa.setTxPower(20);
}


void loop() {
  float volts = (analogRead(A0)*1.1/1024.0) * (99.5+9.97)/9.97;
  /*Serial.print(volts); */
  

  if (loopcounter < 2){
    LoRa.beginPacket();
    LoRa.print("0xA2B2");  //  your key here 
    LoRa.endPacket();
    delay(500);
   }

  if (volts < 3.3 and loopcounter == 1 ){
    LoRa.beginPacket();
    LoRa.print("0xA3B3");   //  your low Battery key here
    LoRa.endPacket();
  }

  if(loopcounter > 2){
    digitalWrite(3, LOW); // sets the digital pin 3 off
  }

  loopcounter ++;
  delay(20);
}
