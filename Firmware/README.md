# Flashing ESP32 firmware

If you want to read/write ESP32 chip firmware i.e. to dump the original firmware, flashing a new firmware or restore the original one, there are some little stuff you need to know.

First of all you should know that is not possible to program the chip directly via the USB port without a little board modification-hack. This is because the board use a CH330 usb-serial converter that has too few pins to support the extra RTS and DTR pins that most ESP32 modules use to switch the ESP32 into programming mode.

Fortunately, it is easy to force programming mode by temporarily shorting IO0 ([PIN 23](https://user-images.githubusercontent.com/8782035/96240138-d523a880-0fa0-11eb-990f-f3877be84a6a.png)) to ground then resetting the ESP32. To obtain this result, simply solder a small wire between ESP32 GPIO0 pin and any GND pin (see picture) or hold a jumper cable on the GPIO0 pin and the other end on GND (you can also hold it simply to the metal of the SD Card slot).

![io-to-gnd](https://github.com/arkypita/Vigotech-VG-L7X/blob/main/Firmware/io0-to-gnd.jpg?raw=true)



## Installing esptool

To be able to read/write ESP32 firmware you need a software called [esptool](https://github.com/espressif/esptool).

If you don't have esptool installed on your PC you should follow any guide about "installing esptools on Windows/MAC/Linux" that you can find in google, or follow this instruction:

1. Download and install [Python 2.x or 3.x](https://www.python.org/) from [https://www.python.org/downloads](https://www.python.org/downloads)
2. Download Esptool from [https://github.com/espressif/esptool/releases](https://github.com/espressif/esptool/releases).
3. Extract the contents of esptool compressed file to c:\esptool.
4. Open Command Prompt ( **Start > Run > cmd** ) and navigate to esptool folder cd c:/esptool .

Install the esptool by issuing the commands below.

```
python setup.py install
pip install pyserial
```



## Using esptool to read/erite ESP32 flash memory

Here is the command for read/write ESP32 flash memory:

```
For  4M Flash:
READ:  python esptool.py -b 115200 --port COM3 read_flash 0x00000 0x400000 flash_4M.bin
WRITE: python esptool.py -b 115200 --port COM3 write_flash --flash_freq 40m 0x000000 flash_4M.bin
```

Of course you should use the right COM port number and .bin filename.

**NOTE: push and keep pressed the black Power-ON button during all the read/write operation.**

That is all! You should get something like this for the 4M flash:

```
C:\esptool-2.6>python esptool.py -b 115200 --port COM3 read_flash 0x00000 0x400000 flash_4M.bin
esptool.py v2.6
Serial port COM3
Connecting....
Detecting chip type... ESP32XYZ
Chip is ESP32
Features: WiFi
MAC: 80:7d:3a:33:xx:xx
Uploading stub...
Running stub...
Stub running...
4194304 (100 %)
4194304 (100 %)
Read 4194304 bytes at 0x0 in 402.0 seconds (83.5 kbit/s)...
Hard resetting via RTS pin...
_____....._____.....____
```

To write flash you need to erase it first by

```
esptool.py erase_flash
```



## Restore the original firmware

If you've made a mess you can re-program the original Vigotech firmware. Vigotech does not provide it publicly/officially but you can just read your firmware and save it somewhere before you start making changes.

Anyway here you can find a copy of the original firmware, copied in this way from an L7X board: [VigoEsp32 3.0 Build 20200720.bin](https://github.com/arkypita/Vigotech-VG-L7X/blob/main/Firmware/VigoEsp32%203.0%20Build%2020200720.bin)
