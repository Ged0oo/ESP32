#include "BluetoothSerial.h"

String device_name = "ESP-NAGY";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

char recData;
BluetoothSerial SerialBT;


void setup() 
{
  Serial.begin(9600);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.begin(device_name);
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
