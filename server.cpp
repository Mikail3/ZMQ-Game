#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <zmq.h>
#include <unistd.h>
#include <sstream>
#include <string>

using namespace std;

void SplitNummer(int number, int array[], int size)
{
    for (; number != 0; number /= 10)
        array[--size] = number%10;
}
int main()
{
    void *context = zmq_ctx_new ();
    void *sender = zmq_socket (context, ZMQ_PUSH); ///If u want to send some , send here
    void *receiver = zmq_socket (context, ZMQ_SUB); ///Benternet pulls , u SUB  ,important voor receive

    int rs = zmq_connect (sender,"tcp://localhost:24041"); ///"tcp://benternet.pxl-ea-ict.be:24041");
    int rr = zmq_connect (receiver, "tcp://localhost:24042");///"tcp://benternet.pxl-ea-ict.be:24042"); ///important voor receive
    int rc = zmq_setsockopt(receiver , ZMQ_SUBSCRIBE , "BC?>" , 4);  ///important , op wat je wilt ontvangen, decides what u receive , BENTERNET SENDS

    assert (rs == 0);
    printf("Bart saves us\n");
    sleep(1); ///Bcz send and receive too quick

    rs = zmq_send (sender , "BullsCows Started" ,  17 , 0);
    srand(time(NULL));
    rs = zmq_send (sender , "---Welcome to BULLS & COWS!---" ,  30 , 0);

    int Guesses[256]; /// guesses
    int size = 0;
    char buf[256];

    /// randomizer
    const short nummer = 4; ///determining nummer voor grootte van gewenste input
    std :: string result = "";

    for (int i = 0; i < nummer; i++) ///loop randomizer
    {

           result.push_back(rand()%10 + '0'); ///zorgt dat je strings aan elkaar concatineert , voeg er iets toe aan achter.

    }

    while(1)
    {
        /// input a number to guess
        ///Concatenate
        std::stringstream id;
        id << "BC!>input a " << nummer << "-digit number : ";
        std:: string s = id.str();
        rs = zmq_send (sender , s.c_str(),  s.size() , 0);
        sleep(1);

        std::string gs= "1111";
        rr = zmq_recv (receiver, buf ,256 , 0 ); ///receiving message option 1
        /// wenselijk heb ik de volgende string ontvangen BC?>1111>  --> ik heb nodig 1111
        gs = buf;
        buf[rr] = '\0'; ///String stop
        printf("Received: %s" , buf);
        
        //String splitting
        std :: string strGuess = buf; // numbers in buff
        std :: size_t posPart1 = strGuess.find ( ">");
        std :: string Part1= strGuess.substr(0, posPart1);
        std :: string Part1After = strGuess.substr ( posPart1 + 1);


        std :: size_t posPart2 = Part1After.find(">");
        std :: string Part2= Part1After.substr(0, posPart2);
        std :: string Part2After = Part1After.substr(posPart2 +1);

        std:: stringstream np; ///number part
        np << '\n' << Part2 << '\n' ;
        std:: string p = np.str();
        rs = zmq_send (sender , p.c_str() , p.size () , 0);

       if (!cin)/// (Guesses[size] < 1000 || Guesses[size] > 9999) check if input is int
        {
            cin.clear();
            cin.ignore(256,  '\n');

            std::stringstream fd;
            fd << "BC!>!!! " << nummer << "-Digits bruh pls !!!\n";
            std:: string f = fd.str();
            rs = zmq_send (sender , f.c_str(),  f.size() , 0);
            continue;
        }
        else
        {
        int bulls = 0;
        int cows = 0;

        std :: string Part2Copy = Part2 ;
        std :: string resultCopy= result;

        for (int i = 0; i < nummer; i++) ///loop cows
        {
            if (resultCopy[i] == Part2Copy[i])
            {    /// if the same
                cows++;
                resultCopy[i] = -1;
                Part2Copy[i] = -1;
            }
        }

        for (int i = 0; i < nummer; i++) ///loop bulls
        {
            if ( Part2Copy [i] >= 0 )
            {
              for (int j = 0; j < nummer; j++) /// loop eelk nummer
              {

                 if ( Part2Copy[j] >= 0 && resultCopy[j] == Part2Copy[i])
                 {    /// if the same
                    bulls++;
                    resultCopy[j] = -1;
                    Part2Copy[i] = -1;
                    break;
                }
             }
          }

        }
        /// if 4 cows = RIGHT
        if (cows == 4) {
            size++;
            break;
        }
        /// weergeven van de aantallen

        std::stringstream bc; ///bullscows
        bc << "BC!>" << bulls << " bulls\n";
        bc << "BC!>" << cows << " cows\n";
        std:: string b = bc.str();
        rs = zmq_send (sender , b.c_str(),  b.size() , 0);

        size++;
        }
    }

    std::stringstream fi; ///finale

    fi << "BC!>" "---\n";
    fi << "You guessed it right\n";
    fi << "The correct number is " << result << endl;;
    fi<< "These are all the numbers you'd guessed.\n";

    std:: string f = fi.str();
    rs = zmq_send (sender , f.c_str(),  f.size() , 0);

    for (int i = 0; i < size; i++)
    {
        std::stringstream gu;
        gu << "BC!>" << Guesses[i] << endl;
        std:: string g = gu.str();
        rs = zmq_send (sender , g.c_str(),  g.size() , 0);
    }
    rs = zmq_send (sender , "BullsCows Stopped" ,  17 , 0);
    return 0;
}
