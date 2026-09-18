void SGRC_polling(){
  int conn;
  if((client1.connected())&&(LAN_av && LAN_sv)){
    conn = 5;
    }
    if((client2.connected())&&(WIFI_av && WIFI_sv && (!LAN_sv))){
    conn = 6;
    }
    if((client3.connected())&&(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv)))){
    conn = 7;
    }
  String SGRC_String =String(siteId)+String("<SGRC(ID(00,")+String(digitalClockDisplay())+String(")X(")
  +String(esp32Temp())+String(",35.0,")+String(WiFi.RSSI())+String(",7")
  +String(")")+String("H(1,1,1,1,1,1,1,1)L(")+String(conn)+String(",2,2,2,2,2,2,2)A(11111111))>")+String("\r");

  //unsigned long epoch = now();

  if((client1.connected())&&(LAN_av && LAN_sv)){
  client1.print(SGRC_String);             
  RS232.println(SGRC_String);
  }

  else if((client2.connected())&&(WIFI_av && WIFI_sv && (!LAN_sv))){
  client2.print(SGRC_String);             
  RS232.println(SGRC_String);
  }

  else if((client3.connected())&&(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv)))){
  client3.print(SGRC_String);             
  RS232.println(SGRC_String);
  }

  else{
    RS232.println("Data couldn't be sent to Server, Server isn't available for connection");
    }
}
bool send_to_server_flag=false;
void Saltec_polling(String global_polling_id)
{
   //if((millis()-startTime1)>5000){
    RS485.print("\r");
   delay(1000);
   RS485.flush();
   RS485.print(global_polling_id);
   //startTime1 = millis();
      
   unsigned long startlocalTime1;
   startlocalTime1 = millis();
   while((millis()-startlocalTime1)<1500){
                
   while (RS485.available()) {
   u1reply1 = RS485.readStringUntil('\r');
   RS485.flush();
   firstpart1 = u1reply1.substring(0,10);
   secondpart1 = u1reply1.substring(14);
   if(send_to_server_flag==true){
    RS232.println("Send to server should have been started");
    serverST_polling();
   }
   RS232.println("SalTec Polling device reply");
   RS232.println(u1reply1);
   startlocalTime1 = millis();
  }
 }          
}

void taskPolling485(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  unsigned long startTime = millis();

  
  for (;;)
  {
    if((millis()-startTime1)>5000){
      Meter_Polling(Mtr_ID, Mtr_FC, Mtr_address, Mtr_NumsRegs, Mtr_BaudRate);
      //gec polling
      GEC_Polling(Inverter_ID, Inverter_FC, Inverter_address, Inverter_NumsRegs, Inverter_BaudRate);
      //gec calc
      GEC_calculation();
      //gec controlling
      //GEC_Polling(Inverter_ID, 6, 3, Total_active_pwr, Inverter_BaudRate);
      
      if((millis()-startTime)>(polling_interval*1000)){
        send_to_server_flag=true;
        startTime=millis();
      }
      RS485.begin(baud1, SERIAL_8N1, RXD1, TXD1);
      delay(500);
      RS232.flush();
    for(int i=0; i<=15; i++){
     if(strlen(Sal_Dev_STR[i])>1){
        Saltec_polling(String(Sal_Dev_STR[i]));
       }
    }
    //modbus polling
    for(int ii=0;ii<=WebNosMBDevs;ii++){
    if(strlen(RTU_Names_Array[ii])>1){
    Modbus_RTU_Polling(RTU_ID_Array[ii], RTU_FC_Array[ii], RTU_address_Array[ii], RTU_NumsRegs_Array[ii], MB_BaudRates[ii], ii);
      }
    }
    if(send_to_server_flag==true){
        //gec data send to server
        SGRC_polling();
        send_to_server_flag=false;
      }
     startTime1 = millis();
   }
  }
}

void serverST_polling(){
  
  String ST_poll_str;
  String checkSend;

  RS232.println("SalTec Server Polling Started");
  
  ST_poll_str = String(siteId)+String("<")+String(firstpart1 + ",")+String(digitalClockDisplay())+String(secondpart1)+String(">")+String("\r");
  
   if((client1.connected())&&(LAN_av && LAN_sv)){
  client1.print(ST_poll_str);
  /*delay(1000);
    checkSend = client1.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client1.stop();
      }*/
  RS232.println(ST_poll_str);
  }

  else if((client2.connected())&&(WIFI_av && WIFI_sv && (!LAN_sv))){
  client2.print(ST_poll_str);
  /*delay(1000);
    checkSend = client2.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client2.stop();
      }*/     
  RS232.println(ST_poll_str);
  }

  else if((client3.connected())&&(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv)))){
  client3.print(ST_poll_str);
  /*delay(1000);
    checkSend = client3.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client3.stop();
      }*/   
  RS232.println(ST_poll_str);
  }

  else{
    RS232.println("Data couldn't be sent to Server, Server isn't available for connection");
    }
}


void serverMB_polling(String RTU_Name, byte RTU_ID, byte RTU_FC, byte RTU_Address, int RTU_pgNo)
{
ModDevName1 = RTU_Name;
modId = RTU_ID;
modfc = RTU_FC;
modadd = RTU_Address;
modPgNo = RTU_pgNo;
unsigned long epochTime;
epochTime = now();
String diamond_open = "<";
String Bracket_open = "(";
String bind = ")>";
byte sendMod[256];
byte* ptr = sendMod;
//RS232.println(siteId);
String MBsiteId;
MBsiteId = String(siteId);

//RS232.println(MBsiteId);
MBsiteId.getBytes(ptr,MBsiteId.length()+1);
ptr += MBsiteId.length();
//RS232.println(ModDevName1);

diamond_open.getBytes(ptr,1+1);
ptr++;

ModDevName1.getBytes(ptr,ModDevName1.length()+1);
ptr += ModDevName1.length();

Bracket_open.getBytes(ptr,1+1);
ptr++;

//RS232.println(epochTime,HEX);
*ptr  = (epochTime >> 24)&0xFF;
ptr++;
*ptr = (epochTime >> 16)&0xFF;
ptr++;
*ptr = (epochTime >> 8)&0xFF;
ptr++;
*ptr = (epochTime)&0xFF;
ptr++;
//RS232.println(modId,HEX);
*ptr = modId;
ptr++;
//RS232.println(modfc,HEX);
*ptr = modfc;
ptr++;

*ptr =  modPgNo;
ptr++;

//RS232.println(modadd,HEX);
*ptr =(modadd >> 8)&0xFF;
ptr++;

*ptr = modadd;
ptr++;

memcpy(ptr, modArray+2, j-2);
ptr += j;
bind.getBytes(ptr,2+1);
ptr+=2;

//byte *ptr2 = sendMod;
//RS232.println(int(ptr - sendMod));
RS232.println();
  
RS232.println("Modbus Server Polling Started");
String checkSend;

   if((client1.connected())&&(LAN_av && LAN_sv)){
    RS232.println("LAN MODBUS SERVER");
    client1.write((char*)sendMod, (int)(ptr - sendMod));
    /*delay(1000);
    checkSend = client1.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client1.stop();
      }*/  
  RS232.write(sendMod, (int)(ptr - sendMod));
    RS232.println();
  }

  else if((client2.connected())&&(WIFI_av && WIFI_sv && (!LAN_sv))){
  RS232.println("WIFI MODBUS SERVER");
   client2.write((char*)sendMod, (int)(ptr - sendMod));
   /*delay(1000);
    checkSend = client2.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client2.stop();
      }*/
  RS232.write(sendMod, (int)(ptr - sendMod));
    RS232.println();
}

  else if((client3.connected())&&(GSM_av && GSM_sv && ((!LAN_sv)&&(!WIFI_sv)))){
  RS232.println("GPRS MODBUS SERVER");
   client3.write(sendMod, (int)(ptr - sendMod));
   /*delay(1000);
    checkSend = client3.print("$");
    if(checkSend == "0"){
      RS232.println(" ~Connection to the server is lost~ ");
      client3.stop();
      }*/
  RS232.write(sendMod, ptr - sendMod);
    RS232.println();
}

  else{
    RS232.println("Data couldn't be sent to Server, Server isn't available for connection");
  }
}
