#include <iostream>
#include "blackjack.h"
using namespace std;

Player::Player()
{
    vector <Card> temp;
    hand = temp;
    name = "NULL";
    bet = 0;
    score = 0;
    in = 0;
    handSize = 0;

}

Player::Player(string n, vector<Card> hand, int betA, int score, int in, int handSize)
{
    name = n;
    this -> hand = hand;
    bet = betA;
    this -> score = score;
    this-> in = in;
    this -> handSize = handSize;
}

void Player::setName(string name)
{
    this->name = name;
}

void Player::setBet(int bet)
{
    this->bet = bet;
}

void Player::setCard(pair<int, string> card)
{
    Card* temp = new Card;
    temp->symbol = card.second;
    temp->value = card.first;
    if (name == "Dealer" && handSize == 0)
    {
        temp->faceUp = 0;
    }else{
        temp->faceUp = 1;
    }
    handSize++;
    hand.push_back(*temp);
}

void Player::setIn(int in)
{
    this->in = in;
}

string Player::getName()
{
    return name;
}

int Player::getBet()
{
    return bet;
}

int Player::getCard(int index)
{
    int temp = hand[index].value;
    return temp;
}

int Player::getScore()
{
    return score;
}

void Player::updateScore()
{
    score = 0;
    int temp(0);
    
    for (auto i : hand)
    {
        temp = i.value;
        
        if (i.symbol == "A" && score <= 10)
        {
            score += 11;
        }else if(i.symbol == "A" && score > 10){

            score +=1;
        
        }else{
            score += temp;
        }   
    }
    
}

int Player::getIn()
{
    return in;
}

void Player::printHand()
{
    cout << name << "'s Hand: ";
    for (auto i : hand){
        if (i.faceUp == 1)
        {
            cout << i.symbol << " ";
        }else if(i.faceUp == 0){
            cout << "X" << " ";
        }
        
    }
    if (name == "Dealer")
    {
        cout << "Score: (?)\n";
    }else{
        cout << "Score: (" << score <<")\n";
    }
    
    
}

bool Player::checkScore()
{
    if (score == 21 && hand.size() == 2)
    {
        cout << name << " Wins " << bet*1.5 <<" dollars" << endl;
        if (name == "Dealer")
        {
            cout << "Dealer has won." << endl; 
            return true;
        }
        
        in = 2;
        return false;

    }else if(score > 21 && name == "Dealer"){

        cout << "Dealer Busts with a "<< score << "! Table wins. ";
        return true;

    }else if (score > 21)
    {
        cout << name << " has busted. They lose " << bet << " dollars" << endl;
        in = 1;
        return false;
    }
    return false;
}

vector<std::pair<int, std::string>> generateDeck() {
    std::vector<std::pair<int, std::string>> deck;
    std::vector<std::string> icons = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11}; // Ace has value 11
    int count(0);
    
    for (const auto& icon : icons) {
        for(int i = 0; i < 4; i++){
            deck.push_back(make_pair(values[count], icon));
        }
        count++;
    }

    return deck;
}

bool dealerBust(bool finished)
{
    return true;
}


void initialize(vector <pair<int, string>>& cards, int players, Player* table)
{
    string name;
    int betA;
    int pot(0);
    for (int i = 1; i < players; i++)
    {
        cout << "Player " << i << " please input your name: ";
        cin >> name;
        cout << "Player " << i << " please input your bet: ";
        cin >> betA;
        pot += betA;
        table[i].setName(name);
        table[i].setBet(betA);
        dealCard(table[i], 2, cards);
        cout << endl;
    }
    table[0].setName("Dealer");
    table[0].setBet(pot);
    dealCard(table[0], 2, cards);
    output(table, players-1);

}

void dealCard(Player& player, int cardNum, vector <pair<int, string>>& cards)
{
    int randomIndex;
    for (int i = 0; i < cardNum; i++)
    {
        randomIndex = rand() % cards.size();
        player.setCard(cards[randomIndex]);
        cards.erase(cards.begin() + randomIndex);
    }
    player.updateScore();
}

void output(Player* table, int num)
{
    for (int i = 0; i < num+1; i++)
    {
        if (table[i].getIn() == 0 || table[i].getIn() == 3)
        {
            table[i].printHand();
            cout << endl;
        }
    }
}

void finalScoreCheck(Player* table, int currentPlayer)
{
    if (table[currentPlayer].getScore() > table[0].getScore())
        {
           cout << table[currentPlayer].getName() << " wins " << table[currentPlayer].getBet() << " dollars. Congrats!" << endl;
        }else if (table[currentPlayer].getScore() < table[0].getScore())
        {
            cout << table[currentPlayer].getName() << " loses " << table[currentPlayer].getBet() << " dollars. Try Again!" <<endl;
        }else{
            cout << table[currentPlayer].getName() << " pushes and wins 0 dollars." << endl;
        }
}

void endGame(Player* table, int players)
{
    cout << "Round over.\n";
    cout << "Dealer's Score: " << table[0].getScore() << endl;
    for (int i = 1; i < players+1; i++)
    {
        if (table[i].getIn() == 0 || table[i].getIn() == 3)
        {
            finalScoreCheck(table, i);
        }
        
    }
}

void round(Player* table, int players, vector <pair<int, string>>& cards, bool& roundDone)
{
    cout << endl;
    bool dealer21;
    dealer21 = table[0].checkScore();
    if (dealer21 == true)
    {
       endGame(table, players);
       return;
    }
    
    vector <char> choices = {'S'};
    char choice('S');
    for (int i = 1; i <= players+1; i++)
    {
        if (table[i].getIn() == 0)
        {
            cout << table[i].getName() << ": Hit or Stand? (H/S) ";
            cin >> choice;
            if (choice == 'H')
            {
                dealCard(table[i], 1, cards);
                cout << table[i].getName() << " hits.\n";
                choices.push_back(choice);
            }else{
                cout << table[i].getName() << " stands.\n";
                choices.push_back(choice);
                table[i].setIn(3);
            }
        }
        
    }

    choices.erase(choices.begin());    

    cout << endl;

    if (table[0].getScore() >= 17)
    {
        cout << "Dealer stands.\n";
    }else if(table[0].getScore() < 17){
        dealCard(table[0], 1, cards);
    }

    for (int i = 0; i < players; i++)
    {
        if (table[i].getIn() == 0 || table[i].getIn() == 3)
        {
            table[i].updateScore();
        }
        
    }
    
    bool temp;
    output(table, players);
    for (int i = 1; i <= players ; i++)
    {
       if (table[i].getIn() == 0 || table[i].getIn() == 3)
        {
            table[i].checkScore();
        }
    }

    bool gameOver;
    for (int i = 1; i <= players; i++)
    {
        if (table[i].getIn() != 1)
        {
            gameOver = false;
            break;
        }
        gameOver = true;
    }

    if (gameOver == true)
    {
        cout << "Everyone busted. Dealer wins. ";
    }else{
        temp = table[0].checkScore();
        if (temp == true)
        {
            roundDone = temp;
        }    
    }
    

    bool hitsLeft(false);
    for (auto n : choices)
    {
        if (n == 'H')
        {
            hitsLeft = true;
            break;
        }
    }

    if (hitsLeft == false)
    {
        cout << endl;
        endGame(table, players);
    }

}

bool gameContinue(Player* table, int players)
{

    for (int i = 1; i < players+1; i++)
    {
        if(table[i].getIn() == 0) //since nobody had a 0 (or was in), it returned false and ended the round even though the final score check had not yet been completed.
        {
            return true;
            endGame(table, players);
        }
    }
    return false;
}
