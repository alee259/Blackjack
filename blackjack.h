#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <time.h>
using namespace std;

struct Card {
    std::string symbol;
    int value;
    int faceUp;
};

class Player {
private:
    std::string name;
    int bet;
    int score;
    int in;
    int handSize;
    std::vector<Card> hand;

public:
    Player();
    Player(std::string n, std::vector<Card> hand, int betA, int score, int in, int handSize);
    void setName(std::string name);
    void setBet(int bet);
    void setCard(std::pair<int, std::string> card);
    void setIn(int in);
    std::string getName();
    int getBet();
    int getCard(int index);
    int getScore();
    void updateScore();
    int getIn();
    void printHand();
    bool checkScore();
};

vector<std::pair<int, std::string>> generateDeck();

void initialize(vector <pair<int, string>>& cards, int players, Player* table);

void dealCard(Player& person, int cardNum, vector <pair<int, string>>& cards);

void output(Player* table, int num);

void round(Player* table, int players, vector <pair<int, string>>& cards, bool& roundDone);

bool gameContinue(Player* table, int players);

void endGame(Player* table, int players);

void finalScoreCheck(Player* table, int currentPlayer);

bool dealerBust(bool finished);

