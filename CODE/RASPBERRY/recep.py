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

bus.write_byte(address,0xFF)

while True:
	#Receives the data from the User
    #value=bus.read_byte(address)
    value=bus.read_block_data(address,4)
    print("VELOCIDADE: %02f" % value)
    time.sleep(.1)



#End of the Script
