#include <analogWrite.h>
#include <WiFi.h> 
#include <WebServer.h>
#include <WiFiAP.h>
#include<TimeLib.h>
#include "SPIFFS.h"
#include <WifiClient.h>
#include <ArduinoJson.h>
#include <Crc16.h>
#include <ETH.h>

Crc16 crc;

#define RS485 Serial1
#define RS232 Serial2
#define USB Serial

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif


#define RXD1 2
#define TXD1 15

#define RXD2 16
#define TXD2 5

#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>

TinyGsm modem(Serial);

//RTOS Priority Variables

WiFiClient client1;
WiFiClient client2;
TinyGsmClient client3(modem);

const int PWRLED = 13;
const int internet_available_LED = 32;

//~~~~~~~~~~~~~~~~~~~~AP Mode~~~~~~~~~~~~~~~~~~~~~//

String ssid_c; 
String password_c; 
String WiFi_Configuration_Flag; 
String WiFi_LocalIP; 
String WiFi_GatewayIP; 
String WiFi_SubnetIP;
String Ethernet_Configuration_Flag; 
String Ethernet_LocalIP; 
String Ethernet_GatewayIP; 
String Ethernet_SubnetIP;
String GPRS_Configuration_Flag; 
String GPRS_APN; 
String GPRS_Username; 
String GPRS_Password;
bool sta_conn_to_AP_Flag = false;

//~~~~~~~~~~~~~~~~~~~~AP Mode~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~Connectivity Flags~~~~~~~~~~~~~~~~~~~~~//

bool LAN_av = false;
bool WIFI_av = false;
bool GSM_av = false;

bool LAN_sv = false;
bool WIFI_sv = false;
bool GSM_sv = false;

//~~~~~~~~~~~~~~~~~~~~Connectivity Flags~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~LAN Config Variables~~~~~~~~~~~~~~~//

int LANconfigEN;

int L1;
int L2;
int L3;
int L4;

int LG1;
int LG2;
int LG3;
int LG4;

int LSN1;
int LSN2;
int LSN3;
int LSN4;

int LDNS1_1;
int LDNS1_2;
int LDNS1_3;
int LDNS1_4;

int LDNS2_1;
int LDNS2_2;
int LDNS2_3;
int LDNS2_4;

//~~~~~~~~~~~LAN Config Variables~~~~~~~~~~~~~~~//

//~~~~~~~~~~~WiFi Config Variables~~~~~~~~~~~~~~~//

int WiFiconfigEN;

int W1;
int W2;
int W3;
int W4;

int WG1;
int WG2;
int WG3;
int WG4;

int WSN1;
int WSN2;
int WSN3;
int WSN4;

int WDNS1_1;
int WDNS1_2;
int WDNS1_3;
int WDNS1_4;

int WDNS2_1;
int WDNS2_2;
int WDNS2_3;
int WDNS2_4;

//~~~~~~~~~~~WiFi Config Variables~~~~~~~~~~~~~~~//


//~~~~~~~~~~~GPRS Config Varialbles~~~~~~~~~~~~~//


int GPRSconfigEN;

const char* apn  = "Jazzconnect.mobilinkworld.com";
const char* gprsUser = "";
const char* gprsPass = "";

unsigned long sim_reinsert = millis();

const char* apn_config;
const char* gprs_user_config;
const char* gprs_pass_config;


//~~~~~~~~~~~GPRS Config Varialbles~~~~~~~~~~~~~//


//~~~~~~~~~~~Sal_Array Config Varialbles~~~~~~~~~~~~~//


String config_baud1;
String config_baud2;
String config_polling_interval;
String SalDevice_Web_STR_mem1;
String SalDevice_Web_STR_mem2;
String SalDevice_Web_STR_mem3;
String SalDevice_Web_STR_mem4;
String SalDevice_Web_STR_mem5;
String SalDevice_Web_STR_mem6;
String SalDevice_Web_STR_mem7;
String SalDevice_Web_STR_mem8;
String SalDevice_Web_STR_mem9;
String SalDevice_Web_STR_mem10;
String SalDevice_Web_STR_mem11;
String SalDevice_Web_STR_mem12;
String SalDevice_Web_STR_mem13;
String SalDevice_Web_STR_mem14;
String SalDevice_Web_STR_mem15;

//~~~~~~~~~~~Sal_Array Config Varialbles~~~~~~~~~~~~~//

//~~~~~~~~~~~Mod_Array config variables~~~~~~~~~~~~~~//

int WebNosMBDevs;
char WebNameMB[100][6];
char WebBaudMB[100][10];
char WebPgNoMB[100][3];
char WebTypDevMB[100][5];
char WebTypeModMB[100][5];
char WebIdMB[100][5];
char WebFcMB[100][5];
char WebAddressMB[100][5];
char WebNRMB[100][4];

//~~~~~~~~~~~Mod_Array config variables~~~~~~~~~~~~~~//

bool internet_available =false;

String default_config_String;
String web_config_String;
const char* ssid;
const char* password;

char Sal_Dev_STR[16][15];

uint32_t polling_interval;

unsigned long baud1;
unsigned long baud2;

const char powerNoc[] = "67.23.248.114";
const int  port = 30002;

char timedata[25];

String server_day;
String server_month;
String server_year_2digits;
String server_year_4digits;
String server_hours;
String server_mins;
String server_secs;

byte serv_conv_day;
byte serv_conv_month;
int serv_conv_year;
byte serv_conv_hours;
byte serv_conv_mins;
byte serv_conv_secs;

String sim_day;
String sim_mon;
String sim_yr;
String sim_hh;
String sim_mm;
String sim_ss;

uint32_t sim_int_day;
uint32_t sim_int_mon;
uint32_t sim_int_yr;
uint32_t sim_int_hh;
uint32_t sim_int_mm;
uint32_t sim_int_ss;

String u1reply1;
String firstpart1;
String secondpart1;
unsigned long startTime1;


String u1reply2;
String firstpart2;
String secondpart2;
unsigned long startTime2;


String u1reply3;
String firstpart3;
String secondpart3;
unsigned long startTime3;

bool default_config_flag = false;
int numModbus;

String Web_Configuration;
bool web_config_flag = false;

bool file_search_flag = false;

//~~~~~~~~~~~~~~~MODBUS GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~MODBUS GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

const char* siteId = "SP768008";
String WebPgSiteId;

String ModDevName1 = "MKEM";
unsigned long ModDevBaud1 = 19200;
String DevTypMod = "485";
String ModTypDev = "RTU";
int PgNumDev1 = 0;
int IdDev1 = 3;
int FcDev1 = 3;
int ModAddDev1 = 0;
int NumsRegDev1 = 20 ;


const char* modDefaultName;
const char* modDefaultBaud;
const char* DefaultPort;
unsigned long DefaultMB_type;
int modPgNo = 0;
byte modId;
byte modfc;
byte modadd;
byte modNumsReg;

unsigned short crc_value;
byte crcMSB;
byte crcLSB;

byte modArray[256];
int j = 0;

char RTU_Names_Array[100][5];
unsigned long MB_BaudRates[100];
int RTU_PageNo_Array[100];
char RTU_Port_Array[100];
char RTU_ModType_Array[100];

byte RTU_ID_Array[100];
byte RTU_FC_Array[100];
unsigned short RTU_address_Array[100];
unsigned short RTU_NumsRegs_Array[100];

uint8_t sizeOfMB;

//~~~~~~~~~~~~~~~MODBUS GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~MODBUS GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~GEC Inverter GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~GEC Inverter GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

byte Inverter_ID = 2;
byte Inverter_FC = 4;
int Inverter_address = 1;
int Inverter_NumsRegs = 29;
unsigned long Inverter_BaudRate = 9600;

int G = 0;

byte Mtr_ID = 3;
byte Mtr_FC = 4;
int Mtr_address = 0;
int Mtr_NumsRegs = 46;
unsigned long Mtr_BaudRate = 9600;

int M = 0;

//~~~~~~~~~~~~~~~GEC Inverter GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~GEC Inverter GLOBAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool wifi_maintain = false;

typedef struct //Meter data: current, voltage, power  //18 registers
{
   int16_t l1_voltage; //10x
   int16_t l2_voltage; //10x
   int16_t l3_voltage; //10x

   int16_t l1_current; //10x
   int16_t l2_current; //10x
   int16_t l3_current; //10x

   int16_t l1_active_power; //100x for kW
   int16_t l2_active_power; //100x for kW
   int16_t l3_active_power; //100x for kW

   int16_t l1_apparent_power; //100x for kva
   int16_t l2_apparent_power; //100x for kva
   int16_t l3_apparent_power; //100x for kva

   int16_t l1_power_factor; //100x
   int16_t l2_power_factor; //100x
   int16_t l3_power_factor; //100x

   int16_t frequency; //100x

   int16_t total_active_power;   //100x
   int16_t total_apparent_power; //100x
} Meter;

void setup() {

  //RS232.begin(19200);
  //RS485.begin(9600);
  Serial.begin(19200);
  RS232.begin(19200, SERIAL_8N1, RXD2, TXD2);
  pinMode(PWRLED, OUTPUT);
  pinMode(internet_available_LED, OUTPUT);
  digitalWrite(internet_available_LED, HIGH);
  startTime1 = millis();
  startTime3 = millis();
  startTime2 = millis();

  RS232.println("CMT Initializing...");
  RS232.println("New Firmware");
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  delay(1000);
  digitalWrite(23, HIGH);
  delay(5000);
  

StaticJsonDocument<5120> doc;

String Default_Configuration;
String Default_Configuration_write2file;

  Default_Configuration =
   "{\"ssid\":\"ENG-Test-WiFi\",\"password\":\"Eng12345678\",\"siteId\":\"SP768008\",\"LANconfigEN\":0,\"LAN_IP\":[10,0,0,56],\"LAN_GATEWAY\":[10,0,0,1],\
   \"LAN_SUBNET\":[255,0,0,0],\"LAN_DNS1\":[10,0,0,1],\"LAN_DNS2\":[10,0,0,1],\"WiFiconfigEN\":0,\"Wifi_IP\":[10,0,0,57],\
   \"Wifi_GATEWAY\":[10,0,0,1],\"Wifi_SUBNET\":[255,0,0,0],\"Wifi_DNS1\":[0,0,0,0],\"Wifi_DNS2\":[0,0,0,0],\"GPRSconfigEN\":0,\
   \"apn_config\":\"Jazzconnect.mobilinkworld.com\",\"username_GPRS\":\"\",\"password_GPRS\":\"\",\"baud1\":\"9600\",\
   \"baud2\":\"9600\",\"polling_interval\":\"30\",\"SalTecDevices\":[\"SMC100DT\",\"SMDG00DT\",\"S3LC00DT\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\
   \"\",\"\",\"\",\"\",\"\"],\"numModbus\":6}";

if(SPIFFS.begin()){ 
    RS232.println(" SPIFFS Mounted ");  
  }
  else
  {
    RS232.println(" Mount Failed ");
    }  
    //
    
    //bool formatted = SPIFFS.format();  
    
    //SPIFFS.remove("/config.txt");
    
    
    file_search_flag = SPIFFS.exists("/config.txt");
    if(!file_search_flag){
      // File not found 
    
    RS232.println(" file not found, creating a new file of similar name ");
    File file1 = SPIFFS.open("/config.txt", "w"); 
    
    DeserializationError error = deserializeJson(doc, Default_Configuration);
    numModbus = doc["numModbus"];
    JsonArray ModbusArray = doc.createNestedArray("MODBUS_DEVICES");
    
    for(int m=0; m<(numModbus*10); m++){
    ModbusArray.add("");
    }

    JsonArray for_size = doc["MODBUS_DEVICES"];
    sizeOfMB = for_size.size();
    RS232.println("No. of Modbus Devices: ");
    WebNosMBDevs = sizeOfMB/10;
    RS232.println(WebNosMBDevs);
    
//~~~~~~~~~~~~~Modbus JSON UPDATE For Default Config~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~Modbus JSON UPDATE For Default Config~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  doc["MODBUS_DEVICES"][0] = ModDevName1;
  doc["MODBUS_DEVICES"][0+(WebNosMBDevs*1)] = ModDevBaud1;
  doc["MODBUS_DEVICES"][1+(WebNosMBDevs*2)] = PgNumDev1;
  doc["MODBUS_DEVICES"][2+(WebNosMBDevs*3)] = DevTypMod;               //    RS485 or RS232
  doc["MODBUS_DEVICES"][3+(WebNosMBDevs*4)] = ModTypDev;               //    RTU or ASCII
  doc["MODBUS_DEVICES"][4+(WebNosMBDevs*5)] = IdDev1;
  doc["MODBUS_DEVICES"][5+(WebNosMBDevs*6)] = FcDev1;
  doc["MODBUS_DEVICES"][6+(WebNosMBDevs*7)] = ModAddDev1;
  doc["MODBUS_DEVICES"][7+(WebNosMBDevs*8)] = NumsRegDev1;

//~~~~~~~~~~~~~Modbus JSON UPDATE For Default Config~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~Modbus JSON UPDATE For Default Config~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

   serializeJson(doc, Default_Configuration_write2file);  
    while(!default_config_flag){
    file1.print(Default_Configuration_write2file);
    RS232.println("Write/append Succesful");
    file1.close();
    default_config_flag = true;       
    }
  }
   else {
    RS232.println(" File Already Present ");
   }
    File file2 = SPIFFS.open("/config.txt", "r");
 
    if(!file2){
        RS232.println("Failed to open file for reading");
    }
 
    RS232.println("File Content:");
 
    if(file2.available()){
      default_config_String = file2.readStringUntil('\n');
      RS232.println(default_config_String);
      
      DeserializationError error = deserializeJson(doc, default_config_String);
      //doc.shrinkToFit();

    if (error) {
    RS232.print(F("deserializeJson() failed: "));
    RS232.println(error.c_str());
    }

//`````````````ModbusParsing_DefaultDev```````````````//
      
      siteId = doc["siteId"];
      WebNosMBDevs = doc["numModbus"];

//WiFi Configuration Data from JSON/txt stored file

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
      
    }
    
    delay(1000); 
    file2.close();

   xTaskCreatePinnedToCore(
    taskPWRLED
    ,  "taskPWRLED"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  0);

  RS232.println("Starting AP mode");
  delay(200);
  
  xTaskCreatePinnedToCore(
    taskAPMode
    ,  "taskAPMode"   // A name just for humans
    ,  10240  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  delay(500);
  digitalWrite(4, HIGH);
  delay(1000);
  
  
   xTaskCreatePinnedToCore(
    taskLANconnect
    ,  "taskLANconnect"   // A name just for humans
    ,  4096 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);
  
  
   xTaskCreatePinnedToCore(
    taskWiFiconnect
    ,  "taskWiFiconnect"   // A name just for humans
    ,  4096  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);
  


 xTaskCreatePinnedToCore(
    taskGPRSconnect
    ,  "taskGPRSconnect"   // A name just for humans
    ,  4096  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);

  xTaskCreatePinnedToCore(
    taskPolling485
    ,  "taskPolling485"   // A name just for humans
    ,  2048  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);

}


void loop(){
}
