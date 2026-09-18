float internalTemp;

#ifdef __cplusplus
  extern "C" {
 #endif
 
  uint8_t temprature_sens_read();
 
#ifdef __cplusplus
}
#endif
 
uint8_t temprature_sens_read();
String esp32Temp(){
  internalTemp = ((temprature_sens_read() - 32) / 1.8);
  char Temp[4];
  sprintf(Temp,"%0.1f",internalTemp);
  return Temp;
}


void wifiReconnect(){
while(wifi_maintain == false){
  delay(100);
  }
IPAddress WiFi_config_ip(W1, W2, W3, W4);
IPAddress WiFi_config_gateway(WG1, WG2, WG3, WG4);
IPAddress WiFi_config_subnet(WSN1, WSN2, WSN3, WSN4);
IPAddress WiFi_config_dns1;
IPAddress WiFi_config_dns2;
  
  RS232.print(" Connecting to ");
  RS232.println(ssid);
  RS232.println(password);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
  delay(500);
  }
    RS232.println(" connected");
    if(WiFiconfigEN==1){
      RS232.println("WiFi will continue with your given configuration");
      WiFi.config(WiFi_config_ip, WiFi_config_gateway, WiFi_config_subnet);
      delay(2500);
    }  
}

void taskWiFiconnect(void *pvParameters)  // This is a task.
{  
  (void) pvParameters;
  for(;;){
  while (WiFi.status() != WL_CONNECTED){
    wifiReconnect();
    }
  if(WiFi.status() == WL_CONNECTED)
  {
    RS232.println("WiFi is Ready");
    WIFI_av = true;
  }
   while(WIFI_av){
      if (client2.connect(powerNoc, port))
      {
      RS232.println("[WIFI attempt to server successful]");
      WIFI_sv = true;
      }
      else
      {
      RS232.println("[WIFI attempt to server failed! :(]");
      WIFI_sv = false;
      client2.stop();
      }
      if(WIFI_av && WIFI_sv)
      {
        break;
      }
    }
    while(!(WIFI_av && WIFI_sv && (!LAN_sv))){
    //WiFi sits here
    }
    while(WIFI_av && WIFI_sv && (!LAN_sv)){
    server_WiFi_connect();
    }
  }
}



void taskPWRLED(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  analogWrite(PWRLED, 255);
  for (;;) // A Task shall never return or exit.
  {
    analogWrite(PWRLED, 150);   // turn the LED on (HIGH is the voltage level)
    delay(150);
    analogWrite(PWRLED, 255);    // turn the LED off by making the voltage LOW
    delay(150);
    analogWrite(PWRLED, 150);   // turn the LED on (HIGH is the voltage level)
    delay(150);
    analogWrite(PWRLED, 255);    // turn the LED off by making the voltage LOW
    delay(1500);
  }
}
