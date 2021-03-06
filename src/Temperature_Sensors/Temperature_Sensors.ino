#include <OneWire.h>
#include <DallasTemperature.h> // DataSheet https://cdn-shop.adafruit.com/datasheets/DS18B20.pdf
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // starndard lib location
#include "config_test.h" //local config file

ADC_MODE(ADC_VCC);


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
  DS18B20.setResolution(12); //Set the resolution

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (DS18B20.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  delay(2000);

  DS18B20.requestTemperatures(); // Send the command to get temperatures
  delay(1000);

  float tempC = DS18B20.getTempCByIndex(0);
  Serial.print("Temp: ");
  Serial.println(String(tempC).c_str());
  client.publish(in_topic,  String(tempC).c_str(), true);
  delay(1000);
  client.publish(in_topic_vcc,  String(vcc_status()).c_str(), true);
  client.disconnect(); // doing the proper disconnect 

  Serial.println(vcc_status());

  sleep();
}


/******************* LOOP *********************/
void loop(void)
{
}
/**********************************************/

void sleep() {
  Serial.println("Going to sleep...");
  delay(2000);
  ESP.deepSleep(SLEEP_TIME * 1000000); // go to sleep  1,000,000 = 1 second
}

void setup_wifi() {
  // Connecting to wifi network
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.hostname(HOSTNAME);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    Serial.println(WIFI_TIMEOUT);
    WIFI_TIMEOUT --;
    if (WIFI_TIMEOUT == 0) {
        Serial.println("Wifi connection timeout");
        sleep();
      }
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

float vcc_status() {
  float vccVolt = ((float)ESP.getVcc())/1024;
  return vccVolt;
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
      Serial.println(client.state());
      delay(1000);
    }
    MQTT_TIMEOUT --;
    if (MQTT_TIMEOUT == 0) {
        Serial.println("MQTT connection timeout");
        sleep();
     }
    }
   }
