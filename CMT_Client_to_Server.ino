String Link_Serv;
void server_LAN_connect(){
  unsigned long startTime = millis();
  unsigned long checkTimer = millis();
  String checksend;
  if (client1.connect(powerNoc, port))
  {
    RS232.println("[Response:]");
    while (client1.connected())
    {
      if (client1.available())
      {
        String line = client1.readStringUntil('\r');
        if(line.substring(0,4)=="SPDT")
        {
        RS232.println(line);
        client1.print("SP768008<PONG>");

        server_day = line.substring(5,7);
        server_month = line.substring(8,10);
        server_year_2digits = line.substring(13,15);
        server_year_4digits = line.substring(11,15);
        server_hours = line.substring(16,18);
        server_mins = line.substring(19,21);
        server_secs = line.substring(22,24);

        serv_conv_day = server_day.toInt();
        serv_conv_month = server_month.toInt();
        serv_conv_year = server_year_4digits.toInt();
        serv_conv_hours = server_hours.toInt();
        serv_conv_mins = server_mins.toInt();
        serv_conv_secs = server_secs.toInt();

        Serial.println(setRTCSIM800());
        delay(1000);
        printRTCSIM800();
        delay(1000);  
        setEsp32time();
        delay(200);
        }

        if(line.substring(14,22)=="OTALink=")
        {
        Link_Serv = line.substring(22,line.indexOf(")"));
        RS232.println("Got OTA link: " + Link_Serv);
        //RS232.println(Link_Serv);
        OTA_update(Link_Serv);
        }
      //status
      if(!client1.connected() || (!ETH.linkUp())){
           LAN_av = false;
           LAN_sv = false;
           RS232.println("\n[Connection Lost (LAN)]");
           client1.stop(); 
      }
      }
    }
    
    client1.stop();
    LAN_av = false;
    LAN_sv = false;
    RS232.println("\n[Disconnected]");
  }
  else
  {
    RS232.println("connection failed!]");
    LAN_av = false;
    LAN_sv = false;
    client1.stop();
  }
  delay(5000);

}


void server_WiFi_connect(){
  unsigned long startTime = millis();
  unsigned long checkTimer = millis();
  String checksend;
  if (client2.connect(powerNoc, port))
  {
    RS232.println("[Response:]");
    while (client2.connected())
    {
      if (client2.available())
      {
        String line = client2.readStringUntil('\r');
        if(line.substring(0,4)=="SPDT")
        {
        RS232.println(line);
        client2.print("SP768008<PONG>");

        server_day = line.substring(5,7);
        server_month = line.substring(8,10);
        server_year_2digits = line.substring(13,15);
        server_year_4digits = line.substring(11,15);
        server_hours = line.substring(16,18);
        server_mins = line.substring(19,21);
        server_secs = line.substring(22,24);

        serv_conv_day = server_day.toInt();
        serv_conv_month = server_month.toInt();
        serv_conv_year = server_year_4digits.toInt();
        serv_conv_hours = server_hours.toInt();
        serv_conv_mins = server_mins.toInt();
        serv_conv_secs = server_secs.toInt();

        RS232.println(setRTCSIM800());
        delay(1000);
        printRTCSIM800();
        delay(1000);  
        setEsp32time();
        delay(200);
        }

        if(line.substring(14,22)=="OTALink=")
        {
        Link_Serv = line.substring(22,line.indexOf(")"));
        RS232.println("Got OTA link: " + Link_Serv);
        //RS232.println(Link_Serv);
        OTA_update(Link_Serv);
        }
        if(!client2.connected()){
           client2.stop();
           LAN_av = false;
           LAN_sv = false;
           RS232.println("\n[Connection Lost (WiFi)]"); 
      }
      }
    }
    
    client2.stop();
    WIFI_av = false;
    WIFI_sv = false;
    RS232.println("\n[Disconnected]");
  }
  else
  {
    RS232.println("connection failed!]");
    WIFI_av = false;
    WIFI_sv = false;
    client2.stop();
  }
  delay(5000);

}





void server_GSM_connect(){
  unsigned long startTime = millis();
  //unsigned long checkTimer = millis();
  //String checksend;
  if (client3.connect(powerNoc, port))
  {   
    RS232.println("[Response:]");
    while (client3.connected())
    {
      if (client3.available())
      {
        String line = client3.readStringUntil('\r');
        if(line.substring(0,4)=="SPDT")
        {
        RS232.println(line);
        client3.print("SP768008<PONG>");

        server_day = line.substring(5,7);
        server_month = line.substring(8,10);
        server_year_2digits = line.substring(13,15);
        server_year_4digits = line.substring(11,15);
        server_hours = line.substring(16,18);
        server_mins = line.substring(19,21);
        server_secs = line.substring(22,24);

        serv_conv_day = server_day.toInt();
        serv_conv_month = server_month.toInt();
        serv_conv_year = server_year_4digits.toInt();
        serv_conv_hours = server_hours.toInt();
        serv_conv_mins = server_mins.toInt();
        serv_conv_secs = server_secs.toInt();

        RS232.println(setRTCSIM800());
        printRTCSIM800();
        setEsp32time();
        delay(1500);
        }
           if(!client3.connected()){
           client3.stop();
           LAN_av = false;
           LAN_sv = false;
           RS232.println("\n[Connection Lost (GPRS)]"); 
      }
      }
    }
    client3.stop();
    GSM_av = false;
    GSM_sv = false;
    RS232.println("\n[Disconnected]");
  }
  else
  {
    RS232.println("connection failed!]");
    GSM_av = false;
    GSM_sv = false;
    client3.stop();
  }
  delay(5000);
      while (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      RS232.println(".");
      delay(2000);
      if(millis()-sim_reinsert>8000){
        sim_reinsert=millis();
        modem.restart();
        }
      }
}
