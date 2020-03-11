#include "mbed.h"

I2C i2c(D14,D15);// sda, scl
Serial pc(USBTX, USBRX); // tx, rx

const char addr = 0x50 << 1; // define the correct I2C Address 

int main(void){
    char regaddr[1];
    char readdata[8]; // room for length and 7 databytes
    char writedata[10]; // room for reg address, length and 7 databytes
    while (1){
        regaddr[0] = 0x00;
        regaddr[1] = 0x00; 
        // copy the data, starting with register address
        writedata[0] = regaddr[0];  // register address
        writedata[1] = regaddr[1]; // length, should be 7
        writedata[2] = 0x00; // byte 1
        writedata[3] = 0xAA;
        writedata[4] = 0xAA;
        writedata[5] = 0xAA;
        writedata[6] = 0xAA;
        writedata[7] = 0xAA;
        writedata[8] = 0xAA;
        writedata[9] = 0xBB;// byte 7
 
        // write the data
        i2c.write(addr, writedata, 10); // select the register, 
                                       // write the length, write 7 databytes      
        wait_us(1000000);
        i2c.write(addr, regaddr, 2, true);  // select the register, no I2C Stop
        i2c.read(addr, readdata, 8);

        wait_us(1000000);
 
        // print the data to the screen
        pc.printf("WRITE Register 0x%x = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",
                  regaddr[0],
                  writedata[2], writedata[3], writedata[4], writedata[5], writedata[6],
                  writedata[7], writedata[8], writedata[9] );
        pc.printf("READ  Register 0x%x = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",
                  regaddr[0],
                  readdata[0], readdata[1], readdata[2], readdata[3],
                  readdata[4], readdata[5], readdata[6] );
        wait_us(1000000);

    } 
}

//address EEPROM OP shield 1010001 enkel de laatste bit kn veranderen of maw 50