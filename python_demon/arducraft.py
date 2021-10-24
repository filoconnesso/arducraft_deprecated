
import serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {}".format(port, desc))

com = input("Enter COM: ")

micro = serial.Serial(port=com, baudrate=115200, timeout=.1)

print("Demon is running...")

while(1) :
    with open("latest.log", "r") as file:
        first_line = file.readline()
        for last_line in file:
            pass
        micro.write(last_line.encode())
        micro.flush()