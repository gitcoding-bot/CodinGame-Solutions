/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: War
Difficulty: Medium

My solutions uses 4 queue data structures. The first two queues are player 1
and player 2's cards respectively. The third and the fourth queues are the cards 
played during the "war" for player 1 and player 2 respectively. 

*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
 
class battle
{
public:
    int player = 0; //The player that won this battle
    int rounds = 0; //How many rounds took place
    bool tie = false; //Is this battle a tie?
};
 

int string_to_int(string card)
{
    //Converts string into int
    char val = card[0];
    
    if (val == '2') {return 2;}
    else if (val == '3') {return 3;}
    else if (val == '4') {return 4;}
    else if (val == '5') {return 5;}
    else if (val == '6') {return 6;}
    else if (val == '7') {return 7;}
    else if (val == '8') {return 8;}
    else if (val == '9') {return 9;}
    else if (val == '1') {return 10;}
    else if (val == 'J') {return 11;}
    else if (val == 'Q') {return 12;}
    else if (val == 'K') {return 13;}
    else if (val == 'A') {return 14;}
    
}

bool war(queue<int> &p1_cards, queue<int> &p2_cards, queue<int> &p1_temp_queue, queue<int> &p2_temp_queue)
{

    //Represents one round of war

    if (p1_cards.size() < 4 || p2_cards.size() < 4) //If a player has less than 4 cards it's a draw
    {
        return false;
    }
    
    for (int i = 0; i <= 3; i++) //Add 4 cards from P1 and P2 hands to temporary queue
    {
        p1_temp_queue.push(p1_cards.front());
        p1_cards.pop();
        
        p2_temp_queue.push(p2_cards.front());
        p2_cards.pop();
    }
    
    return true;
    
    
}

battle battle_func(battle &this_battle, queue<int> &p1_cards, queue<int> &p2_cards, queue<int> &p1_temp_cards, queue<int> &p2_temp_cards, bool tie)
{
    int p1_top_card = p1_cards.front();
    int p2_top_card = p2_cards.front();

    if (tie)
    {
        this_battle.tie = true;
        return this_battle;
    }
    
    if (p1_cards.empty()) //P1 loses, since he ran out of cards
    {
        this_battle.player = 2;
        return this_battle;
    }
    else if (p2_cards.empty()) //P2 loses, since he ran out of cards
    {
        this_battle.player = 1;
        return this_battle;
    }
    else if (p1_top_card > p2_top_card) { //P1 wins and gets all temporary cards in queus
        while (not(p1_temp_cards.empty()))
        {
            p1_cards.push(p1_temp_cards.front());
            p1_temp_cards.pop();
        }
        p1_cards.push(p1_top_card);
        while (!p2_temp_cards.empty())
        {
            p1_cards.push(p2_temp_cards.front());
            p2_temp_cards.pop();
        }
        p1_cards.push(p2_top_card);
        p1_cards.pop();
        p2_cards.pop();
    }
    else if (p1_top_card < p2_top_card) { //P2 wins and gets all temporary cards in queues
        while (!p1_temp_cards.empty())
        {
            p2_cards.push(p1_temp_cards.front());
            p1_temp_cards.pop();
        }
        p2_cards.push(p1_top_card);
        while (!p2_temp_cards.empty())
        {
            p2_cards.push(p2_temp_cards.front());
            p2_temp_cards.pop();
        }
        p2_cards.push(p2_top_card);
        p1_cards.pop();
        p2_cards.pop();
    }
    else
    {
        this_battle.rounds -= 1;
        if (!war(p1_cards, p2_cards, p1_temp_cards, p2_temp_cards))
        {
            return battle_func(this_battle, p1_cards, p2_cards, p1_temp_cards, p2_temp_cards, true);
        }
    }
    this_battle.rounds += 1;
    return battle_func(this_battle, p1_cards, p2_cards, p1_temp_cards, p2_temp_cards, false);
}

int main()
{
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    queue<int> p1_cards;
    queue<int> p2_cards;
    queue<int> p1_temp_cards;
    queue<int> p2_temp_cards;
    battle this_battle;
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        p1_cards.push(string_to_int(cardp1));
    }
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        p2_cards.push(string_to_int(cardp2));
    }

    battle my_battle = battle_func(this_battle, p1_cards, p2_cards, p1_temp_cards, p2_temp_cards, false);

    if (this_battle.tie)
    {
        cout << "PAT" << endl;
    }
    else
    {
        cout << my_battle.player << " " << my_battle.rounds << endl;
    }
}
