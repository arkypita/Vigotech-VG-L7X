# Welcome to the VG-L7X Custom Firmware!

![vgl7x](https://user-images.githubusercontent.com/8782035/96716014-c2481400-13a4-11eb-9c7f-2a90dcbe5fc6.jpg)

Vigotech made some design choices that make this machine usable ONLY with their VigoWorks software. This means that if you buy this machine you will not be able to use it with other programs that use the GRBL standard (like [LaserGRBL](https://lasergrbl.com), LightBurn, T2Laser, etc).

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
- Jumper cable

To bring the ESP32 on the VG-L7X is boot mode is a bit tricky. To do so you have to bridge the GPIO0 Pin to GND. So first plug in the power adapter and the USB cable and connect it with you computer. Now hold on end of your jumper cable on the GPIO0 pin and the other end on GND (you can also hold it simply to the metal of the SD Card slot). 

##### Be carefull that you only hold it on the GPIO0 pin to avoid any short circuit.
Then while holding the jumper cable you have to press and hold the power key on the controll board. The red light should light up. At this point you can remove the bridge from GPIO0 but keep holding the power key the whole flashing process. Then you can start the upload in Arduino IDE. After flash you can release the power button and enjoy a grbl laser.

Have Fun!
