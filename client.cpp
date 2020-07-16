#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

void SplitNummer(int number, int array[], int size)
{
    for (; number != 0; number /= 10)
        array[--size] = number%10;
}
int main()
{
    srand(time(NULL));
    printf( "--- BULLS & COWS game ---\n\n");
    int Guesses[100]; /// guesses
    int size = 0;
    /// randomizer
    const short nummer = 4;
    int result = rand()%9000 + 1000;

    int resultArray[nummer];
    int resultArrayCopy[nummer]; ///duplicating array bcz line 66 its put to 0

    SplitNummer(result, resultArray, nummer);	///  split resultaat -> gaat naar array
    /// loop tot de input juist is
    while(1)
    {
        /// input a number to guess
        cout << "input a " << nummer << "-digits number : ";
        cin >> Guesses[size];

        if (Guesses[size] < 1000 || Guesses[size] > 9999)
        {
            cout << "!!! " << nummer << "-Bruh digits !!!\n";
            continue;
        }
        else
        {
        /// bulls and cows
        int bulls = 0;
        int cows = 0;
        /// inputted number as array
        int numberArray[nummer];
        SplitNummer(Guesses[size], numberArray, nummer);
        /// loop find bulls and cows

       memcpy(resultArrayCopy, resultArray, nummer*sizeof(int)); ///Overwriting resultArrayCopy to resultArray
        for (int i = 0; i < nummer; i++)
        {
            if (resultArrayCopy[i] == numberArray[i])
            {    // if the same
                cows++;
                resultArrayCopy[i] = -1;
                numberArray[i] = -1;
            }
        }

        for (int i = 0; i < nummer; i++)
        {
            if ( numberArray[i] >= 0 )
            {
              for (int j = 0; j < nummer; j++) /// loop eelk nummer
              {

                 if ( resultArrayCopy[j] >= 0 && resultArrayCopy[j] == numberArray[i])
                 {    // if the same
                    bulls++;
                    resultArrayCopy[j] = -1;
                    numberArray[i] = -1;
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
        cout << bulls << " bulls\n";
        cout << cows << " cows\n";
        size++;
        }
    }
    /// finale
    cout << "---\n";
    cout << "You guess it right\n";
    cout << "The correct number is " << result << endl;;
    cout << "These all the numbers you'd guessed.\n";
    for (int i = 0; i < size; i++)
        cout << Guesses[i] << endl;
    return 0;
}
