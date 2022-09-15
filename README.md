# ESP32 Fan Controller
All you need is:
1. ESP32
2. 434MHz receiver and transmitter
    * This might work with other frequency modules but I haven't tested
3. Other normal hobbyist stuff i.e. breadboard/wires/power supply  

I've included the file for the receiver so you can map your own 434MHz remote. The other folders are the FCC ID of the corresponding remote that it is mapped for.  

* [Receiver](#-Receiver)
* [Remote About](#-Remotes)
* [CHQ7222T434](#-CHQ7222T434)
* [CHQ7225T](#-CHQ7225T)
  
# Receiver
This code is a modified version of [ReceiveDemo_Advanced](https://github.com/sui77/rc-switch/tree/master/examples/ReceiveDemo_Advanced) from [sui77/rc-switch](https://github.com/sui77/rc-switch)  

It's been adapted as a normal *.cpp file if you want to use something other than the Arduino IDE. Other than that it is functionally the same and will still capture broadcasts on the 434MHz frequency.  

## Wiring  
Always check the specifications of the specific modules you are using as well as the pinout for the specific ESP32 dev board you're using. The module I'm using supports 5v but yours may differ. If you power the ESP32 with USB you can pull 5v from Vin. If your module is only 3.3v adjust accordingly.
|ESP32 Pin|434MHz Receiver Pin|
|---------|-------------------|
|Vin|VCC|
|GND|GND|
|GPIO 4|Data Pin|  

## Programming
Write the main.cpp file to your ESP32 using your IDE of choice. Depending on what you are using all you should need to adjust is the baud rate to 115200 and importing the rc-switch dependency. If you're using PlatformIO with VS Code you can do this by adding  
`lib_deps = sui77/rc-switch@^2.6.4`   
to the platformio.ini file in your project folder.  

## Use  
Compile and write main.cpp to your ESP32. Once it's written, monitor the serial output. Point your remote at the module and press one of the buttons, you should now see the data for that button press. The three pieces you will need are:  
1. Binary
2. PulseLength
3. Protocol  

Also take note of how many times that command was sent per button press. Most remotes don't care about the exact number but I've found that getting close to that number helps in the fan responding better for some remotes.  

## What Next?
You have the data you need to build your own ESP32 fan controller at this point. View some of the code for other remotes and use that as a starting point for building your own. Connect your ESP32 to WiFi, have it listen for API calls, broadcast the fan command over 434MHz for the API that is called. Once you have that framework you can easily incorporate it into [Home Assistant](https://www.home-assistant.io/) (I highly recommend checking it out if you aren't aware of it) and automate your ceiling fans.

# Remotes
Unless otherwise noted under the specifc remote the below will apply to all remotes.

## Wiring  
Connect power and ground per the specs for your specific transmitter. Use GPIO 4 for data.

## Programming

### Dependancies
Make sure your project imports the rc-switch dependancy  
`sui77/rc-switch@^2.6.4`   
Other than that it uses `WiFi.h` and `WebServer.h` which both should be handled automatically.

### Wifi
Find `Wifi details` in main.cpp and change to your SSID and password before writing to the ESP32.  
`const char *SSID = "WiFi SSID"`  
`const char *PWD = "WiFi Password"`  

## Use  

Send a GET request to `http://"ESP32 IP"/"API"` and the corresponding code will be sent. Transmit distance is going to be limited by your module power, antenna, and interference. If you find that this isn't working try moving closer to your fan and pointing the antenna directly at it.  

# CHQ7222T434
Model numbers:  
* UC7222T434
* RR7222T434  

## API 
There are five API endpoints that are pretty self explanitory:  
* `/off`
* `/low`
* `/med`
* `/high`
* `/reverse`  

## To-Do  
My fan doesn't have a light so I didn't think to capture the light button. If you need it for now you'll need to grab that on your own.

# CHQ7225T
Model numbers:  
* UC7225T
* 7225

## API  
There are fifteen API endpoints:  
* `/on`
* `/off`
* `/fanUp`
* `/fanDown`
* `/timer2h`
* `/timer4h`
* `/timer8h`
* `/timerOff`
* `/pulseLow`
* `/pulseMed`
* `/pulseHigh`
* `/pulseOff`
* `/revUp`
* `/revDown`
* `/light`  

## To-Do  
Not all of the commands have been fully tested. 