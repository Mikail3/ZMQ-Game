#Pyhton server made for Bulls&Cows
#imports 
import random
import zmq
import time
import string

 #Setting up the filters and the topics -> 2 commands over Benternet
joinfilter = "BullsCows>join?>".encode('ascii') 
jointopic = "BullsCows>join!>"

gamefilter = "BullsCows>game?>".encode('ascii') 
gametopic = "BullsCows>game!>"

# pub and sub for network initialisation
context = zmq.Context()
publisher = context.socket(zmq.PUSH)
subscriber = context.socket(zmq.SUB)


subscriber.setsockopt(zmq.SUBSCRIBE , joinfilter )
subscriber.setsockopt(zmq.SUBSCRIBE , gamefilter )



publisher.connect("tcp://benternet.pxl-ea-ict.be:24041")
subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042")



print("""
                      }   {         ___               
                      (o o)        (o o)              
               /-------\\ /          \\ /-------\\    
              / | BULL |O            O| COW  | \\     
             *  |-,--- |              |------|  *     
                ^      ^              ^      ^        
Welcome to Bulls&Cows!
The game where you have to guess a 4 digit number!
for every right digit you get a Cow
for every right digit at wrongs place you get a Bull
Enjoy!
""")

message = subscriber.recv()
time.sleep(2)
message = jointopic+ "Game is ready"
publisher.send_string(message)
time.sleep(1)
subscriber.setsockopt(zmq.UNSUBSCRIBE , joinfilter )

while(1):
    x = str(random.randint(9995, 9999))
    y = 0
    Cont = "Y"
    guesses = 0
    def reset():
        x = str(random.randint(9995,9999))
        guesses = 0
        return x, guesses


    def CowsAndBulls():
        cows = 0
        bulls = 0
        for i in range(0, 4):
            if x[i] == y[i]:
                cows += 1
            else:
                bulls += 1
        return cows, bulls


    message = gametopic+ "Make a guess first "
    message = publisher.send_string(message)


    while Cont == "Y":
        #y = input('Make a guess: ')
        #input change to a recieve
        
        message = subscriber.recv()
        y = message.decode('utf8').split('>')[2]
        print(y)
        
        if y == "quit":
            Cont = "N"
        guesses += 1
        cows = CowsAndBulls()[0]
        bulls = CowsAndBulls()[1]
        if cows == 4:
            
            
            #print("You have guessed correctly! It took u " + str(guesses) + " guesses.")
            message = gametopic+ "You have guessed good! " + str(guesses) + "guesses." + "Play Again? Y|N " 
            message = publisher.send_string(message)
            
            
            #Cont = input("Play agian? Y|N")
            #message = gametopic + "Play again? Y|N "
            #message = publisher.send_string(message)
            message = subscriber.recv()
            Cont = message.decode('utf8').split('>')[2]
            
            
            if Cont == "Y":
                x = reset()[0]
                guesses = reset()[1]
                message = gametopic+ "Make a guess first "
                message = publisher.send_string(message)
                
        else:
            #print(str(cows) + " Cows, " + str(bulls) + " Bulls")
            message = gametopic+ str(cows) + " Cows, " + str(bulls) + " Bulls" + ", make a new guess."
            message = publisher.send_string(message)
            
            

