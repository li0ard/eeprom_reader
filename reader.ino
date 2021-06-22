/* 
  *  Support EEPROM list:
  *  24C01, 20C02, 24C04, 24C08, 24C16, 24C64
  * 
  *  This one by li0rd
  *  June, 2021
  *
  * For a single device, connect as follows:
  * EEPROM 1 (A0)  to GND
  * EEPROM 2 (A1)  to GND
  * EEPROM 3 (A2)  to GND
  * EEPROM 4 (GND) to GND
  * EEPROM 5 (SDA) to Arduino Analog Pin 4
  * EEPROM 6 (SCL) to Arduino Analog Pin 5
  * EEPROM 7 (WP)  to GND
  * EEPROM 8 (Vcc) to Vcc (5 Volts)
  */

/* Memory lenght in bytes
24C64 = 4096
24C16 = 2048
24C08 = 1024
24C04 = 512
24C02 = 256
24C01 = 128
                       */

#define memorylenght 2048

#include <Wire.h>

const byte DEVADDR = 0x50;

void setup() { 
    Wire.begin();
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
      int data = Serial.read();
      if(data == 114) {
        Serial.print("memcopy ");
        eeprom_dump(DEVADDR, 0, memorylenght);
        Serial.println();
        delay(20000);
        while (true) {};
      }
    }
    
}

int eeprom_read_buffer(byte deviceaddr, unsigned eeaddr,
                        char * buffer, byte length)
{
    byte devaddr = deviceaddr | ((eeaddr >> 8) & 0x07);
    byte addr    = eeaddr;
    
    Wire.beginTransmission(devaddr);
    Wire.write(int(addr));
    Wire.endTransmission();

    Wire.requestFrom(devaddr, length);
    int i;
    for (i = 0; i < length && Wire.available(); i++) {
        buffer[i] = Wire.read();
    }
    return i;
}

void eeprom_dump(byte devaddr, unsigned addr, unsigned length)
{
    unsigned startaddr = addr & (~0x0f);

    unsigned stopaddr  = (addr + length + 0x0f) & (~0x0f);

    for (unsigned i = startaddr; i < stopaddr; i += 16) {
        char buffer[16];
        char outbuf[6];
        eeprom_read_buffer(devaddr, i, buffer, 16);
        for (int j = 0; j < 16; j++) {
            if (j == 8) {
                Serial.print(" ");
            }
            sprintf(outbuf, "%02x ", byte(buffer[j]));
            Serial.print(outbuf);          
        }
    }
}