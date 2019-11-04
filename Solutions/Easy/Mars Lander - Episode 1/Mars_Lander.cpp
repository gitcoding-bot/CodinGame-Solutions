/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Mars Lander - Episode 1
Difficulty: Easy

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
    }

    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
        
        if (vSpeed < -40)
        {
            power += 1;
        }

        else if (vSpeed >0)
        {
            power += -1;
        }
        
        power = (power < 0)? 0 : power;
        power = (power > 4)? 4 : power;
        
        // 2 integers: rotate power. rotate is the desired rotation angle (should be 0 for level 1), power is the desired thrust power (0 to 4).
        cout << 0 << " " << power << endl;
    }
}
