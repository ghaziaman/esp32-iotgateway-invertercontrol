
void taskGPRSconnect(void *pvParameters)  // This is a task.
{
  
  (void) pvParameters;
while(1){
  
  if (!modem.isGprsConnected()){
  RS232.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  RS232.print("Modem Info: ");
  RS232.println(modemInfo);

  if(GPRSconfigEN==1){
      RS232.println("GPRS will continue with your given configuration");
      apn = apn_config;
      gprsUser = gprs_user_config;
      gprsPass = gprs_pass_config;
      RS232.println("Your given GPRS Configuration are: ");
      RS232.println(apn);
      RS232.println(gprsUser);
      RS232.println(gprsPass);
  }
  RS232.print(F("Connecting to "));
    RS232.println(apn);
    while (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      RS232.println(".");
      delay(2000);
      if(millis()-sim_reinsert>8000){
        sim_reinsert=millis();
        modem.restart();
        }
    }
  }
  if (modem.isGprsConnected()){
    RS232.println("~~~success~~~");
    GSM_av = true;
  }
   while(GSM_av){
      if (client3.connect(powerNoc, port))
      {
      RS232.println("[GPRS attempt to server successful]");
      GSM_sv = true;
      }
      else
      {
      RS232.println("[GPRS attempt to server failed! :(]");
      GSM_sv = false;
      client3.stop();
      }
      if(GSM_av && GSM_sv)
      {
        break;
      }
    }
    while(!(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv)))){
    //GPRS sits here
    }
    while(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv))){
    server_GSM_connect();
    }
}
}
