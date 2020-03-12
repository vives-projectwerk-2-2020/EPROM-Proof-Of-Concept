## Example code for I2C  
(Source: https://os.mbed.com/forum/mbed/topic/3856/?page=1#comment-56893)

```
#include "mbed.h"
 
I2C i2c(D14, D15);       // sda, scl
/* With the used shield and µC we need to select teh folowinng pins */
Serial pc(USBTX, USBRX); // tx, rx
 
const int addr = 0x50 << 1;; 
/* We are Using the SOT23 package of the 24AA64 EEPROM and thus we can't select the I2C address so we need to get is from the data sheet. Address in binary: 1010000 */

int main() 
{
    char regaddr[1];
    char readdata[8]; // room for length and 7 databytes
    char writedata[9]; // room for reg address, length and 7 databytes
    while (1) 
    {
        // read the data
        regaddr[0] = 0xE0;
        i2c.write(addr, regaddr, 1, true);  // select the register, no I2C Stop
        i2c.read(addr, readdata, 8);        // read the length byte and the 7 databytes
        
        wait (1);
 
        // print the data to the screen
        pc.printf("Register 0x%x = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",
                  regaddr[0],
                  readdata[1], readdata[2], readdata[3], readdata[4],
                  readdata[5], readdata[6], readdata[7] );
        wait(1);
 
        // copy the data, starting with register address
        writedata[0] = regaddr[0];  // register address
        writedata[1] = regaddr[1];  // register address part 2
        writedata[2] = 0x00; // byte 1
        writedata[3] = 0xAA;
        writedata[4] = 0xAA;
        writedata[5] = 0xAA;
        writedata[6] = 0xAA;
        writedata[7] = 0xAA;
        writedata[8] = 0xAA;
        writedata[9] = 0xBB;// byte 7
 
        // write the data
        i2c.write(addr, writedata, 9); // select the register, 
                                       // write the length, write 7 databytes      
        wait(1);
 
    }
}
```

### Pinout

| FROM | TO | Description|
| :---- | :---- | :----- |
| SDA-EEPROM | SDA-µC | The Data-line of the I2C bus |
| SCL-EEPROM | SCL-µC | The Clok-line of the I2C bus |
| Vdd | Vcc | A 3v3 power suply |
| GND | Ground | Common Ground |