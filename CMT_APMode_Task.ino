uint8_t sizeOfMB_prev;

const char MAIN_page[] PROGMEM = R"=====(
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>CMT Configuration Page</title>

<script type="text/javascript">


    var counter = 0;

    function moreFields() {
      counter++;
      var newFields = document.getElementById("readroot").cloneNode(true);
      newFields.id = '';
      newFields.style.display = 'block';
      var newField = newFields.childNodes;
      for (var i = 0; i < newField.length; i++) {
        if (newField[i].tagName == "SPAN") {
          newField[i].innerText = "SalTec Device " + counter;
        }
        if (newField[i].tagName == "INPUT" && newField[i].type == "text") {
          newField[i].name = "Saltec_" + counter;
          newField[i].id = "Saltec_" + counter;
        }
      }
      var insertHere = document.getElementById("writeroot");
      insertHere.parentNode.insertBefore(newFields, insertHere);
    }

    window.onload = moreFields;
  </script>


<script type="text/javascript">

    var counter2 = 0;
    
    function moreFields2() {
        counter2++;
        var value = parseInt(document.getElementById('NumMB').value, 10);
        value = isNaN(value) ? 0 : value;
        value++;
        document.getElementById('NumMB').value = value;
        var newFields = document.getElementById('readroot2').cloneNode(true);
        newFields.id = '';
        newFields.style.display = 'block';
        var newField = newFields.childNodes;
        for (var i=0;i<newField.length;i++) {
            
            var theLabel = newField[i].innerText;
            if(theLabel){
            newField[i].innerText = theLabel + counter2;
            }

            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="MB_") {
            newField[i].name = "MB_" + counter2;
            newField[i].id = "MB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="baudMB_") {
            newField[i].name = "baudMB_" + counter2;
            newField[i].id = "baudMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="pnoMB_") {
            newField[i].name = "pnoMB_" + counter2;
            newField[i].id = "pnoMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="typeDevMB_") {
            newField[i].name = "typeDevMB_" + counter2;
            newField[i].id = "typeDevMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="typeMODMB_") {
            newField[i].name = "typeMODMB_" + counter2;
            newField[i].id = "typeMODMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="IdMB_") {
            newField[i].name = "IdMB_" + counter2;
            newField[i].id = "IdMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="fcMB_") {
            newField[i].name = "fcMB_" + counter2;
            newField[i].id = "fcMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="modaddMB_") {
            newField[i].name = "modaddMB_" + counter2;
            newField[i].id = "modaddMB_" + counter2;
        }
            if (newField[i].tagName == "INPUT" && newField[i].type == "text" &&  newField[i].id =="nRMB_") {
            newField[i].name = "nRMB_" + counter2;
            newField[i].id = "nRMB_" + counter2;
        }
            
        }
        var insertHere = document.getElementById('writeroot2');
        insertHere.parentNode.insertBefore(newFields,insertHere);
    }
    
    window.onload = moreFields2;
    
    </script>

</head>

<body>
  <h2>GEC Configuration</h2>
  <h3>CMT</h3>
  <br>
  <h3>WiFi Configuration</h3>

  <form action="/action_page" method="post">
    WiFi-SSID :<br>
    <input type="text" id="SSID" name="SSID" value="" required>
    <br><br>
    WiFi-Password :<br>
    <input type="text" id="Password" name="Password" value="" required>
    <br><br>
    WiFi-Configuration(0/1) :<br>
    <input type="text" id="WificonfigEN" name="WificonfigEN" value="0">
    <br><br>
    WiFi-LocalIP :<br>
    <input type="text" id="WiFiLocalIP" name="WiFiLocalIP" value="">
    <br><br>
    WiFi-Gateway :<br>
    <input type="text" id="WiFiGateway" name="WiFiGateway" value="">
    <br><br>
    WiFi-Subnet :<br>
    <input type="text" id="WiFiSubnet" name="WiFiSubnet" value="">
    <br><br>

    <h3>Ethernet Configuration</h3>
    Ethernet-Configuration(0/1) :<br>
    <input type="text" id="EthernetconfigEN" name="EthernetconfigEN" value="0">
    <br><br>
    Ethernet-LocalIP :<br>
    <input type="text" id="EthernetLocalIP" name="EthernetLocalIP" value="">
    <br><br>
    Ethernet-Gateway :<br>
    <input type="text" id="EthernetGateway" name="EthernetGateway" value="">
    <br><br>
    Ethernet-Subnet :<br>
    <input type="text" id="EthernetSubnet" name="EthernetSubnet" value="">
    <br><br>

    <h3>GPRS Configuration</h3>
    GPRS-Configuration(0/1) :<br>
    <input type="text" id="GPRSconfigEN" name="GPRSconfigEN" value="0">
    <br><br>
    GPRS-APN :<br>
    <input type="text" id="GPRSAPN" name="GPRSAPN" value="">
    <br><br>
    GPRS-Username :<br>
    <input type="text" id="GPRSUsername" name="GPRSUsername" value="">
    <br><br>
    GPRS-Password :<br>
    <input type="text" id="GPRSPassword" name="GPRSPassword" value="">
    <br><br><br>

    <h4>Site ID:</h4>
    <input type="text" id="siteId" name="siteId" value="" required>
    <br>
    <h3>SALTEC_Polling Configuration</h3>
    Baud Rate (UART1) :<br>
    <input type="text" id="BAUD1" name="BAUD1" value="" required>
    <br><br>
    Baud Rate (UART2) :<br>
    <input type="text" id="BAUD2" name="BAUD2" value="">
    <br><br>
    Polling Interval :<br>
    <input type="text" id="Polling_Interval" name="Polling_Interval" value="" required>
    <br><br>


    <div id="readroot" style="display: none">

      <span>SalTec Device :</span><br>
      <input type="text" id="Saltec_0" name="Saltec_0" value="">
      <input type="button" value="x"
        onclick="this.parentNode.parentNode.removeChild(this.parentNode);" /><br /><br />

    </div>

      <span id="writeroot"></span>

      <input type="button" value="Add More Device" onclick="moreFields()" />
      <br><br>

      <h3>MODBUS_Polling Configuration</h3>
      <div id="readroot2" style="display: none">
        <innerText> </innerText>.&nbsp;
            <input type="hidden" id="NumMB" name="NumMB" value="" >
            Name:  
            <input type="text" id="MB_" name="MB_" size="3" value="">  &nbsp;&nbsp;
          
            Baud:  
            <input type="text" id="baudMB_" name="baudMB_" size="3" value="">  &nbsp;&nbsp;
             
            Pg No.:  
            <input type="text" id="pnoMB_" name="pnoMB_" size="1" value="">  &nbsp;&nbsp;
          
            Type of Device:  
            <input type="text" id="typeDevMB_" name="typeDevMB_" size="1" value="">  &nbsp;&nbsp;
          
            Type of MODBUS:  
            <input type="text" id="typeMODMB_" name="typeMODMB_" size="1" value="">  &nbsp;&nbsp;
          
            ID:  
            <input type="text" id="IdMB_" name="IdMB_" size="1" value="">  &nbsp;&nbsp;
          
            FC:  
            <input type="text" id="fcMB_" name="fcMB_" size="1" value="">  &nbsp;&nbsp;
          
            Address:  
            <input type="text" id= "modaddMB_" name="modaddMB_" size="3" value="">  &nbsp;&nbsp;
          
            No.Of Regs:  
            <input type="text" id="nRMB_" name="nRMB_" size="1" value="">   &nbsp;&nbsp;
          
            
        <input type="button" value="x"
        onclick="this.parentNode.parentNode.removeChild(this.parentNode);" /><br /><br />
        
    </div>
    
    
        <span id="writeroot2"></span>
    
        <input type="button" value="Add a MODBUS Device" onclick="moreFields2()"  />
        <br><br>
  <input type="submit" value="Submit">
</form>

</body>

<script type="text/javascript">
   var i=0;
   var x=0;
   //getDATA();
   setTimeout(function() {
      getDATA();
    }, 1000);
    function getDATA() {
      var url = "http:/"+"/192.168.4.1/config";  
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var kkk= JSON.parse(this.responseText);
            document.getElementById("SSID").value =kkk['ssid'];
            document.getElementById("Password").value =kkk['password'];
            document.getElementById("WificonfigEN").value =kkk['WiFiconfigEN'];
            document.getElementById("WiFiLocalIP").value =kkk['Wifi_IP'];
            document.getElementById("WiFiGateway").value =kkk['Wifi_GATEWAY'];
            document.getElementById("WiFiSubnet").value =kkk['Wifi_SUBNET'];
            document.getElementById("EthernetconfigEN").value =kkk['LANconfigEN'];
            document.getElementById("EthernetLocalIP").value =kkk['LAN_IP'];
            document.getElementById("EthernetGateway").value =kkk['LAN_GATEWAY'];
            document.getElementById("EthernetSubnet").value =kkk['LAN_SUBNET'];
            document.getElementById("GPRSconfigEN").value =kkk['GPRSconfigEN'];
            document.getElementById("GPRSAPN").value =kkk['apn_config'];
            document.getElementById("GPRSUsername").value =kkk['username_GPRS'];
            document.getElementById("GPRSPassword").value =kkk['password_GPRS'];
            document.getElementById("siteId").value =kkk['siteId'];
            document.getElementById("BAUD1").value =kkk['baud1'];
            document.getElementById("BAUD2").value =kkk['baud2'];
            document.getElementById("Polling_Interval").value =kkk['polling_interval'];
            if (document.getElementById("Saltec_"+(i+1))){
            document.getElementById("Saltec_"+(i+1)).value =kkk['SalTecDevices'][i];
            i++;
            }
            var nnn = kkk['numModbus'];
            //var nnn = 6;
            //for(var i=0; i<nnn; i++){
               //moreFields2();
              //}
            if (document.getElementById("MB_"+(x+1))){
            document.getElementById("MB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x];
            document.getElementById("baudMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*1)];
            document.getElementById("pnoMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*2)];
            document.getElementById("typeDevMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*3)];
            document.getElementById("typeMODMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*4)];
            document.getElementById("IdMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*5)];
            document.getElementById("fcMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*6)];
            document.getElementById("modaddMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*7)];
            document.getElementById("nRMB_"+(x+1)).value =kkk['MODBUS_DEVICES'][x+(nnn*8)];
            x++;
            }      
        }
      };
      xhttp.open("GET",url, true);
      xhttp.send();
    } 
</script>


</html>
)=====";
 
//SSID and Password of your WiFi router
const char* ap_ssid = "cmt-ap2";
const char* ap_password = "Eng12345678";
 
WebServer server(80); //Server on port 80
void handleConfig() { 
   String json_config; //Read HTML contents

  File file6 = SPIFFS.open("/config.txt", "r");
    if(file6.available()){
      json_config = file6.readStringUntil('\n');
    }
    file6.close();
   //deserializeJson(doc, json_config ); 
 server.send(200, "application/json", json_config); //Send web page
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm() {

 WebPgSiteId = server.arg("siteId");
 ssid_c = server.arg("SSID"); 
 password_c = server.arg("Password"); 
 WiFi_Configuration_Flag = server.arg("WificonfigEN"); 
 WiFi_LocalIP = server.arg("WiFiLocalIP"); 
 WiFi_GatewayIP = server.arg("WiFiGateway"); 
 WiFi_SubnetIP = server.arg("WiFiSubnet");
 Ethernet_Configuration_Flag = server.arg("EthernetconfigEN"); 
 Ethernet_LocalIP = server.arg("EthernetconfigEN"); 
 Ethernet_GatewayIP = server.arg("EthernetconfigEN"); 
 Ethernet_SubnetIP = server.arg("EthernetconfigEN");
 GPRS_Configuration_Flag = server.arg("GPRSconfigEN"); 
 GPRS_APN = server.arg("GPRSAPN"); 
 GPRS_Username = server.arg("GPRSUsername"); 
 GPRS_Password = server.arg("GPRSPassword");
 config_baud1 = server.arg("BAUD1");
 config_baud2 = server.arg("BAUD2");
 config_polling_interval = server.arg("Polling_Interval");
 SalDevice_Web_STR_mem1 = server.arg("Saltec_1");
 SalDevice_Web_STR_mem2 = server.arg("Saltec_2");
 SalDevice_Web_STR_mem3 = server.arg("Saltec_3");
 SalDevice_Web_STR_mem4 = server.arg("Saltec_4");
 SalDevice_Web_STR_mem5 = server.arg("Saltec_5");
 SalDevice_Web_STR_mem6 = server.arg("Saltec_6");
 SalDevice_Web_STR_mem7 = server.arg("Saltec_7");
 SalDevice_Web_STR_mem8 = server.arg("Saltec_8");
 SalDevice_Web_STR_mem9 = server.arg("Saltec_9");
 SalDevice_Web_STR_mem10 = server.arg("Saltec_10");
 SalDevice_Web_STR_mem11 = server.arg("Saltec_11");
 SalDevice_Web_STR_mem12 = server.arg("Saltec_12");
 SalDevice_Web_STR_mem13 = server.arg("Saltec_13");
 SalDevice_Web_STR_mem14 = server.arg("Saltec_14");
 SalDevice_Web_STR_mem15 = server.arg("Saltec_15");

 WebNosMBDevs = server.arg("NumMB").toInt();

RS232.println("Nos of Devices: ");
RS232.println(WebNosMBDevs);


//09/11/2020 - start from here
char namesMB[10];
String Form_MB_name;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(namesMB,"MB_%d",i+1);
  Form_MB_name = server.arg(namesMB);
  sprintf(WebNameMB[i],"%s",Form_MB_name.c_str());
  }

char BaudsMB[10];
String Form_MB_Bauds;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(BaudsMB,"baudMB_%d",i+1);
  Form_MB_Bauds = server.arg(BaudsMB);
  sprintf(WebBaudMB[i],"%s",Form_MB_Bauds.c_str());
  }


char NosPgsMB[10];
String Form_MB_PgNos;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(NosPgsMB,"pnoMB_%d",i+1);
  Form_MB_PgNos = server.arg(NosPgsMB);
  sprintf(WebPgNoMB[i],"%s",Form_MB_PgNos.c_str());
  }

char DevsTypsMB[10];
String Form_MB_DevTyp;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(DevsTypsMB,"typeDevMB_%d",i+1);
  Form_MB_DevTyp = server.arg(DevsTypsMB);
  sprintf(WebTypDevMB[i],"%s",Form_MB_DevTyp.c_str());
  }

char ModTypsMB[10];
String Form_MB_ModTyp;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(ModTypsMB,"typeMODMB_%d",i+1);
  Form_MB_ModTyp = server.arg(ModTypsMB);
  sprintf(WebTypeModMB[i],"%s",Form_MB_ModTyp.c_str());
  }


char SlaveIdMB[10];
String Form_MB_IdMB;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(SlaveIdMB,"IdMB_%d",i+1);
  Form_MB_IdMB = server.arg(SlaveIdMB);
  sprintf(WebIdMB[i],"%s",Form_MB_IdMB.c_str());
  }


char Func_CMB[10];
String Form_MB_FC;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(Func_CMB,"fcMB_%d",i+1);
  Form_MB_FC = server.arg(Func_CMB);
  sprintf(WebFcMB[i],"%s",Form_MB_FC.c_str());
  }


char AddressMB[10];
String Form_MB_Address;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(AddressMB,"modaddMB_%d",i+1);
  Form_MB_Address = server.arg(AddressMB);
  sprintf(WebAddressMB[i],"%s",Form_MB_Address.c_str());
  }


char nosRegsMB[10];
String Form_MB_nosRegs;
for(int i=0; i<WebNosMBDevs; i++){
  sprintf(nosRegsMB,"nRMB_%d",i+1);
  Form_MB_nosRegs = server.arg(nosRegsMB);
  sprintf(WebNRMB[i],"%s",Form_MB_nosRegs.c_str());
  }


 RS232.println("Closing Webpage");
 String s = "<a href='/'> Go Back </a>";
 server.send(200, "text/html", s); //Send web page

 DynamicJsonDocument doc(5120); 
   RS232.println("AP config mode WiFi settings");
   String read_file_to_parse;

  File file3 = SPIFFS.open("/config.txt", "r");
    if(file3.available()){
      read_file_to_parse = file3.readStringUntil('\n');
    }
   deserializeJson(doc, read_file_to_parse);
   //doc.shrinkToFit();
  
   JsonObject for_size_prev = doc["MODBUS_DEVICES"];
   for_size_prev.remove("MODBUS_DEVICES");
    JsonArray ModbusArray = doc.createNestedArray("MODBUS_DEVICES");
    
    for(int m=0; m<(WebNosMBDevs*10); m++){
    ModbusArray.add("");
    }
   
   doc["siteId"] = WebPgSiteId;
   doc["ssid"] = ssid_c;
   doc["password"] = password_c;
   doc["WiFiconfigEN"] = WiFi_Configuration_Flag;
   doc["Wifi_IP"] = WiFi_LocalIP;
   doc["Wifi_GATEWAY"] = WiFi_GatewayIP;
   doc["Wifi_SUBNET"] = WiFi_SubnetIP;
   doc["LANconfigEN"] = Ethernet_Configuration_Flag;
   doc["LAN_IP"] = Ethernet_LocalIP;
   doc["LAN_GATEWAY"] = Ethernet_GatewayIP;
   doc["LAN_SUBNET"] = Ethernet_SubnetIP;
   doc["GPRSconfigEN"] = GPRS_Configuration_Flag;
   doc["apn_config"] = GPRS_APN;
   doc["username_GPRS"] = GPRS_Username;
   doc["password_GPRS"] = GPRS_Password;
   doc["baud1"] = config_baud1;
   doc["baud2"] = config_baud2;
   doc["polling_interval"] = config_polling_interval;
   doc["SalTecDevices"][0] = SalDevice_Web_STR_mem1;
   doc["SalTecDevices"][1] = SalDevice_Web_STR_mem2;
   doc["SalTecDevices"][2] = SalDevice_Web_STR_mem3;
   doc["SalTecDevices"][3] = SalDevice_Web_STR_mem4;
   doc["SalTecDevices"][4] = SalDevice_Web_STR_mem5;
   doc["SalTecDevices"][5] = SalDevice_Web_STR_mem6;
   doc["SalTecDevices"][6] = SalDevice_Web_STR_mem7;
   doc["SalTecDevices"][7] = SalDevice_Web_STR_mem8;
   doc["SalTecDevices"][8] = SalDevice_Web_STR_mem9;
   doc["SalTecDevices"][9] = SalDevice_Web_STR_mem10;
   doc["SalTecDevices"][10] = SalDevice_Web_STR_mem11;
   doc["SalTecDevices"][11] = SalDevice_Web_STR_mem12;
   doc["SalTecDevices"][12] = SalDevice_Web_STR_mem12;
   doc["SalTecDevices"][13] = SalDevice_Web_STR_mem14;
   doc["SalTecDevices"][14] = SalDevice_Web_STR_mem15;
   doc["numModbus"] = WebNosMBDevs;
   
  for(int i=0; i<WebNosMBDevs; i++){
    //RS232.println(WebNameMB[i]);
      doc["MODBUS_DEVICES"][i] = WebNameMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+WebNosMBDevs] = WebBaudMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*2)] = WebPgNoMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*3)] = WebTypDevMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*4)] = WebTypeModMB[i];
      }


  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*5)] = WebIdMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*6)] = WebFcMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*7)] = WebAddressMB[i];
      }

  for(int i=0; i<WebNosMBDevs; i++){
      doc["MODBUS_DEVICES"][i+(WebNosMBDevs*8)] = WebNRMB[i];
      }
      
  serializeJson(doc, Web_Configuration);
   
  file_search_flag = SPIFFS.exists("/config.txt");
    if(file_search_flag){
      RS232.println(" File Exists, Updating the config_file according to your Web_Configuration... ");
      File file4 = SPIFFS.open("/config.txt", "w");  
        while(!web_config_flag){
          file4.print(Web_Configuration);
          RS232.println("File Updated");
          file4.close();
          web_config_flag = true;       
        }
      }
      web_config_flag = false;

    File file5 = SPIFFS.open("/config.txt", "r");
    if(!file5){
        RS232.println("Failed to open file for reading");
    }
 
    RS232.println("File Content:");
 
    if(file5.available()){
      web_config_String = file5.readStringUntil('\n');
      RS232.println(web_config_String);
    }


//WiFi Configuration Data from JSON/txt stored file
      numModbus = doc["numModbus"];
      siteId = doc["siteId"];
      ssid = doc["ssid"];
      password = doc["password"];

      WiFiconfigEN = doc["WiFiconfigEN"];
      
      W1 = doc["LAN_IP"][0];
      W2 = doc["LAN_IP"][1];
      W3 = doc["LAN_IP"][2];
      W4 = doc["LAN_IP"][3];

      WG1 = doc["LAN_GATEWAY"][0];
      WG2 = doc["LAN_GATEWAY"][1];
      WG3 = doc["LAN_GATEWAY"][2];
      WG4 = doc["LAN_GATEWAY"][3];

      WSN1 = doc["LAN_SUBNET"][0];
      WSN2 = doc["LAN_SUBNET"][1];
      WSN3 = doc["LAN_SUBNET"][2];
      WSN4 = doc["LAN_SUBNET"][3];


//LAN Configurable Data from JSON/txt stored file
      
      LANconfigEN = doc["LANconfigEN"];
      
      L1 = doc["LAN_IP"][0];
      L2 = doc["LAN_IP"][1];
      L3 = doc["LAN_IP"][2];
      L4 = doc["LAN_IP"][3];

      LG1 = doc["LAN_GATEWAY"][0];
      LG2 = doc["LAN_GATEWAY"][1];
      LG3 = doc["LAN_GATEWAY"][2];
      LG4 = doc["LAN_GATEWAY"][3];

      LSN1 = doc["LAN_SUBNET"][0];
      LSN2 = doc["LAN_SUBNET"][1];
      LSN3 = doc["LAN_SUBNET"][2];
      LSN4 = doc["LAN_SUBNET"][3];

//GPRS Configuration Data from JSON/txt stored file
      
      GPRSconfigEN = doc["GPRSconfigEN"];
      apn_config = doc["apn_config"];
      gprs_user_config = doc["username_GPRS"];
      gprs_pass_config = doc["password_GPRS"];


//SalTec Devices Configuration Data from JSON/txt stored file


      baud1 = doc["baud1"];
      baud2 = doc["baud2"];
      polling_interval = doc["polling_interval"];

      //Sal_Array_mem1 = doc["SalTecDevices"][0];
      for(int iii=0;iii<16;iii++){
        const char * ttt=doc["SalTecDevices"][iii];
        strncpy(Sal_Dev_STR[iii],ttt,10);
        Sal_Dev_STR[iii][14]='\0';
        if(strlen(Sal_Dev_STR[iii])<=13)
          strncat(Sal_Dev_STR[iii],"\r",1);
      }

      for(int i=0; i<WebNosMBDevs; i++){
        const char * tt=doc["MODBUS_DEVICES"][i];
        strncpy(RTU_Names_Array[i],tt,5);
        RTU_Names_Array[i][4]='\0';
      }
      for(int i=0; i<WebNosMBDevs; i++){
      MB_BaudRates[i] = doc["MODBUS_DEVICES"][i+WebNosMBDevs];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_PageNo_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*2)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_Port_Array[i]  = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*3)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_ModType_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*4)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_ID_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*5)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_FC_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*6)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_address_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*7)];
      }
      for(int i=0; i<WebNosMBDevs; i++){
      RTU_NumsRegs_Array[i] = doc["MODBUS_DEVICES"][i+(WebNosMBDevs*8)];
      }
      RS232.println("Restarting Device");
      delay(1000);
      ESP.restart();
      //file5.close();
}


void taskAPMode(void *pvParameters)  // This is a task.
{  
  (void) pvParameters;
  for(;;){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress myIP = WiFi.softAPIP();
  RS232.print("AP IP address: ");
  RS232.println(myIP);
  server.on("/", handleRoot);      //This is display page
  server.on("/config", handleConfig);
  server.on("/action_page", handleForm);  
  server.begin();                  //Start server
  RS232.println("HTTP server started"); 
  RS232.println();
  for(int i=0; i<=180; i++){
    wifi_maintain = false;
  server.handleClient();
  if(WiFi.softAPgetStationNum() != 0){
    i=0;
      sta_conn_to_AP_Flag = true;
      delay(100);
      }
  delay(500);
  }
wifi_maintain = true;
  
while(1){
server.handleClient();
  }
}
}
