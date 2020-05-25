# ZMQ Game Bulls&Cows


#Gameplay rules



This project utilizes ZMQ to share data between Python and C.

Game/Server is built using -> Python running on a Rasperry PI
Client is built using  -> C

2 Commands that are being used;

* BullsCows>join?>message> & BullsCows>join!>message>

* BullsCows>game?>message & BullsCows>game!>message>

 -> [ Messages to the server are being sent with an " ? " ]
 
 -> [ Replies from the server are with an " ! " ]
