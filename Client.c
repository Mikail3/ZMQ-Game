#include <stdio.h>
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

    //connect
    int rd = zmq_connect(publisher, "tcp://benternet.pxl-ea-ict.be:24041");
    int rc = zmq_connect( subscriber, "tcp://benternet.pxl-ea-ict.be:24042" );
    sleep (3);


    const char *filter = (argc > 1)? argv [1]: "example>task!>Mikail";
    const char *filter2 = (argc > 1)? argv [1]: "example>answer!>Mikail";


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
                rd = zmq_send(publisher, "example>task?>Mikail Cinar>", 29, 0); printf("message send\n");
                assert (rd == 29);
                break;
            case 1:

                rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter2, strlen (filter2));
                //send and receive
                rd = zmq_send(publisher, "example>answer?>Mikail Cinar >CORONA-FREE-CHANNEL>4cb9aedf2d6c0a521be6af4d6d097eb78f868c83>*HATSJU*>", 101, 0);
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


/*

#include <stdio.h>
#include <zmq.h>
#include <string.h>



void * context; //Global context, because you only need one !

int main( int argc, char * argv[] )
{
    printf("Hello World!\n");
    context = zmq_ctx_new();

    const char* stringTopic = "";
    void * pusher = zmq_socket( context, ZMQ_PUSH );
    void * sub = zmq_socket( context, ZMQ_SUB );
   /// char s [] = "example>Answer!>Mikail Cinar>" ;

    zmq_connect( pusher, "tcp://benternet.pxl-ea-ict.be:24041" );/// "tcp://localhost:24058"
    zmq_connect( sub, "tcp://benternet.pxl-ea-ict.be:24042");

    zmq_send( pusher, "example>task?>Mikail Cinar", 20, 0 );
    zmq_setsockopt(sub , ZMQ_SUBSCRIBE, "" , 0);

    //ALL MAGIC HAPPENS HERE
    printf("Magic!\n");
    char buffer [50];
    zmq_recv(sub, buffer , 20 , 0);
    printf("Received: %s\n" , buffer);

    zmq_close( pusher );
    zmq_close( sub );
    zmq_ctx_shutdown( context );
    zmq_ctx_term( context );
    ///printf("KTNXBYE!\n");
    return 0;
}
*/
