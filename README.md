# Tiny, low power temperature sensor based on DS18B20.
The main scope of this project was to have dirt cheap, wireless, tiny and portable temperature sensor powered by batteries for at least 4+ months.

### Requirements:
(Hardware)
* ESP8266 (ESP01) + Low power mod
* 4.7k resistor 
* 2x1.5 AAA/AA batteries
* Battery holder
* Working MQTT Server 
* Graphana (optional)

(Software)
* Temperature values will be sent to an MQTT broker
* Store the data into a database
* Plot nice graphs :)

### Let's build it!
1. **Deep sleep mod**.There is a way to make ESP-01 work for months using something called deep sleep mode. When in deep sleep, ESP8266 disables almost all of its functions and reboots after specified period of time. There is one catch: ESP-01 is capable to enter deep sleep, but unable to restart and resume operation. XPD_DCDC MCU pin in not connected to RESET pin. To fix it, you would have to solder thin wire between XPD_DCDC and RESET pin. [There is a good article explaining in details how do to this](https://quadmeup.com/esp8266-esp-01-low-power-mode-run-it-for-months/).
I also have removed the red power led from the ESP01 board what saved 10mA more.

2. **Wiring** see ![alt text](https://github.com/ialex87/Portable-temperature-sensor/blob/master/extras/wiring.png)
3. Upload the sketch


### Restults
![alt text](https://github.com/ialex87/Portable-temperature-sensor/blob/master/extras/graphana_screenshot.png)
![alt text](https://github.com/ialex87/Portable-temperature-sensor/blob/master/extras/IMG1.jpg)
![alt text](https://github.com/ialex87/Portable-temperature-sensor/blob/master/extras/IMG2.jpg)
