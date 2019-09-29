# Domotics

## What is Domotics

Domotics is a PoC project which aims to automatize the Atelier  
Several services are running on server inside the room to make everything work  
A wifi nammed DOMOTICS_WIFI is provided inside the room for devices  
Many services are running on the RaspberryPi and the Domotics VM on the server

## How to acces Domotics's services

| Service             | Adress to acces it                                                           |
|---------------------|------------------------------------------------------------------------------|
| Documentation       | [raspberrypi_ip_adress:1234](raspberrypi_ip_adress:1234)                     |
| Grafana            | [raspberrypi_ip_adress:3000/Grafana](raspberrypi_ip_adress:3000/Grafana)   |
| OctoPrint Ultimaker | [raspberrypi_ip_adress:1234/profile_1](raspberrypi_ip_adress:1234/profile_1) |
| OctoPrint 1         | [raspberrypi_ip_adress:1234/profile_2](raspberrypi_ip_adress:1234/profile_2) |
| OctoPrint 2         | [raspberrypi_ip_adress:1234/profile_3](raspberrypi_ip_adress:1234/profile_3) |


## How to use Domotics's services

### The API

The API must be installed on a raspberryPi connected to the DOMOTICS wifi  
It will handle calls to the door locker and the power-strip  
The API must be launched at startup so a service must be assigned to it  
A dockerfile was provided to dockerise it if wanted  

### The Documentation

A documentation was written using Sphinx and rst files. To change it:
1. Create a Python virtualenv
1. install the packages in the [`documentation/requirement.txt`](/documentation/source)  and edit rst files in [`documentation/source`](/documentation/source)  
2. Once it's done, run `make html` in the root of the documentation's folder. It will regenerate html files from the rst files  
3. After that, you can launch the script [`documentation/launch_server.sh`](./documentation/launch_server.sh), a python simpleHttp server will host the html files on the post 1234  
A service must be assigned to it to run at startup  


**A version of the documentation is also available on the wiki of the repo**  


### Grafana

The Grafana folder contains the configuration of the printers. It's a save if the profile created to monitor printers.
Visit the Grafana page on the PoC wifi to change the profile  

### NFC folders

[`NFC_door_locker`](./NFC_door_locker) and [`NFC_power_strip`](./NFC_power_strip) folders contain the arduino source code of the ESP32 used for the door and the powerstrip. The enable users to scan their epitech card and be allowed to acces the Atelier. Once scanned, the id of the card is sent to the API on the Raspberry and a response code is received. If the ID is recognized in the database of allowed users, 200 is sent, otherwise it's 400.

To transfer code on an ESP32, you need to install required libraries and set the ESP32 kit on the arduino IDE.

### Prometheus

Prometheus server is used to query data from the printer, which will then be interpreted in Grafana. A service must be created in order to launch one instance of prometheus per printer