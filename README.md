# ps2tobluetooth_Keyboard
You can use your old ps2 port keyboard wirelessly through bluetooth.

## Things required
Arduino nano
Bluetooth module hc05
5v Battery

## Connections
keyboard vcc ->> arduino nano - 5v  
keyboard ground ->> arduino nano - Gnd  
keyboard data wire ->> arduino nano - A3  
keyboard clock wire ->> arduino nano - A4  

(if you dont know which is color wire is data or clock, google it or an easy way open your keyboard and check it PCB.)

## How to use
1. Flash the  " wireless_keyboard.ino " in your arduino nano.
2. Connect to your bluetooth module hc05 and pair with it.
3. Check the serial transmission port of your buletooth.
4. If the port is COM6 then you don't need do any change in script.
5. If the port is not COM6 the open the script and change the COMPORT value in line no. 10 of script.
6. Run the " keycapture.py " script file on your system ( windows or linux ).
7. Make sure you have installed all the required library.
8. Press button on the keyboard and map the keys.
9. you can change the key for making in " keys list ".
10. after mapping all key script will stop and save mapping in dat file.
11. run again the script it will find the mapping and connect with the arduino nano through blutooth.  
    😊you are ready to go enjoy.
