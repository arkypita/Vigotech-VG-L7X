If you want to read/write ESP32 chip firmware i.e. to dump the original firmware, flashing a new firmware or restore the original one, there are some little stuff you need to know.

First of all you should know that is not possible to program the chip directly via the USB port without a little board modification-hack. This is because the board use a CH330 usb-serial converter that has too few pins to support the extra RTS and DTR pins that most ESP32 modules use to switch the ESP32 into programming mode.

Fortunately, it is easy to force programming mode by temporarily shorting IO0 ([PIN 23](https://user-images.githubusercontent.com/8782035/96240138-d523a880-0fa0-11eb-990f-f3877be84a6a.png)) to ground then resetting the ESP32. To obtain this result, simply solder a small wire between ESP32 IO0 pin and any GND pin. (see picture)

