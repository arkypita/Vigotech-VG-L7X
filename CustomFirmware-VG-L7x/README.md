# Welcome to the VG-L7X Custom Firmware!
This is Firmware is designed to use the VG-L7X laser engraver with any GRBL compatilbe software.

# Firmware not tested until now!

![vgl7x](https://user-images.githubusercontent.com/8782035/96716014-c2481400-13a4-11eb-9c7f-2a90dcbe5fc6.jpg)

Vigotech made some design choices that make this machine usable ONLY with their VigoWorks software. This means that if you buy this machine you will not be able to use it with other programs that use the GRBL standard (like [LaserGRBL](https://lasergrbl.com), LightBurn, T2Laser, etc).

[GRBL is a standard open-source firmware](https://github.com/gnea/grbl/) for CNC and Engravers, that use a protocol that is well documented and supported by most PC software for engraving. Vigotech decided to use GBRL internally on his control board, but to communicate with the outside through a proprietary protocol, making all classic programs unusable.


# Firmware Features
- USB Serial connection
- Wifi Telnet support for LaserGRBL*

*Note: USB connection has priority over the Wifi connection. As soon there is a Serail USB connection the Wifi Server is not started.


# Flash Firmware
Check out this:
- [ESP32 Firmware](https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Firmware)

# Index

- [Hardware Hack](https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Hardware)
- [ESP32 Firmware](https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Firmware)
- [Vigo Protocol](https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Protocol)
