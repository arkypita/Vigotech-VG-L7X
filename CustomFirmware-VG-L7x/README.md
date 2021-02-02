# Welcome to the VG-L7X Custom Firmware!

![vgl7x](https://user-images.githubusercontent.com/8782035/96716014-c2481400-13a4-11eb-9c7f-2a90dcbe5fc6.jpg)

Vigotech made some design choices that make this machine usable ONLY with their VigoWorks software. This means that if you buy this machine you will not be able to use it with other programs that use the GRBL standard (like [LaserGRBL](https://lasergrbl.com), LightBurn, T2Laser, etc) by default.

[GRBL is a standard open-source firmware](https://github.com/gnea/grbl/) for CNC and Engravers, that use a protocol that is well documented and supported by most PC software for engraving. Vigotech decided to use GBRL internally on his control board, but to communicate with the outside through a proprietary protocol, making all classic programs unusable.

**This firmware** replaces the one contained in the ESP32 chip, **and enable you to use the VG-L7X laser engraver with any GRBL compatilbe software**, without any hardware hack. 

You can use Arduino IDE to build and flash the CustomFirmware-VG-L7x.ino sketch you can find in this folder.


## Flashing any firmware on your control board may void warranty! You also can brick your board!


# Firmware Features
- USB Serial connection
- Wifi Telnet support for LaserGRBL*

*Note: WIFI connection has priority over the USB connection. As soon there is a Telnet Wifi connection the USB connection is ignored.

# Flash Firmware
##### No soldering is need for this mod!
To flash the firmware you need:
- Arduino IDE
- ESP32 Hardware Library (used Node-MCU32s)
- WifiManager Library 2.03 (https://github.com/tzapu/WiFiManager.git)

To bring the ESP32 on the VG-L7X is boot mode is very easy. So first plug in the power adapter and the USB cable and connect it with you computer. Now hold the right button while you press and hold the power key on the controll board. The red light should light up. At this point you can release the right button but keep holding the power key the whole flashing process. Then you can start the upload in Arduino IDE. After flash you can release the power button and enjoy a grbl laser.

Have Fun!

# Get Connected
To use the telnet conncection via WiFi you have to connect the controll board with your router. For this, the firmware has two options:
##### 1. WPS (Push Button)
If your router support Push Button WPS, this is the easiest way to connect. Just start the WPS sequence on your router, then turn on the Laser, wait a few seconds until is booted completely. Then do a middle button short press to start the WPS. After a few seconds the Laser is connected. The Console in Laser GRABL should also print the IP now!

##### 2. WiFi Manager (HotSpot)
Another simple way to connect is using the HotSpot. For this press the middle button for over 5 seconds and release it. Then the Laser will create a HotSpot called "ESP 32". Connect to this WiFi. Normally a pop up will come up and you can setup WiFi over the user interface. If the pop up will not appear, open your browser and enter the IP address which is printed in LaserGRBL (normally it should be 192.168.4.1). 

After setting a connection reboot the Laser once and LaserGRBL (or any other Serial terminal) will print the IP address.

###### Note: The Laser will always remember the last connected WiFi network. To connect to another one just repeat the discribed process. 