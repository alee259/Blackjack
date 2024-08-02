#include <iostream>
#include <vector>
#include "blackjack.cpp"
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

int main()
{
    char cont('y');
    while(cont == 'y' || cont == 'Y'){
        vector <pair<int, string>> cards = generateDeck();

        cout << "How many players are there? ";
        int numPlayers(0);
        cin >> numPlayers;

        Player* table = new Player[numPlayers+1];
        srand(time(0));

        initialize(cards, numPlayers+1, table);    

        bool roundDone(false);

        do
        {
            //infinite loop issue, endgame outputting issue
            round(table, numPlayers, cards, roundDone); 
            cout << endl;            

        } while (gameContinue(table,numPlayers) && roundDone == false);
        delete[] table;

        cout << "\nPlay Again? (y/n): ";
        cin >> cont;

    }

}