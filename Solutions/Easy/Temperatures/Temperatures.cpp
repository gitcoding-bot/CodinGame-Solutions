/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Chuck Norris
Difficulty: Easy
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    
    int min_val = 5527;
    for (int i = 0; i < n; i++) {
        int t; // a temperature expressed as an integer ranging from -273 to 5526
        cin >> t; cin.ignore();
        if (abs(min_val) == abs(t))
        {
            min_val = (t > min_val) ? t : min_val;
        }
        else if ((abs(t)) < (abs(min_val)))
        {
            min_val = t;
        }
    }
    
    min_val = (min_val == 5527) ? 0 : min_val;

    cout << min_val << endl;
}
