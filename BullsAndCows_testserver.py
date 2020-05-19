import zmq
import struct
import time

joinfilter = "BullsCows>join?>".encode('ascii') 
jointopic = "BullsCows>join!>"

gamefilter = "BullsCows>game?>".encode('ascii') 
gametopic = "BullsCows>game!>"


context = zmq.Context()
publisher = context.socket(zmq.PUSH)
subscriber = context.socket(zmq.SUB)

publisher.connect("tcp://benternet.pxl-ea-ict.be:24041")
subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042")

subscriber.setsockopt(zmq.SUBSCRIBE, joinfilter) #subben op join

time.sleep(2)
print("sending reply")
message = gametopic+"9999>" #je gaat jointopic en de playerjoined samevoegen
publisher.send_string(message)


print("waiting for message")
message = subscriber.recv()
print("received message: %s" %message)


