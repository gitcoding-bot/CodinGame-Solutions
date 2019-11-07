#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int L;
    int C;
    int N;
    
    cin >> L >> C >> N; cin.ignore();   

    //Initialise the queue
    vector<int> queue_start(N); 
    //Number of completed rides
    int completed_rides = 0; 
    
    //Number of passengers on roller coaster
    int roller_coaster = 0; 
    
    // Amount of dirhams collected
    long int dirhams = 0; 
    
    vector<string> groups_strings;
    vector<long int>  groups_dirhams;
    
    groups_strings.push_back("g");
    groups_dirhams.push_back(0);

    for (long int i = 0; i < N; ++i) {
        long int Pi;
        cin >> Pi; cin.ignore();
        
        //Add each group to the queue;
        queue_start[i] = Pi;
    }    

    //Counter to make sure the same group of friends don't 
    //enter the same roller coaster twice
    int cnt = 0; 
    
    // Next group to enter roller coaster
    // Next group is first group in queue
    int next = queue_start[0]; 
    
    //Current position in queue
    int current_queue = 0; 
    
    //Index where group repetition occurs
    int index = -1;
    int number_of_groups = 1;
    int number_of_passengers = 0;
    
	for (int completed_rides = 0; completed_rides < C; completed_rides++)
	{

		while (roller_coaster < L && cnt < N && roller_coaster + next <= L)
		{
		    ++cnt;
		    
		    //Avoid queue out of range
		    if (current_queue + 1 >= N)
		    {
			    current_queue = 0;
			}
			else
			{
			    //Update to next group in queue
			    ++current_queue;
			}

			//Add group to roller coaster & update dirhams
			roller_coaster = roller_coaster + next;
			dirhams = dirhams + next;
			
			//Group up to find repetition
			//Update group dirhams
			groups_dirhams[number_of_groups - 1] = groups_dirhams[number_of_groups - 1] + next;

			//Update group string
			groups_strings[number_of_groups - 1] = groups_strings[number_of_groups - 1] + to_string(current_queue);

			if (current_queue > N - 1)
			{
			    current_queue = 0;
			}
			next = queue_start[current_queue];
			
			++number_of_passengers;
		}
		
		//If groups is not empty check for repetition
		if (number_of_groups != 1)
		{
		    int counter = 0;
		    for (int x = 0; x < number_of_groups - 1; ++x)
		    {
		        if (groups_strings[number_of_groups - 1] == groups_strings[x] && number_of_passengers >= N) //Check for repetition
		        {
		            //Need to remove duplicates
		            groups_strings.pop_back();
		            groups_dirhams.pop_back();
		            --number_of_groups;

		            //get index for where repetition starts
		            index = counter;
		            break;
		        }
		        else
		        {
		            //update counter
		            ++counter;
		        }
		    }
		}
		

		//If repetition was found
		if (index != -1)
		{
		    //Need to add 1 since current group has already been added to dirhams
		    int temp_index = index + 1;

		    if (temp_index > number_of_groups - 1)
		    {
		        temp_index = 0;
		    }
		    
		    completed_rides += 1;
		    
		    while (completed_rides < C)
		    {
		        dirhams = dirhams + groups_dirhams[temp_index];
		        
		        ++temp_index;
		        
		        if (temp_index > number_of_groups - 1)
		        {
		            temp_index = index;
		        }
		        
		        ++completed_rides;
		    }
		    break;
		}
		else
		{

		    ++number_of_groups;
		    groups_dirhams.push_back(0);
		    groups_strings.push_back("g");

		}
		
		
		//empty roller coaster
		roller_coaster = 0;
		cnt = 0;
	}

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    cout << dirhams;
}
