# Transform VG-L7x controller to a standard Grbl board
If you need to use VG-L7x engraver with any standard GRBL compatible software you can try with this hack (at your risk).

Here is a picture of a VG-L7x board that highlight connection between USB - CH330 - ESP32 - Atmega328:

![original-wiring](original-wiring.jpg)

If you bypass the ESP32 WiFi chip, connecting directly the Atmega328 with the USB-Serial CH330 converter chip, and removing connection between ESP32 and Atmega328, you should be able to use VG-L7x board as a standard GRBL compatible board.

![hack](grbl-hack.jpg)

You should carefully remove the smd resistor R7, R8, R37, R38 and solder a pair of small wires between the resistor pad, side near CH330, and the resistor pad near Atmega 328. TX to RX, and RX to TX.

**WARNING: this entails the loss of the warranty and the disabling of all WiFi functions. The board will only continue to work via USB.**

# Buid your own fake VG-L7x controller to test the protocol

VG-L7x controller is basically an ESP32 chip wired to Atmega328 tx/rx lines. You can easly build up a firmware test environment by using a [cheap ESP32 proto board](https://s.click.aliexpress.com/e/_AcmKU1) and a common and even more cheap [Arduino UNO/Nano board](https://s.click.aliexpress.com/e/_A4UcUD).

![fakeboard](https://github.com/arkypita/Vigotech-VG-L7X/blob/main/Hardware/fakeboard.jpg)

You can flash the original ESP32 firmware using instruction in this page: [https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Firmware](https://github.com/arkypita/Vigotech-VG-L7X/tree/main/Firmware)

Be care that ESP32 is a 3.3v device (proto board has a 5v to 3.3v converter, but tx/rx lines use 3.3v and are not 5v tollerant) while arduinois usually a 5v device (but some 3.3v version exists too). Wiring between both must take care about this issue!

I suggest this wiring.
- Common GND
- ESP32 Vin to Arduino 5V
- ESP32 GPIO27 to Arduino TXD (via 100ohm resistor)
- ESP32 GPIO33 to Arduino RXD (no resistor needed)

![fakeboardwiring](https://github.com/arkypita/Vigotech-VG-L7X/blob/main/Hardware/fakeboardwiring.png)



