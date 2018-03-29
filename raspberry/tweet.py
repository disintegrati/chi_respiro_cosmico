#!/usr/bin/python
from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
import time
#from OSC import OSCClient, OSCMessage
#import RPi.GPIO as GPIO
import serial
arduino = serial.Serial('/dev/ttyUSB0', 9600)
#arduino = serial.Serial(port='/dev/tty.usbmodemfa141', baudrate=9600)

#Variables that contains the user credentials to access Twitter API
access_token = "17821271-bM9Rk5aUumOnJ5w7M2m1QGr0HnQfGSpzFhOizhWcz"
access_token_secret = "AjOvwaN9JEkWJ6oMF3QH8ZoOAHZcpejP2UROdUULbeC4d"
consumer_key = "Jp0cykYKjgmPKMQTAXdeRUdB1"
consumer_secret = "kU7XNYNh4pRbeTwy4g18RbECn6wQZJr0j2xBe4YM6bPFYIMKr2"

#sendAddress = '127.0.0.1', 9002
#sendRate = 0.1 # send a message every two seconds
#client = OSCClient()
#client.connect(sendAddress)

#This is a basic listener that just prints received tweets to stdout.
class StdOutListener(StreamListener):

 #print "lol"
 def on_data(self, data):
     print data

     print
     arduino.write("q")
     #msg = OSCMessage()
     #msg.setAddress('/oscTest')
     #msg.append(data)
     #print "Sending '/oscTest 100' message to SuperCollider"
     #try:
     #    client.send(msg)
     #except:
     #    print "Waiting for SuperCollider to become available..."
     #    pass
     #time.sleep(0.1)
    # arduino.write("a")
     #return True

 def on_error(self, status):
     print status


while True:
    #This handles Twitter authetification and the connection to Twitter Streaming API
    l = StdOutListener()
    auth = OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    stream = Stream(auth, l, timeout=60)
    try:
        stream.filter(track=['migrant'])
        stream.userstream()

    except Exception as e:
        print "Error. Restarting Stream.... Error: "
        print e.__doc__
        print e.message
