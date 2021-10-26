#!/usr/bin/env python3
from tabulate import tabulate
from genericpath import exists
import platform
import serial
import serial.tools.list_ports
import os
import os.path
from threading import Thread
import re

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
print("#  FILO CONNESSO ARDUCRAFT Daemon   #")
print("#             v. 0.0.1              #")
print("#                                   #")
print("#####################################")


print("Select Your Device : \n")

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
    print("{}: {}".format(port, desc))

com_port = input("\nEnter COM: ")

serial_port = serial.Serial(port=com_port, baudrate=115200, timeout=.1)

current_os = platform.system()


if(current_os == "Windows"):
    logfile = os.environ.get("APPDATA") + "\.minecraft\logs\latest.log"
if(current_os == "Linux"):
    logfile = ""
if(current_os == "Darwin"):
    logfile = os.path.expanduser(
        '~') + "/Library/Application Support/minecraft/logs/latest.log"

running = 0;

def readLog():
    if(exists(logfile)):
        global running;
        running = 1
        print("\nArducraft Daemon is running...")
        print("\nType \"!help\" to get the lists of the available commands\n")
        while(running):
            with open(logfile, "r") as file:
                for last_message in file:
                    pass

            ParsedMessage =  re.findall("\[*.\]*.[a-zA-Z]+.[a-zA-Z]+", last_message);      
            if(ParsedMessage[2] ==" [CHAT"):
                print(ParsedMessage[4].replace('>', '', 1))

                serial_port.write(last_message.encode())
                serial_port.flush()
    else:
        print("Check that Minecraft is installed correctly!")


def scanner():
    while 1:
        user_input = input("Type a command: ")
        command_prefix = "!"
        if(user_input == command_prefix + "exit"):
            global running;
            running = 0
            serial_port.close()
            print("\nArducraft Daemon stopped!\n")
            quit()
        elif(user_input == command_prefix + "clear"):
            os.system('cls' if os.name == 'nt' else 'clear')

        elif(user_input == command_prefix + "help"):
            print(
                "\n" + tabulate([
                    [command_prefix + 'exit', "kill the daemon"],
                    [command_prefix + 'clear', "clear the console"],
                    [command_prefix + 'help', "show this page"]
                ]) + "\n")


if __name__ == '__main__':
    Thread(target=readLog).start()
    Thread(target=scanner).start()
