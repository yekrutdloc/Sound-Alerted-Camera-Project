# Grupp4 - A sound alerted surveillance camera


##Directory tree
> The directory tree for this repo

``` ruby
.  
|-- Documentation  
|    +-- Feather HUZZAH w/ ESP8266 #All documentation and "non-source code" files  
|        |  
|        +-- Feather HUZZAH Serial Drivers #Mac, Windows, Linux or Android serial drivers for Feather HUZZAH  
|+-- Code #Contains all source- & test codes for the project  
|    |  
|    +-- Arduino Library #Libraries for Arduino IDE needed to compile source code   
|    |    |  
|    |    +-- ESP8266Scheduler #Scheduler for tasks on Arduino IDE for Feather HUZZAH ESP8266  
|    +-- HUZZAH	 #Source code for Feather HUZZAH ESP8266  
|        |  
|        +-- Hardware Test Codes #Projects for testing hardware  
```

##Setting up Feather HUZZAH w/ ESP8266
> Feather HUZZAH w/ ESP8266 is used to read the noise levels in an area and pinpoint loud sounds - which then will control the PTZ camera through HTTP-requests.

###Install serial drivers
There are serial drivers compatible with Mac, Windows, Linux and Android. Install serial drivers located in "Documentation->Feather HUZZAH with ESP8266->Feather HUZZAH Serial Drivers" or download from:  
https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

###Connecting with serial(for LUA programming)
1. Connect Feather HUZZAH through USB-cable to your computer.  
2. Use a serial console app like CoolTerm (Mac) or Putty (Windows) or screen (linux).  
3. Connect to the serial port using the console app with 9600bps  
4. Press the RESET button on the HUZZAH to print out the welcome message on the serial console  

###Connecting & programming with Arduino IDE
1. Open Arduino IDE Preferences  
2. Enter this into Additional Boards Manager URLs: http://arduino.esp8266.com/stable/package_esp8266com_index.json  
3. Press OK  
4. Go to "Tools->Board->Board Manager"  
5. Install "esp8266 by ESP8266 Community"  
6. Restart Arduino IDE  
7. Select "Adafruit HUZZAH ESP8266" in "Tools->Board"  
8. Select "80MHZ" in "CPU Frequency" 
9. Select "4M (3M SPIFFS)"" in "Flash Size"  
10. Select "115200bps" in "baud rate"  
11. Select correct serial port  
12. Ready to upload code!  
13. Recommended to try a test code in "Code->HUZZAH->Hardware Test Codes" to verify that everything is working  

###Connecting to camera using Ethernet cable
1. Connect Ethernet cable between camera(AXIS PTZ Q6115-E or compatible) and PoE module(PoE port), this supplises the network connection+power  
2. Connect PoE module to 230V and an Ethernet cable between PoE port(non PoE port) to a router or computer ethernet port  
3. Local network options for computer needed to connect to camera:  
    * IP: 192.168.0.10  
    * Subnet: 255.255.255.0  
    * Router: 192.168.0.20  
4. Using a web browser connect to: "192.168.0.20". If there is a popup screen asking for login information, then check camera manual for factory user login information.
5. Camera has to be configured to accept anonymous users(should be able to be configured in cameras browser configurator)  
