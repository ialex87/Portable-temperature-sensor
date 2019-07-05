#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // starndard lib location
#include "config_test.h" //local config file

WiFiClient espClient;
PubSubClient client(espClient);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18B20(&oneWire);

/****************** SETUP ********************/
void setup(void)
{
  // start serial port
  Serial.begin(115200);

  setup_wifi(); // setup wifi connection
  mqtt_connect(); // connect to mqtt
  
  DS18B20.begin();   // Start up the library

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (DS18B20.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
      
  delay(2000);
}


/******************* LOOP *********************/
void loop(void)
{
  DS18B20.requestTemperatures(); // Send the command to get temperatures
  delay(1000);

  float tempC = DS18B20.getTempCByIndex(0);
  Serial.print("Temp: ");
  Serial.println(String(tempC).c_str());
  client.publish(in_topic,  String(tempC).c_str(), true);
  client.disconnect(); // doing the proper disconnect 
  
  Serial.println("zzz");
  delay(2000);
  ESP.deepSleep(SLEEP_TIME * 1000000); // go to sleep  1,000,000 = 1 second

}
/**********************************************/

void setup_wifi() {
  // Connecting to wifi network
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.hostname(HOSTNAME);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void mqtt_connect() {
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect(HOSTNAME, mqttUser, mqttPassword )) {
      Serial.println("connected");
      } 
    else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(1000);
    }
  }
}
