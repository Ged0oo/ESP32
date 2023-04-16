#include "BluetoothSerial.h"
#include <HardwareSerial.h>

String device_name = "ESP-NAGY";
char recData;
BluetoothSerial SerialBT;


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void setup() 
{
  Serial.begin(9600 , SERIAL_8N1 , 16, 17);
  delay(100);
  Serial.printf("\n\nThe device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.begin(device_name);
}


void loop() 
{
  recData = SerialBT.read();    
  if (SerialBT.available()) 
  {
      Serial.println(recData);
  }
}
