# OSC Communication
# - repeatedly sending an OSC message to SuperCollider

from OSC import OSCClient, OSCMessage
from threading import Timer
import serial
import struct

arduino = serial.Serial('/dev/ttyUSB0', 9600)

sendAddress = '127.0.0.1', 9001
sendRate = 0.01 # send a message every two seconds
client = OSCClient()
client.connect(sendAddress)

def timedSendMessage():
	Timer(sendRate, sendMessage).start()

def sendMessage():
	#value = 0.1
	#values = arduino.readline()
	try:
		value = arduino.readline()
		print value
	#print struct.unpack("<L", value)[0]
	#print isinstance(value, chr)
	#intvalue = ord(value)
		msg = OSCMessage()
		msg.setAddress('/oscTest')
		msg.append(float(value))
	except:
		print "lo saltiamo"
		pass
	#print value
	try:
		client.send(msg)
	except:
		print "Waiting for SuperCollider to become available..."
		pass
	timedSendMessage() # recursive call, keeps the timer going

#sendAddress = '127.0.0.1', 9002
#sendRate = 0.1 # send a message every two seconds
#client = OSCClient()
#client.connect(sendAddress)
timedSendMessage() # init call to start the sensing loop
