String setRTCSIM800() {
  sprintf(timedata, "AT+CCLK=\"%s/%02u/%02u,%02u:%02u:%02u+00\"", server_year_2digits, serv_conv_month, serv_conv_day, serv_conv_hours, serv_conv_mins, serv_conv_secs);
  delay(1000);
  return timedata;
}

String printRTCSIM800(){
unsigned long RTCFail_millis = millis();
String SIM_timestamp;
char time_StampSIM[25];
modem.sendAT(GF("+CCLK?"));
delay(1000);
while(!modem.waitResponse(GF("+CCLK: \"")))
{
  modem.sendAT(GF("+CCLK?"));
  RS232.println(".");
  delay(1000);
  if((millis()-RTCFail_millis)>5000)
      {
        break;
      }
  }
  RTCFail_millis = millis();
        SIM_timestamp = RS232.readStringUntil('+');
        sim_yr = SIM_timestamp.substring(0,2);
        sim_mon = SIM_timestamp.substring(3,5);
        sim_day = SIM_timestamp.substring(6,8);
        sim_hh = SIM_timestamp.substring(9,11);
        sim_mm = SIM_timestamp.substring(12,14);
        sim_ss = SIM_timestamp.substring(15,17);
        sprintf(time_StampSIM, "%s/%s/%s,%s:%s:%s", sim_day, sim_mon, server_year_4digits, sim_hh, sim_mm, sim_ss);
        sim_int_day = sim_day.toInt();
        sim_int_mon = sim_mon.toInt();
        sim_int_yr = sim_yr.toInt();
        sim_int_hh = sim_hh.toInt();
        sim_int_mm = sim_mm.toInt();
        sim_int_ss = sim_ss.toInt();
        RS232.println(time_StampSIM);
        return time_StampSIM;
}

void setEsp32time(){
if(!modem.waitResponse(GF("+CCLK: \""))){
setTime(serv_conv_hours, serv_conv_mins, serv_conv_secs, serv_conv_day, serv_conv_month, serv_conv_year);
}
else{
setTime(sim_int_hh, sim_int_mm, sim_int_ss, sim_int_day, sim_int_mon, sim_int_yr);
}
}
String digitalClockDisplay(){
  char stringTimeEsp32[25];
  sprintf(stringTimeEsp32,"%02u/%02u/%04u,%02u:%02u:%02u", day(), month(), year(), hour(), minute(), second());

  return stringTimeEsp32;
}
