# Grupp4 - A sound alerted surveillance camera


##Directory tree
> The directory tree for this repo

.  
|-- Documentation  
|    |-- Feather HUZZAH with ESP8266 #All documentation and "non-source code" files  


|        |  
|        +-- Feather HUZZAH Serial Drivers #Mac, Windows, Linux or Android serial drivers for Feather HUZZAH  
|+-- Code		#Contains all source- & test codes for the project  
|    |  
|    +-- Arduino Library		#Libraries for Arduino IDE needed to compile source code   
|    |    |  
|    |    +-- ESP8266Scheduler		#Scheduler for tasks on Arduino IDE for Feather HUZZAH ESP8266  
|    +-- HUZZAH		#Source code for Feather HUZZAH ESP8266  
|        |  
|        +-- Hardware Test Codes #Projects for testing hardware  

##Setting up Feather HUZZAH w/ ESP8266
> Feather HUZZAH w/ ESP8266 is used to read the noise levels in an area and pinpoint loud sounds - which then will control the PTZ camera through HTTP-requests.

###Install serial drivers
There are serial drivers compatible with Mac, Windows, Linux and Android.  
Install serial drivers located in "Documentation->Feather HUZZAH with ESP8266->Feather HUZZAH Serial Drivers" or download from:
https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

###Connecting with serial(for LUA programming)
-Connect Feather HUZZAH through USB-cable to your computer.  
-Use a serial console app like CoolTerm (Mac) or Putty (Windows) or screen (linux).  
-Connect to the serial port using the console app with 9600bps  
-Press the RESET button on the HUZZAH to print out the welcome message on the serial console  

###Connecting & programming with Arduino IDE
Open Arduino IDE Preferences  
Enter this into Additional Boards Manager URLs: http://arduino.esp8266.com/stable/package_esp8266com_index.json  
Press OK  
Go to Tools -> Board -> Board Manager  
Install "esp8266 by ESP8266 Community"  
Restart Arduino IDE  
Select "Adafruit HUZZAH ESP8266" in Tools -> Board  
Select 80MHZ in CPU Frequency  
Select 4M (3M SPIFFS) in Flash Size  
Select 115200 baud rate  
Select Serial port  
Ready to upload code!  
Recommended to try a test code in "Code->HUZZAH->Hardware Test Codes" to verify that everything is working  

###Connecting to camera using Ethernet cable
Connect Ethernet cable to PoE module(*TO DO: skriv ner modell nummer och hämta specs), this supplises the network connection+power  
Connect PoE module to 230V and an Ethernet cable to a router or computer  
Kameran ska kunna acceptera anonymous users(Ska vara satt på kamerans GUI settings)  

Local network options for computer needed to connect to camera:  
IP: 192.168.0.10  
Subnet: 255.255.255.0  
Router: 192.168.0.20  
Using a browser connect to: 192.168.0.20  
Login information:  
User: *********  
Password: *******  
