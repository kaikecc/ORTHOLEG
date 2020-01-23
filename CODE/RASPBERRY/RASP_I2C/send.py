#RPi Pinouts

#I2C Pins
#GPIO2 -> SDA
#GPIO3 -> SCL

#Import the Library Requreid
import smbus
import time

# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
#Slave Address 1
address = 0x18
i2c_cmd = 0x01

def ConvertStringToBytes(src):
    converted = []
    for b in src:
        converted.append(ord(b))
    return converted

# loop to send message
exit = False
while not exit:
    r = input('SETPOIT: ')
    print(r)

    bytesToSend = ConvertStringToBytes(r)
    bus.write_i2c_block_data(address, i2c_cmd, bytesToSend)
    
    if r=='q':
        exit=True

#End of the Script
