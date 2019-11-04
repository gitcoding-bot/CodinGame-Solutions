/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Shadows of the Knight - Episode 1
Difficulty: Medium
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> bomb_direction(string bombDir)
{
    //converts bomb direction into x and y coordinates
    vector<int> b_dir;
    
    if (bombDir == "U")
    {
        b_dir = {0, -1};
        return b_dir;
    }
    else if (bombDir == "UR") 
    {
        b_dir = {1, -1};
        return b_dir;           
    }
    else if (bombDir == "R")
    {
        b_dir = {1, 0};
        return b_dir; 
    }
    else if (bombDir == "DR")
    {
        b_dir = {1, 1};
        return b_dir;  
    }
    else if (bombDir == "D")
    {
        b_dir = {0, 1};
        return b_dir;
    }
    else if (bombDir == "DL")
    {
        b_dir = {-1, 1};
        return b_dir;
    }
    else if (bombDir == "L")
    {
        b_dir = {-1, 0};
        return b_dir;
    }
    else
    {
        b_dir = {-1, -1};
        return b_dir;
    }
};

void possible_area(vector<int> current_loc, string bombDir, int &min_H, int &max_H, int &min_W, int &max_W)
{
    // determines the possible area the bomb is located in 
    vector<int> bomb_dir = bomb_direction(bombDir);
    
    if (bomb_dir[0] == 0)
    {
        min_W = (current_loc[0] > min_W) ? current_loc[0]:min_W;
        max_W = (current_loc[0] < max_W) ? current_loc[0]:max_W;
    }
    else
    {
        if (bomb_dir[0] == 1 && current_loc[0] > min_W)
        {
            min_W = current_loc[0]; 
        }
        
        else if(bomb_dir[0] == -1)
        {
            max_W = (current_loc[0] < max_W) ? current_loc[0]: max_W;   
        }
    }
    
    if (bomb_dir[1] == 0)
    {
        min_H = (current_loc[1] > min_H) ? current_loc[1]: min_H;
        max_H = (current_loc[1] < max_H) ? current_loc[1]: max_H;
    }
    else
    {
        if (bomb_dir[1] == 1 && current_loc[1]>min_H)
        {
            min_H = current_loc[1];
        }
        
        else if(bomb_dir[1] == -1)
        {
            max_H = (current_loc[1] < max_H) ? current_loc[1]: max_H;       
        }
    }        
};

vector<int> new_location(vector<int> current_loc, string bombDir, int min_H, int max_H, int min_W, int max_W)
{
    // Determines the new x and y coordinates Batman should move to
    int new_x = 0;
    int new_y = 0;
    
    vector<int> new_loc = {0,0};
    
    vector<int> bomb_direc = bomb_direction(bombDir);
    
    new_x = current_loc[0] + bomb_direc[0]*(max_W - min_W + 1)/2;
    new_y = current_loc[1] + bomb_direc[1]*(max_H - min_H + 1)/2;
    
    new_loc[0] = new_x;
    new_loc[1] = new_y;
    
    return new_loc;
    
};

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();

    cerr << W << " " << H << endl;

    vector<int> current_loc = {X0,Y0};

    int min_H = 0;
    int min_W = 0;
    int max_H = H;
    int max_W = W;

    vector<int> bomb_direction(string bombDir);
    void possible_area(vector<int> current_loc, string bombDir, int &min_H, int &max_H, int &min_W, int &max_W);
    vector<int> new_location(vector<int> current_loc, string bombDir, int min_H, int max_H, int min_W, int max_W);
    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        possible_area(current_loc, bombDir, min_H, max_H, min_W, max_W);
        current_loc = new_location(current_loc, bombDir, min_H, max_H, min_W, max_W);
        
        cout << to_string(current_loc[0]) << " " << to_string(current_loc[1]) << endl;
        
    }
}
