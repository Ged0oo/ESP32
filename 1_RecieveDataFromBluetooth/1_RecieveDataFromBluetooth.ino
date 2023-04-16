#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


char recData;
BluetoothSerial SerialBT;


void setup() 
{
  Serial.begin(9600);
  Serial.println("Bluetooth Started! Ready to pair...");
  SerialBT.begin();
}


void loop() 
{
  recData = SerialBT.read();    
  if (SerialBT.available()) 
  {
      Serial.write(recData);
  }
  delay(10);
}
