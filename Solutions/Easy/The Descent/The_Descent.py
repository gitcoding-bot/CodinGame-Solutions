/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: The Descent
Difficulty: Easy
*/


import sys
import math

# The while loop represents the game.
# Each iteration represents a turn of the game
# where you are given inputs (the heights of the mountains)
# and where you have to print an output (the index of the moutain to fire on)
# The inputs you are given are automatically updated according to your last actions.


# game loop
while True:
    
    lys = []
    for i in range(8):
        mountain_h = int(input())  # represents the height of one mountain.
        lys.append(mountain_h)


    max_value = max(lys)
    max_index = lys.index(max_value)
    print (max_index)
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)

    # The index of the mountain to fire on.
