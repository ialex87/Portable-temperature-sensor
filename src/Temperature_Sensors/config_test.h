// Wifi Settings

#define wifi_ssid "wifi-ap"
#define wifi_password "wifi password"
#define HOSTNAME "esp01.lan"

// Data wire is connected to ESP01 GPIO2
#define ONE_WIRE_BUS 2
#define SLEEP_TIME 60 // seconds 

// MQTT settins
const char* mqttServer = "mqtt.lan";
const int mqttPort = 1883;
const char* mqttUser = "user";
const char* mqttPassword = "password";
const char* in_topic = "/sensor/topic/temp";
const char* in_topic_vcc = "/sensor/topic/vcc";
