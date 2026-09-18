
#ifdef ETH_CLK_MODE
#undef ETH_CLK_MODE
#endif
#define ETH_CLK_MODE    ETH_CLOCK_GPIO17_OUT

// Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_POWER_PIN   -1

// Type of the Ethernet PHY (LAN8720 or TLK110)
#define ETH_TYPE        ETH_PHY_LAN8720

// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_ADDR        0

// Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_MDC_PIN     14

// Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_MDIO_PIN    12

static bool eth_connected = false;


void WiFiEvent(WiFiEvent_t event) {
//String strlanip;
      
      IPAddress Lan_config_ip(L1, L2, L3, L4);
      IPAddress Lan_config_gateway(LG1, LG2, LG3, LG4);
      IPAddress Lan_config_subnet(LSN1, LSN2, LSN3, LSN4);
      IPAddress Lan_config_dns1;
      IPAddress Lan_config_dns2;
      
  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      RS232.println("ETH Started");
      //set eth hostname here
      ETH.setHostname("esp32-ethernet");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      RS232.println("ETH Connected");
      if(LANconfigEN==1){
      RS232.println("LAN will continue with your given configuration");
      ETH.config(Lan_config_ip, Lan_config_gateway, Lan_config_subnet);
      delay(2500);
      }
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      RS232.print("ETH MAC: ");
      RS232.print(ETH.macAddress());
      RS232.print(", IPv4: ");
      RS232.print(ETH.localIP());
      if (ETH.fullDuplex()) {
        RS232.print(", FULL_DUPLEX");
      }
      RS232.print(", ");
      RS232.print(ETH.linkSpeed());
      RS232.println("Mbps");
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      RS232.println("ETH Disconnected");
      eth_connected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      RS232.println("ETH Stopped");
      eth_connected = false;
      break;
      default:
      break;
  }
}
void taskLANconnect(void *pvParameters)  // This is a task.
{
  (void) pvParameters;  
   for(;;){

  WiFi.onEvent(WiFiEvent);
  delay(500);
  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
  delay(1000);
  unsigned long eth_millis = millis();
  while(!eth_connected){
    delay(100);
      if((millis()-eth_millis)>5000)
      {
        break;
      }
    }
    eth_millis = millis();
    if(eth_connected){
      RS232.println("ETHERNET CONNECTED");
      LAN_av = true;
      }
      while(LAN_av){
      if (client1.connect(powerNoc, port))
      {
      RS232.println("[LAN attempt to server successful]");
      LAN_sv = true;
      }
      else
      {
      RS232.println("[LAN attempt to server failed! :(]");
      LAN_sv = false;
      client1.stop();
      }
      if(LAN_av && LAN_sv)
      {
        break;
      }
    }
    while(LAN_av && LAN_sv){
    server_LAN_connect();
    }
    }
}
