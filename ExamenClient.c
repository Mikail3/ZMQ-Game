#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define MAXINPUT 100

///String parsing
///

char *Parse (int lenght1 , char *StringSplit)
{
        char *string,*StringSplitted;
        string = strdup(StringSplit);

         for (int p=0; p<lenght1; p++)
         {
            StringSplitted = strtok(&string , ">");

         }
         return StringSplitted;
         free (strdup);
}

int main( int argc, char * argv[] )
{
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUSH);
    void *subscriber = zmq_socket (context, ZMQ_SUB);

    ///Here we connect
    int rd = zmq_connect(publisher, "tcp://benternet.pxl-ea-ict.be:24041");
    int rc = zmq_connect( subscriber, "tcp://benternet.pxl-ea-ict.be:24042" );

    sleep (3);

    if (rd != 0 && rc != 0)
    {
        printf("ERROR: ZeroMQ error occurred during zmq_ctx_new(): %s\n", zmq_strerror(errno));
        return EXIT_FAILURE;
    }

    ///Here we filter tru
    const char *joinfilter = (argc > 1)? argv [1]: "BullsCows>join!>";
    const char *gamefilter = (argc > 1)? argv [1]: "BullsCows>game!>";
    const char *initfilter = (argc > 1)? argv [1]: "BullsCows>init!>";


    ///Here we message tru

    const char *jointopic = (argc > 1)? argv [1]: "BullsCows>join?>";
    const char *gametopic = (argc > 1)? argv [1]: "BullsCows>game?>";
    const char *inittopic = (argc > 1)? argv [1]: "BullsCows>init?>";

    /// in case if u want to char more
    char textplay [20];
    char textgame [20];
    char textjoin [20];
    char textagain [20];
    int number ;
    int assigned ;
    char guess [MAXINPUT] = "";
    int length,i;
    char *StringSplitted;
    char buf [256];
    buf[0] ='\0';
    char lengthnum;

        ///join
         zmq_msg_t message;
         strcpy(textjoin, jointopic); ///Bericht samenstellen
         strcat(textjoin, "join"); strcat(textgame, ">");
         rd = zmq_send(publisher, textjoin, strlen(textjoin), 0); printf("joined\n");
         memset(buf,0,256);


        //////BullsCows>join!>game is ready
         rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, joinfilter, strlen (joinfilter));
         rc = zmq_recv (subscriber, buf, 256, 0); assert(rc != -1);
         StringSplitted = Parse(3 ,buf );
         printf("Message received1: %s\n\n",buf);
         memset(buf,0,256);
         rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, gamefilter, strlen (gamefilter));

       do ///loop for the game part

    {
        ///BullsCows>!game!>make a guess first
        rc = zmq_recv (subscriber, buf, 256, 0); assert(rc != -1);
        StringSplitted = Parse(3 ,buf );
        printf("Message received2: %s\n\n",buf);
        memset(buf,0,256);




        char guess [100]; ///Guess made here

        do

        {
//        printf("Pick lenghtnum: %s\n\n",buf);
//        scanf("%s" ,lengthnum);
//        rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, initfilter, strlen (initfilter));
//        rc = zmq_recv (subscriber, buf, 256, 0); assert(rc != -1);
//        StringSplitted = Parse(3 ,buf );







        printf("Your input: %s\n\n",buf);
        scanf("%s",guess);
        assigned = sscanf(guess , "%d" , &number);
        length = strlen (guess);



        if(StringSplitted[0] != '!') ///if u won u skip this part , als het geen ! bevat
        {



                        for (i=0;i<length; i++) ///Checking if input is a number
                        if (!isdigit(guess[i]))
                        {
                            printf ("Entered input is not a number , try again\n");
                            scanf("%s",guess);
                        }

                        if(StringSplitted[0] == 'N')
                        {
                            exit(0);
                        }
           }





        ///Check if input is the right one
        }///while((guess[0] == 'Y') && (StringSplitted[0] != '!')
        while(number< 0 || number > 10000 || strcmp("reset" , guess) ==0 );
        memset(buf,0,256);



        rc = zmq_msg_init (&message); ///makes message
        memset(buf,0,256);
        strcpy(textplay, gametopic); ///Bericht samenstellen
        strcpy(textplay, inittopic);
        strcat(textplay, guess); strcat(textplay, ">");


        //send and receive
        rd = zmq_send(publisher, textplay, strlen(textplay), 0); printf("message send3\n");
        memset(buf,0,256);
        }while(50);



        rc = zmq_recv (subscriber, buf, 256, 0); assert(rc != -1);
        StringSplitted = Parse(3 ,buf );
        printf("Waiting for reply\n");
        memset(buf,0,256);

        sleep(1);



        zmq_msg_close(&message);
        zmq_close(publisher);
        zmq_close( subscriber );
        zmq_ctx_shutdown( context );
        zmq_ctx_term( context );
        printf("KTNXBYE!\n");
        return 0;
    }

