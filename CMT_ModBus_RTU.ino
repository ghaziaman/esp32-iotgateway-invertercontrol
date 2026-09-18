

byte mod_string[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//byte myArray[50];

void Modbus_RTU_Polling(byte RTU_ID, byte RTU_FC, unsigned short RTU_address, unsigned short RTU_NumsRegs, unsigned long MB_BR, int aa){

    delay(100);
    RS485.begin(MB_BR, SERIAL_8N1, RXD1, TXD1);
    delay(500);
    RS485.flush();
    delay(100);
    mod_string[0] = RTU_ID;  //modId
    mod_string[1] = RTU_FC;  //modfc
    //mod_string[2] = highByte(RTU_address);
    mod_string[2] = (RTU_address>>8)&0xff;
    mod_string[3] = RTU_address&0xff; //modadd
    mod_string[4] = (RTU_NumsRegs>>8)&0xff; //modNumsReg
    mod_string[5] = (RTU_NumsRegs&0xff);  //modNumsReg
    crc_value = crc.Modbus(mod_string,0,6);
    //RS232.println(crc_value, HEX);
    crcMSB = highByte(crc_value);
    crcLSB = lowByte(crc_value);
    mod_string[6] = crcLSB;
    mod_string[7] = crcMSB;
    RS485.write(mod_string, 8);
    delay(300);

   
    char ch;
    j=0;
    while (RS485.available()) {     // If anything comes in RS485 (pins 0 & 1)
    delay(10);
    ch = RS485.read();   // read it and send it out RS232 (USB)
    delay(10);
    modArray[j] = ch;
    j++;
    if(j>255) j=0;
    }
    RS232.println();
    RS232.println("Modbus Reply");
    delay(100);
    for(int iii=0;iii<j;iii++){
      RS232.print(modArray[iii],HEX);
      RS232.print(" ");
    }
    delay(100);
    RS232.println();
    delay(1000);
    
    if((strlen(RTU_Names_Array[aa])>1)&&(j>1)){
       serverMB_polling(String(RTU_Names_Array[aa]),RTU_ID_Array[aa],RTU_FC_Array[aa],RTU_address_Array[aa], RTU_PageNo_Array[aa]);
          }

}
