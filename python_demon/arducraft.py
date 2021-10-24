from genericpath import exists
import platform
import serial
import serial.tools.list_ports
import os
import os.path
import keyboard

print("#####################################")
print("#                                   #")
print("#             ██████████            #")
print("#             █░░░░░░░░█            #")
print("#             █░██░░██░█            #")
print("#             █░░░░░░░░█            #")
print("#             █░░█░░█░░█            #")
print("#             █░░████░░█            #")
print("#             █░░░██░░░█            #")
print("#             ██████████            #")
print("#                                   #")
print("#   FILO CONNESSO ARDUCRAFT DEMON   #")
print("#             v. 0.0.1              #")
print("#                                   #")
print("#####################################")

print("Select Your Device : \n")

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {}".format(port, desc))

com = input("\nEnter COM: ")

micro = serial.Serial(port=com, baudrate=115200, timeout=.1)

curos = platform.system()

if(curos == "Windows") :
    logfile = os.environ.get("APPDATA") + "\.minecraft\logs\latest.log"
if(curos == "Linux") :
    logfile = ""
if(curos == "Mac") :
    logfile = ""

if(exists(logfile)):

    running = True

    print("\nArducraft Demon is running...")
    print("\nPress \"x\" to stop")

    while(running) :
        with open(logfile, "r") as file:
            for last_message in file:
                pass
            micro.write(last_message.encode())
            micro.flush()
        if(keyboard.is_pressed("x")) :
            running = False
            micro.close()
            file.close()
            print("\nArducraft Demon stopped!\n")

else : 

    print("Check that Minecraft is installed correctly!")
