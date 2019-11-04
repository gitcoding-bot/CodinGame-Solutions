/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Aneo
Difficulty: Medium
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

bool is_light_green(double t, double duration)
{
    //determines if the light will be green when the car gets there
    float val = t/(duration*2);
    
    val = floor(val);

    t = (val >= 1)? t - (2*duration)*val : t;
    
    if (t/duration < 1)
    {
        return true;        
    }

    return false;
}


bool test_speed(double c_speed, int duration, double distance)
{
    //tests if the light will be green when the car drives at this speed
    //return true if it will be green and false if it isnt
    double t = distance/(c_speed*1000/3600);

    //double t = distance/(c_speed);
    if (is_light_green(t, duration))
    {
        return true;
    }
    return false;
    
}


int max_speed_allowed(vector<int> v_distance, vector<int> v_duration, int speed_lim, int c_speed)
{
    //calculates the max speed allowed
    int cnt = 0;
    for (int distance:v_distance)
    {
        int duration = v_duration[cnt];
        if (not (test_speed(c_speed, duration, distance)))
            {
                return max_speed_allowed(v_distance, v_duration, speed_lim, c_speed - 1);
            }
        ++cnt;
    }  
    return c_speed;
}

int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    
    vector<int> v_distance {};
    vector<int> v_duration {};
    
    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        
        cin >> distance >> duration; cin.ignore();
   
        v_distance.push_back(distance);
        v_duration.push_back(duration);
        
    }


    int m_speed = max_speed_allowed(v_distance, v_duration, speed, speed);

    cout << m_speed << endl;
}
