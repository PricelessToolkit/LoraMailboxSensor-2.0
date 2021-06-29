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
	// For accuracy, check the resistance of the resistors R6 and R7 with a multimeter and change value in the code
  float volts = (analogRead(A0)*1.1/1024.0) * (100+20)/20; // Resistors R6 (100k) and R7 (20k)
  /*Serial.print(volts); */
  

  if (loopcounter < 2){
    LoRa.beginPacket();
    LoRa.print("0xA2B2");  //  your MailBox key here 
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
