#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


int main ( int argc, char * argv [] )

{

    ///Hello world 4 ZMQ
    void *context = zmq_ctx_new ();
    void *sender = zmq_socket (context, ZMQ_PUSH); ///If u want to send some , send here
    void *receiver = zmq_socket (context, ZMQ_SUB); ///Benternet pulls , u SUB  ,important voor receive


    int rs = zmq_connect (sender,"tcp://benternet.pxl-ea-ict.be:24041"); ///"tcp://benternet.pxl-ea-ict.be:24041");
    int rr = zmq_connect (receiver, "tcp://benternet.pxl-ea-ict.be:24042");///"tcp://benternet.pxl-ea-ict.be:24042"); ///important voor receive
    ///int rc = zmq_setsockopt(receiver , ZMQ_SUBSCRIBE , "BC!>Joined!" , 21); ///important , op wat je wilt ontvangen, decides what u receive , BENTERNET SENDS
    ///int rc = zmq_setsockopt(receiver , ZMQ_SUBSCRIBE , "example>answer!>Mikail>" , 21);

     const char *berichtJoin = (argc > 1)? argv [1]: "BC>join?>"; ///bericht
     const char *filterJoin = (argc > 1)? argv [1]: "BC>join!>"; ///filter

       assert (rs == 0);
       printf("Client started\n");

       sleep(1); ///Bcz send and receive too quick
      /// rs = zmq_send (sender , "example>task?>Mikail>" ,  21 , 0);
       char buf [256];
       int guess [256];
       char textJoin [20];
       char textgame [20];
       char filterPlayer[50];
       char name [20];

       printf("Enter your name: ");
       scanf("%s", name);

           strcpy(textJoin, berichtJoin);
           strcat(textJoin, name);
           strcat(textJoin, guess);
           strcat(textJoin, ">");

        do
       {

           rs = zmq_send(sender, textJoin, strlen(textJoin), 0);

           buf[rs] = '\0';
           printf("Your input: %d\n\n" ,guess);
            buf[rs] = '\0';
           scanf("%d", guess);
            buf[rs] = '\0';
           rs = zmq_send (sender , guess ,  256 , 0);
            buf[rs] = '\0';

            rr = zmq_setsockopt (sender, ZMQ_SUBSCRIBE, filterJoin, strlen (filterJoin));
                rr = zmq_recv (sender, buf, 256, 0);
       } while (1); {




               rr = zmq_recv (receiver, buf ,256 , 0 ); ///receiving message option 1
               buf[rr] = '\0'; ///String stop
               printf("Received: %s" , buf);

   //            zmq_msg_t msg; ///receiving message option 2
   //            int rr = zmq_msg_init (&msg);
   //            assert (rr == 0);
   //            rr = zmq_msg_recv (&msg, receiver, 0); ///important voor receive
   //            zmq_msg_close (&msg);
       }


           zmq_close(receiver);
           zmq_ctx_destroy(context);
           return 0;
   }
