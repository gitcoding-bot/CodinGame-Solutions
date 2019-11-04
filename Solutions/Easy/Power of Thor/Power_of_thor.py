/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Power of Thor
Difficulty: Easy
*/


import sys
import math
import copy
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]


x = copy.copy(initial_tx)
y = copy.copy(initial_ty)

# game loop
while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.

    if light_x == x and light_y > y:
        y = y + 1
        print ("S")

    elif light_x > x and light_y == y:
        x = x + 1
        print ("E")
    
    elif light_x == x and light_y < y:
        y = y -1
        print ("N")
    
    elif light_x < x and light_y == y:
        x = x - 1
        print ("W")
    
    elif light_x > x and light_y > y:
        x = x + 1
        y = y + 1
        print ("SE")
    
    elif light_x > x and light_y < y:
        x = x + 1
        y = y - 1       
        
        print ("NE")
    
    elif light_x < x and light_y < y:
        x = x - 1
        y = y - 1
        
        print ("NW")
        
    elif light_x < x and light_y > y:
        x = x - 1
        y = y + 1
        
        print ("SW")

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)


    # A single line providing the move to be made: N NE E SE S SW W or NW
