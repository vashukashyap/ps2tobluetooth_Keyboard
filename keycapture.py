import os
import pickle
import serial
import pyautogui as pyky
import tkinter as tk
import threading
from pynput import keyboard


COMPORT = "COM6"

keys = [
        "q", "w" , "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'",
        "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
        "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "backspace",
        "esc", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12",
        "tab", "capslock", "shiftleft", "shiftright", "ctrlleft", "ctrlright", "win", "altleft", "altright","numlock","space",
        "insert","home", "pageup", "delete", "end", "pagedown",
        "up", "down", "left", "right",
        "enter"
        ]

keymapFile = "./keymaps/keymap.dat"

mappedKeys = {}

def keyMapper():
    mappingKeys = {}
    com = serial.Serial(COMPORT, 9600)
    for i in keys:
        print("Press key for",i)
        print("Mapped to =>", end ="")
        keyData = com.readline()
        if keyData:
            decodeData = keyData.decode('utf-8')
            print(decodeData)
            mappingKeys[decodeData[0:-2]] = i
    com.close()
    return mappingKeys

def writeKeymap():
    File = open(keymapFile, 'wb')
    keymapDict = keyMapper()
    pickle.dump(keymapDict, File)
    File.close()

def listenToKeyboard():
    com = serial.Serial(COMPORT, 9600)
    while True:
        keyData = com.readline()
        if keyData:
            decodeData = keyData.decode('utf-8')[0:-2]
            if(decodeData in mappedKeys.keys()):
                pyky.press(mappedKeys[decodeData])
            else:
                print("key is not mapped")

if __name__ == "__main__":
    try:
        com = serial.Serial(COMPORT, 9600)
        print("Connecting to:", com.portstr)
        com.close()
        if os.path.exists(keymapFile):
            print("Keymap Exist")
            File = open(keymapFile, 'rb')
            mappedKeys = pickle.load(File)
            print(mappedKeys)
            print("Keymapped Loaded")
            listenToKeyboard()

        else:
            print("Unable to load Keymap")
            print("Write keymapp")
            writeKeymap()
            print("Mapping is Done...")
            print("Turning on Listner")

    except Exception as e:
        print(e)
