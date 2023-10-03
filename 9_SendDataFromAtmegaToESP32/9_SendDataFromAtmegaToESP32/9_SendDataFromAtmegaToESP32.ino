void setup() {
  Serial.begin(9600);     // Initialize the Serial interface with baud rate of 9600
}

// the loop function runs over and over again forever
void loop() {  
  if(Serial.available()>0)    //Checks is there any data in buffer 
  {
    Serial.print("We got:");
    Serial.print('\n');
    Serial.print(char(Serial.read()));  //Read serial data byte and send back to serial monitor
  }
  else
  {
    Serial.println("Hello World..."); //Print Hello word every one second
    delay(1000);                      // Wait for a second
  }
}
