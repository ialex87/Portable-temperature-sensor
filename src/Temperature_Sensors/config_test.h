// Wifi Settings

const char* wifi_ssid="SSID";
const char* wifi_password="PASSWORD";
const char* HOSTNAME="ESP_HOSTNAME";

// Data wire is connected to ESP01 GPIO2
const int ONE_WIRE_BUS=2;
const int TEMPERATURE_PRECISION=12;
const int SLEEP_TIME=600; // seconds 
// Wifi connection timeout
int WIFI_TIMEOUT = 10;
int MQTT_TIMEOUT = 3;

// MQTT settins
const char* mqttServer = "";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* in_topic = "/temp";
const char* in_topic_vcc = "/vcc";
