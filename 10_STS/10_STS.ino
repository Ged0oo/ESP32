#include <BluetoothSerial.h>
#include <LiquidCrystal.h>

BluetoothSerial SerialBT;
LiquidCrystal lcd(22, 23, 21, 19, 18, 5);

void setup() 
{
  Serial.begin(9600);
  SerialBT.begin("ESP32");
  lcd.begin(16, 2);

  while (!SerialBT.available()) 
  {
    delay(10);
  }
}

void loop() 
{
  if (SerialBT.available()) 
  {
    String receivedData = SerialBT.readStringUntil('\n'); // Read data until a newline character is received
    receivedData.trim(); // Remove leading and trailing whitespace

    if (receivedData.length() > 0) 
    {
      Serial.print("Received: ");
      Serial.println(receivedData);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(receivedData);
    }
  }
}
