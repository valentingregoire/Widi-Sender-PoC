# Widi-Sender-PoC

## Info

This is a proof of concept of sending UDP messages with a ESP8266 (ESP-12-E) module. I am far from an electronics expert, so this was a big challenge for me.

## Circuit

* In order to program the ESP-12-E, you need to connect it to the pc through the Arduino UNO (I failed with the Arduino USB2SERIAL Mini USB and the FTDI232 Mini USB).
* The ESP-12-E has a programming mode and a normal running mode (and maybe more).
* To be able to put the ESP-12-E in programming mode, you need to ground the GPIO0 pin.
* To upload a sketch, you need to put the ESP-12-E in programming mode (ground the GPIO0 pin) and after compiling - at the start of uploading - you need to trigger the reset.
* For testing, put the board in running mode by disconnecting the GPIO0 pin and resetting the ESP-12-E.

### Programming mode

* On The Arduino UNO, connect the Reset pin to Ground
* From the Arduino UNO to the ESP-12-E:
  * Ground to Ground
  * 3.3V to VCC
  * TX to TXD0
  * RX to RXD0
* On the ESP8266:
  * GPIO0 to Ground
  * GPIO15 to Ground
  * RST (reset) to a button with a 10K resistor
  * EN (CH_PD) to 3.3V

When uploading the sketch, if no connection can be found, press the reset pin right after compiling.

### Normal running mode

* Disconnect the GPIO0 pin and reset the board so the board reboots in running mode.
* Keep the TX/RX pins attached to read the ouput in the serial monitor.
* When running standalone, you only need to keep:
  * VCC
  * EN (CH_PD)
  * Ground
  * GPIO15
  * Reset (not sure if necessary, I kept it for ease of testing)
