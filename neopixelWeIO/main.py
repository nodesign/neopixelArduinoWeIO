from weioLib.weio import *
import serial

ser = None

def setup():
    global ser
    # list available serial ports in WeIO
    ser = serial.Serial()
    ser.port = "/dev/ttyACM2"
    ser.baud = 9600
    
    try: 
        ser.open()
    except Exception, e:
    
        print "error open serial port: " + str(e)
        exit()
    
    print "wait for arduino init"
    
    attach.event("writeToLed", writeToLed)
    attach.event("writeToAllLeds", writeToAllLeds)
    

def writeToLed(d):
    global ser
    
    n = d[0]
    r = d[1]
    g = d[2]
    b = d[3]
    
    data = "P " + "R" + str(r) + " G" + str(g) + " B" + str(b) + " L" + str(n) + "\n"
    #print data
    if not(ser is None):
        ser.write(data)

def writeToAllLeds(d):
    global ser
      
    r = d[0]
    g = d[1]
    b = d[2]
    
    data = "A " + "R" + str(r) + " G" + str(g) + " B" + str(b)+"\n"
    #print data
    if not(ser is None):
        ser.write(data)