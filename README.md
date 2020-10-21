# Welcome to the Vigotech VG-L7X wiki!
This Wiki was created to talk about Vigotech VG-L7X (WiFi) engraver protocol.

![vgl7x](https://user-images.githubusercontent.com/8782035/96716014-c2481400-13a4-11eb-9c7f-2a90dcbe5fc6.jpg)

Vigotech made some design choices that make this machine usable ONLY with their VigoWorks software. This means that if you buy this machine you will not be able to use it with other programs that use the GRBL standard (like [LaserGRBL](https://lasergrbl.com), LightBurn, T2Laser, etc).

[GRBL is a standard open-source firmware](https://github.com/gnea/grbl/) for CNC and Engravers, that use a protocol that is well documented and supported by most PC software for engraving. Vigotech decided to use GBRL internally on his control board, but to communicate with the outside through a proprietary protocol, making all classic programs unusable.

This pictures can help you understand what is the difference between a standard/common GRBL controller board, and Vigo L7X board:

![standard-vs-vigo](https://user-images.githubusercontent.com/8782035/96724377-0db3ef80-13b0-11eb-9911-2358934ce6ef.png)


I am trying to decode and implement some peculiarities of the VigoWork protocol to be able to make [LaserGRBL](https://github.com/arkypita/LaserGRBL) talk to the boards.
Here I want to share all the collected info to ones that want to help.



# Index

- [Hardware Hack](https://github.com/arkypita/Vigotech-VG-L7X/blob/main/Hardware/Convert%20VG-L7x%20to%20standard%20GRBL%20board.md)
- ESP32 Firmware
