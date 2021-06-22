# Li0ard EEPROM - Simple EEPROM reader on Arduino with Programm for PC

### Support EEPROM list:
`24C01, 20C02, 24C04, 24C08, 24C16, 24C64`

### How connect

```
EEPROM 1 (A0)  to GND
EEPROM 2 (A1)  to GND
EEPROM 3 (A2)  to GND
EEPROM 4 (GND) to GND
EEPROM 5 (SDA) to Arduino Analog Pin 4
EEPROM 6 (SCL) to Arduino Analog Pin 5
EEPROM 7 (WP)  to GND
EEPROM 8 (Vcc) to Vcc (5 Volts)
```

### How use

1. To start, download the firmware (reader.ino) to your Arduino, and connect the EEPROM according to the scheme.

2. Install modules for working with a PC program:
```
Windows: pip install -r requirements.txt
Linux: sudo pip3 install -r requirements.txt
```

3. Run the program, and if you have done correctly, the device name will be displayed in the list.
4. To read the memory, make sure that you have connected the EEPROM according to the schema and click "Read"

### Test's

Programm was test on `Ubuntu 18.04 LTS`

### Contacts

If you have error/answer please DM Me - [*CLICK*](https://vk.com/li0ard)