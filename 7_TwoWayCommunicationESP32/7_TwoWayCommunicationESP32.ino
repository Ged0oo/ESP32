#include <esp_now.h>
#include <WiFi.h>


uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};      //REPLACE WITH THE MAC Address of your receiver.


int send_rnd_val_1;             //Variables to accommodate the data to be sent.
int send_rnd_val_2;
int receive_rnd_val_1;          //Define variables to store incoming readings
int receive_rnd_val_2;
String success;                 //Variable to store if sending data was successful



//Structure example to send data and Must match with ESP32 paired.
typedef struct struct_message 
{
    int rnd_1;
    int rnd_2;
} struct_message;
struct_message send_Data;           // Create a struct_message to send data.
struct_message receive_Data;        // Create a struct_message to receive data.



//Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0)
  {
    success = "Delivery Success :)";
  }
  else
  {
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}



//Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
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
  WiFi.mode(WIFI_STA);        //Set device as a Wi-Fi Statiob
  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //Once ESPNow is successfully Init, we will register for Send CB to Get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_peer_info_t peerInfo;             //Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv); //Register for a callback function that will be called when data is received
}

void loop() 
{
  //Set values to send
  send_rnd_val_1 = random(0, 255);
  send_rnd_val_2 = random(0, 255);
  send_Data.rnd_1 = send_rnd_val_1;
  send_Data.rnd_2 = send_rnd_val_2;
  
  
  Serial.println();
  Serial.print(">>>>> ");
  Serial.println("Send data");

  //Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
   
  if (result == ESP_OK) 
  {
    Serial.println("Sent with success");
  }
  else 
  {
    Serial.println("Error sending the data");
  }
  delay(5000);
}
