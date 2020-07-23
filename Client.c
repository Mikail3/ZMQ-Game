#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


int main ( int argc, char * argv [] )

{

    ///Hello world 4 ZMQ
    void *context = zmq_ctx_new ();
    void *sender = zmq_socket (context, ZMQ_PUSH); ///If u want to send some , send here
    void *receiver = zmq_socket (context, ZMQ_SUB); ///Benternet pulls , u SUB  ,important voor receive


    int rs = zmq_connect (sender,"tcp://localhost:24041"); ///"tcp://benternet.pxl-ea-ict.be:24041");
    int rr = zmq_connect (receiver, "tcp://localhost:24042");///"tcp://benternet.pxl-ea-ict.be:24042"); ///important voor receive
    ///int rc = zmq_setsockopt(receiver , ZMQ_SUBSCRIBE , "example>task?>Mikail>" , 21); ///important , op wat je wilt ontvangen, decides what u receive , BENTERNET SENDS
    ///int rc = zmq_setsockopt(receiver , ZMQ_SUBSCRIBE , "example>answer!>Mikail>" , 21);

     ///Making filter


    assert (rs == 0);
    printf("Bart saves us\n");

    sleep(1); ///Bcz send and receive too quick
   /// rs = zmq_send (sender , "example>task?>Mikail>" ,  21 , 0);
    rs = zmq_send (sender , "BC?>1111>" ,  9 , 0);
    printf("Send bytes = %d", rs );
    char buf[256];

    while (1) {


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


/*#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int main( int argc, char * argv[] )
{
        void *context = zmq_ctx_new();
        void *publisher = zmq_socket(context, ZMQ_PUSH);
        void *subscriber = zmq_socket (context, ZMQ_SUB);

         ///Hello world 4 ZMQ
        int rd = zmq_connect(publisher, "tcp://benternet.pxl-ea-ict.be:24041");
        int rc = zmq_connect( subscriber, "tcp://benternet.pxl-ea-ict.be:24042" );
        sleep (3);

        //filter instellen
        const char *filter = (argc > 1)? argv [1]: "example>task!>Mikail";
        const char *filter2 = (argc > 1)? argv [1]: "example>answer!>Mikail";

    //luisteren naar reactie en verzenden
        for(int i=0; i < 2; i++)
        {
                char buf [256];
                buf[0] ='\0';

                zmq_msg_t message;
            rc = zmq_msg_init (&message);
                switch(i)
                {
                        case 0:
                                rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
                                //send and receive
                                rd = zmq_send(publisher, "example>task?>Mikail>", 29, 0); printf("message send\n");
                                assert (rd == 29);
                                break;
                        case 1:

                                rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter2, strlen (filter2));
                                //send and receive
                                rd = zmq_send(publisher, "example>answer?>Mikail>CORONA-FREE-CHANNEL>e370b8e39ff4609ea22243f5fe71f9def3e14e86>*HATSJU*>", 101, 0);
                                assert (rd ==101);
                                printf("answer send\n");
                                break;
                }
                printf("Waiting for reply\n");
                rc = zmq_recv (subscriber, buf, 256, 0); assert(rc != -1);
        int size = zmq_msg_size (&message);
        char *string = malloc (size + 1);
        memcpy (string, zmq_msg_data (&message), size);
        zmq_msg_close (&message);
        string [size] = 0;
        printf("Message received: %s\n\n",buf);
                sleep(1);
        }
        //free (string);
        zmq_close(publisher);
        zmq_close( subscriber );
        zmq_ctx_shutdown( context ); //optional for cleaning lady order (get ready you l*zy f*ck)
        zmq_ctx_term( context ); //cleaning lady goes to work
        printf("KTNXBYE!\n");
        return 0;
}

*/
