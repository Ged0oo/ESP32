
#include <esp_now.h>
#include <WiFi.h>

//Define variables to store incoming readings
int receive_rnd_val_1;
int receive_rnd_val_2;



//Structure example to receive data and Must match the sender structure
typedef struct struct_message 
{
    int rnd_1;
    int rnd_2;
} struct_message;
//Create a struct_message to receive data.
struct_message receive_Data; 



//Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  receive_rnd_val_1 = receive_Data.rnd_1;
  receive_rnd_val_2 = receive_Data.rnd_2;
  Serial.println("Receive Data: ");
  Serial.println(receive_rnd_val_1);
  Serial.println(receive_rnd_val_2);
  Serial.println("<<<<<");
}



void setup() 
{
  Serial.begin(115200);
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA); 

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv); 
}



void loop() 
{
  
}
