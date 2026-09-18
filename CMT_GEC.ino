
byte GEC_Poll_str[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//byte myArray[50];

void GEC_Polling(byte Inv_ID, byte Inv_FC, int Inv_address, int Inv_NumsRegs, unsigned long Inv_BR){

    for (int x = 0; x < sizeof(modArray) / sizeof(modArray[0]); x++)
    {
    modArray[x] = 0;
    }
    /*RS232.println(RTU_ID);
    RS232.println(RTU_FC);
    RS232.println(RTU_address);
    RS232.println(RTU_NumsRegs);
    RS232.println(MB_BR);
    */
    RS485.begin(Inv_BR, SERIAL_8N1, RXD1, TXD1);
    delay(500);
    RS485.flush();
    GEC_Poll_str[0] = Inv_ID;  //modId
    GEC_Poll_str[1] = Inv_FC;  //modfc
    GEC_Poll_str[2] = highByte(Inv_address); //modadd
    GEC_Poll_str[3] = lowByte(Inv_address); //modadd
    GEC_Poll_str[4] = highByte(Inv_NumsRegs); //modNumsReg
    GEC_Poll_str[5] = lowByte(Inv_NumsRegs);  //modNumsReg
    crc_value = crc.Modbus(GEC_Poll_str,0,6);

    crcMSB = highByte(crc_value);
    crcLSB = lowByte(crc_value);
    
    GEC_Poll_str[6] = crcLSB;
    GEC_Poll_str[7] = crcMSB;
    RS485.write(GEC_Poll_str, 8);
    //RS485.flush();
    delay(500);

   
    char ch;
    G=0;
    while (RS485.available()) {     // If anything comes in RS485 (pins 0 & 1)
    delay(25);
    ch = RS485.read();   // read it and send it out RS232 (USB)
    delay(25);
    modArray[G] = ch;
    G++;
    if(G>255) G=0;
    }
    RS232.println();
    RS232.println("Inverter Reply");
    for(int iii=0;iii<G;iii++){
     // RS232.print(modArray[iii],HEX);
      RS232.print(" ");
    }
    RS232.println();
    delay(1000);
    
}

byte Meter_Poll_str[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//byte myArray[50];

void Meter_Polling(byte Meter_ID, byte Meter_FC, int Meter_address, int Meter_NumsRegs, unsigned long Meter_BR){

    for (int x = 0; x < sizeof(modArray) / sizeof(modArray[0]); x++)
    {
    modArray[x] = 0;
    }
    RS485.begin(Meter_BR, SERIAL_8N1, RXD1, TXD1);
    delay(500);
    RS485.flush();
    Meter_Poll_str[0] = Meter_ID;  //modId
    Meter_Poll_str[1] = Meter_FC;  //modfc
    Meter_Poll_str[2] = highByte(Meter_address); //modadd
    Meter_Poll_str[3] = lowByte(Meter_address); //modadd
    Meter_Poll_str[4] = highByte(Meter_NumsRegs); //modNumsReg
    Meter_Poll_str[5] = lowByte(Meter_NumsRegs);  //modNumsReg
    crc_value = crc.Modbus(Meter_Poll_str,0,6);

    crcMSB = highByte(crc_value);
    crcLSB = lowByte(crc_value);
    
    Meter_Poll_str[6] = crcLSB;
    Meter_Poll_str[7] = crcMSB;
    RS485.write(Meter_Poll_str, 8);
    //RS485.flush();
    delay(500);

   
    char ch;
    M=0;
    while (RS485.available()) {     // If anything comes in RS485 (pins 0 & 1)
    delay(25);
    ch = RS485.read();   // read it and send it out RS232 (USB)
    delay(25);
    modArray[M] = ch;
    M++;
    if(M>255) M=0;
    }
    RS232.println();
    RS232.println("Meter Reply");
    for(int iii=0;iii<M;iii++){
      RS232.print(modArray[iii], HEX);
      RS232.print(" ");
    }
    RS232.println();
    delay(1000);
    
}

int16_t Total_active_pwr;

void GEC_calculation(){

Meter.l1_voltage |= (((int)(modArray[3])) << 8);
Meter.l1_voltage |= (int)(modArray[4]);

Meter.l1_current |= (((int)(modArray[5])) << 8);
Meter.l1_current |= (int)(modArray[6]);

Meter.l1_power_factor |= (((int)(modArray[3])) << 8);
Meter.l1_power_factor |= (int)(modArray[4]);

Meter.l1_apparent_power |= (((int)(modArray[3])) << 8);
Meter.l1_apparent_power |= (int)(modArray[4]);

Meter.l1_active_power |= (((int)(modArray[3])) << 8);
Meter.l1_active_power |= (int)(modArray[4]);

Meter.l2_voltage |= (((int)(modArray[3])) << 8);
Meter.l2_voltage |= (int)(modArray[4]);

Meter.l2_current |= (((int)(modArray[3])) << 8);
Meter.l2_current |= (int)(modArray[4]);

Meter.l2_power_factor |= (((int)(modArray[3])) << 8);
Meter.l2_power_factor |= (int)(modArray[4]);

Meter.l2_apparent_power |= (((int)(modArray[3])) << 8);
Meter.l2_apparent_power |= (int)(modArray[4]);

Meter.l2_active_power |= (((int)(modArray[3])) << 8);
Meter.l2_active_power |= (int)(modArray[4]);

Meter.l3_voltage |= (((int)(modArray[3])) << 8);
Meter.l3_voltage |= (int)(modArray[4]);

Meter.l3_current |= (((int)(modArray[3])) << 8);
Meter.l3_current |= (int)(modArray[4]);

Meter.l3_power_factor |= (((int)(modArray[3])) << 8);
Meter.l3_power_factor |= (int)(modArray[4]);

Meter.l3_apparent_power |= (((int)(modArray[3])) << 8);
Meter.l3_apparent_power |= (int)(modArray[4]);

Meter.l3_active_power |= (((int)(modArray[3])) << 8);
Meter.l3_active_power |= (int)(modArray[4]);

Meter.frequency |= (((int)(modArray[3])) << 8);
Meter.frequency |= (int)(modArray[4]);

Meter.total_apparent_power |= (((int)(modArray[3])) << 8);
Meter.total_apparent_power |= (int)(modArray[4]);

Meter.total_active_power |= (((int)(modArray[3])) << 8);
Meter.total_active_power |= (int)(modArray[4]);
  
  //int meter_pwr;
  int power_int = 0;
  power_int |= (((int)(modArray[56])) << 8);
  power_int |= (int)(modArray[57]);

  
  //Total_active_pwr = ((power_int)*10)/18000;
  RS232.print("Total Active Power from Power Meter: ");
  RS232.println(Total_active_pwr);  
}
