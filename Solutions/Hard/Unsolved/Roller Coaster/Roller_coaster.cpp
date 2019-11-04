/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Roller Coaster
Difficulty: Hard

This solution implements pointer manipulation to indicate where the front of the queue is. In an attempt
to optimize the code the roller coasters start filling up as soon as the first group size is read through
cin.get().
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int L;
    int C;
    int N;
    cin >> L >> C >> N; cin.ignore();
	int* queue_start = new int(N);
	
	int completed_rides = 0;
	int roller_coast = 0;
	long int dirhams = 0;
	int cnt2 = 1;

    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
		queue_start[i] = Pi;
		if (roller_coast + Pi <= L)
		{
		    roller_coast += Pi;
		    dirhams += Pi;
		    cnt2 += 1;
		}
		else
		{
		    //completed_rides++;
		    if(++completed_rides == C)
        		{
        		    cout << dirhams << endl;
        		    return 0;
        		}
		    if (Pi <= L)
		    {
                roller_coast = Pi;
		        dirhams += Pi;
		    }
		    
		    cnt2 = 1;
		}
    }
    
	int current_queue = 0;
    int next = queue_start[current_queue];
    
    	
	for (int cnt = completed_rides; cnt < C; cnt++)
	{
		while (roller_coast < L && cnt2 <= N && roller_coast + next <= L)
		{
		    cnt2++;
		    if (current_queue + 1 >= N)
		    {
			    current_queue = 0;
			}
			else
			{
			    current_queue = current_queue + 1;
			}
			roller_coast = roller_coast + next;
			dirhams = dirhams + next;
			next = queue_start[current_queue];
		}
		roller_coast = 0;
		cnt2 = 1;
	}
    cout << dirhams << endl;
}
