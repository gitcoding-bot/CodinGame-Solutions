/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: There is no spoon
Difficulty: Medium
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

bool is_node(const vector<vector<char>> vec_2d, vector<int> place)
{
    //checks if applicable location (x, y) has a node
    int x = place[0];
    int y = place[1];
    vector<char> vec_1d = vec_2d[y];
    
    char val_to_check = vec_1d[x];
    
    bool cond;
    
    //cond = (val_to_check == '0')? true : false;
    
    if (val_to_check == '0')
    {
        cond = true;
    }
    
    else
    {
        cond = false;
    }
    
    return cond;
};

string right_check(const vector<vector<char>> vec_2d, vector<int> place, int width, int height)
{
    //checks if location to the right of (x, y) has a node  
    
    int x = place[0];
    int y = place[1];
    
    int x_to_check = x + 1;
    int y_to_check = y;
    
    if (x_to_check >= width)
    {
        return "-1 -1 ";
    }
    
    vector<int> place_to_check = {x_to_check, y_to_check};
   
    if(is_node(vec_2d, place_to_check))
    {
        return to_string(x_to_check) + " " + to_string(y_to_check) + " ";
    }
    
    return right_check(vec_2d, place_to_check, width, height);
};

string down_check(const vector<vector<char>> vec_2d, vector<int> place, int width, int height)
{
    //checks if location to the bottom of (x, y) has a node      
    
    int x = place[0];
    int y = place[1];
    
    int x_to_check = x;
    int y_to_check = y + 1;
    
    if (y_to_check >= height)
    {
        return "-1 -1 ";
    }
    
    vector<int> place_to_check = {x_to_check, y_to_check};

    if(is_node(vec_2d, place_to_check))
    {
        return to_string(x_to_check) + " " + to_string(y_to_check) + " ";
    }
    
    return down_check(vec_2d, place_to_check, width, height);
    
};

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    vector<vector<char>> vec_2d;
    
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line); // width characters, each either 0 or .
        vector<char> vec_1d = {};
        for (char c:line)
        {
            vec_1d.push_back(c);
        }
        
        vec_2d.push_back(vec_1d);

    }

    string right_check(vector<vector<char>> vec_2d, vector<int> place, int width, int height);
    bool is_node(vector<vector<char>> vec_2d, vector<int> place);
    string down_check(vector<vector<char>> vec_2d, vector<int> place, int width, int height);

    vector<int> place = {0,0}; 

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            place[0] = x;
            place[1] = y;

            string right;
            string down;

            if (is_node(vec_2d, place))
            {
                right = right_check(vec_2d, place, width, height);

                down = down_check(vec_2d, place, width, height);

                cout << to_string(x) << " " << to_string(y) 
                << " " << right << down << endl;
            }
        }
        
    }
}
