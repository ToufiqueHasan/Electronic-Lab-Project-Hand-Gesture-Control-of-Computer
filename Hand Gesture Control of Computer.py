import serial                                      # add Serial library for serial communication
import pyautogui                                   # add pyautogui library for programmatically controlling the mouse and keyboard.

Arduino_Serial = serial.Serial('com3',9600)       # Initialize serial and Create Serial port object called Arduino_Serial
 
while 1:
    incoming_data = str (Arduino_Serial.readline()) # read the serial data and print it as line
    print (incoming_data)                           # print the incoming Serial data
     

    if 'next' in incoming_data:                    # if incoming data is 'next'
        pyautogui.hotkey('ctrl', 'pgdn')           # perform "ctrl+pgdn" operation which moves to the next tab
        
    if 'previous' in incoming_data:                # if incoming data is 'previous'
        pyautogui.hotkey('ctrl', 'pgup')           # perform "ctrl+pgup" operation which moves to the previous tab

    if 'down' in incoming_data:                    # if incoming data is 'down'
        #pyautogui.press('down')                   # performs "down arrow" operation which scrolls down the page
        pyautogui.scroll(-100) 
         
    if 'up' in incoming_data:                      # if incoming data is 'up'
        #pyautogui.press('up')                      # performs "up arrow" operation which scrolls up the page
        pyautogui.scroll(100)

            #Update v 2.0
    if 'zoomIn' in incoming_data:                  # if incoming data is 'change'
        pyautogui.hotkey('ctrl','+')
	
    if 'zoomOut' in incoming_data:                 # if incoming data is 'change'
        pyautogui.hotkey('ctrl','-')
	        
	    #update v 2.1 
    if 'play/pause' in incoming_data:               # if incoming data is 'change'
        pyautogui.typewrite(['space'], 0.2)
	
        
    incoming_data = "";                            # clears the data
