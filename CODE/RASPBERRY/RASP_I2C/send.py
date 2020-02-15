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
SPEED = []

for i in range(1,2001)
    SPEED(i) = 1000*math*sin(2*math.pi*1*(i/2001));


# loop to send message
exit = False
t = 0;
while not exit:
    #r = input('SETPOIT: ')
    #print(r)
    RPM = 1000*math.sin(2*math.pi*1*t);
    if RPM<0
        RPM = 0

    t = t + 1;
    time.sleep(1)
    #bytesToSend = ConvertStringToBytes(r)
    #bus.write_i2c_block_data(address, i2c_cmd, bytesToSend)
    bus.write_byte(address,RPM)
    #if r=='q':
        #exit=True
    if t==20
        exit=True

#End of the Script
