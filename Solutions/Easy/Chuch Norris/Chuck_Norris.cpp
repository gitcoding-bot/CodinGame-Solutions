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

void binary_conv(vector<char> &v, char c)
{
        //Converts the ASCII characters into binary representation.
        
        int i = int(c);
        int remain = 1;
        int val = 1;
        
        val = i;
        
        while (val > 0)
        {
            remain = val%(2);
            val /= 2;
            
            if (remain == 0)
            {
                v.insert(v.begin(), '0');
            }
            else
            {
                v.insert(v.begin(), '1');
            }

        }
        
};

void chuck_norris(string &vv, vector<char> v)
{
    //Converts the binary representation into Chuck Norris representation.
    
    int cnt = 0;
    
    for (char c: v)
    {
        if (vv == "")
        {
            if (c == '0')
            {
                vv += "00 0";
            }
            else
            {
                vv += "0 0";
            }
        }
        else
        {
            if (c == v[cnt - 1])
            {
                vv += "0";
            }
            else
            {
                if (c == '0')
                {
                    vv += " 00 0";
                }
                else
                {
                    vv += " 0 0";
                }    
            }
            
        }
        cnt++;
    }
    
};

int main()
{
    void binary_conv(vector<char> &v, char c);
    void chuck_norris(string &vv, vector<char> v);
    
    string MESSAGE;
    
    getline(cin, MESSAGE);
    vector<char> v = {};
    string vv;
    int cnt = 1;
    char c;

    for (int i = MESSAGE.size() - 1; i >= 0; i = i - 1)
    {
        c = MESSAGE[i];
        binary_conv(v, c);
        while (v.size() < cnt*7)
        {
            v.insert(v.begin(), '0'); 
        }
        ++cnt;
    }
    chuck_norris(vv, v);

    cout << vv << endl;
}
