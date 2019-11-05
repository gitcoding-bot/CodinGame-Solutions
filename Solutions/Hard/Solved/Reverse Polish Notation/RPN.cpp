/*
CodinGame.com Solutions by gitcoding-bot

Puzzle: Reverse Polish Notation
Difficulty: Hard
Date: 05/11/2019
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class incorrect_stack_size{};
class division_by_zero{};
class incorrect_command{};
class stack_empty{};
class incorrect_stack_size_rol{};

class stack
{
public:
    int* start = nullptr;
    int stack_size = 0;
    int max_size = 0;
    
    stack();
    ~stack();
    
    
    void opperands(string command);
    void add();
    void subtract();
    void multiply();
    void divide();
    void mod();
    int pop();
    void dup();
    void swp();
    void rol();
    void push(int number);
    void stack_full();
};

stack::stack()
{
    max_size = 100;
    start = new int(max_size);
}

stack::~stack()
{
    delete[] start;
}

void stack::stack_full()
{
    max_size = max_size*2;
    int* new_start = new int(max_size);
    
    for (int i = 0; i < max_size/2; ++i)
    {
        new_start[i] = start[i];
    }
    
    delete[] start;
    start = new_start;
}

void stack::opperands(string command)
{
    if (stack_size == 0)
    {
        throw stack_empty();
    }
    else if (command == "POP")
    {

        pop();
    }
    else if (command == "DUP")
    {
        dup();
    }
    else if (stack_size < 2)
    {
        throw incorrect_stack_size();
    }
    else if (command == "ADD")
    {
        add();
    }
    else if (command == "SUB")
    {
        subtract();
    }
    else if (command == "MUL")
    {
        multiply();
    }
    else if (command == "DIV")
    {
        divide();
    }
    else if (command == "MOD")
    {
        mod();
    }
    else if (command == "SWP")
    {
        swp();
    }
    else if (command == "ROL")
    {
        rol();
    }
    else
    {
        throw incorrect_command();
    }
}


void stack::add()
{
    int number1 = pop();
    int number2 = pop();
    
    push(number1 + number2);
}

void stack::subtract()
{
    int number1 = pop();
    int number2 = pop();
    
    push(number2 - number1);
}

void stack::multiply()
{

    int number1 = pop();
    int number2 = pop();
    
    push(number1*number2);
}

void stack::divide()
{
    int number1 = pop();
    int number2 = pop();

    if (number1 == 0)
    {
        throw division_by_zero();
    }
    
    push(number2/number1);
}

void stack::mod()
{
    int number1 = pop();
    int number2 = pop();
    
    push(number2%number1);
}

int stack::pop()
{
    int number = start[stack_size - 1];
    --stack_size;
    
    return number;
}

void stack::dup()
{
    int number1 = pop();
    
    push(number1);
    push(number1);
}

void stack::swp()
{
    int number1 = pop();
    int number2 = pop();
    
    push(number1);
    push(number2);
}

void stack::rol()
{
    pop();
    
    if (stack_size <= 2)
    {
        throw incorrect_stack_size_rol();
    }
    
    //It needs to be a hard coded 3rd position
    int number2 = start[stack_size - 3];
    
    for (int i = stack_size - 3; i < stack_size - 1; ++i)
    {
        start[i] = start[i + 1];
    }
    
    --stack_size;
    
    push(number2);
}

void stack::push(int number)
{
    if (stack_size == max_size)
    {
        stack_full();
    }
    
    start[stack_size] = number;
    ++stack_size;
    
}

void use_string(string commands, stack& my_stack)
{
    char i = commands[0];
    
    int j = i;
    if ((j >= 48 && j <= 57) || i == '-') //Represents numbers 0 - 9 on ASCII table
    {
        j = 0;
        stringstream number(commands);
        
        number >> j;
        
        my_stack.push(j);
    }
    else //If not a number then it must be a command
    {
        //Determine which method to call
        my_stack.opperands(commands.substr(0,3));
    }
    
}

int main()
{
    stack my_stack;
    
    try{
        int N;
        cin >> N; cin.ignore();
        
        //Get input instructions
        for (int i = 0; i < N; i++) 
        {
            string instruction;
            cin >> instruction; cin.ignore();
            use_string(instruction, my_stack);
        }

        string output;
        
        //Print the stack as a single string
        for (int i = 0; i < my_stack.stack_size; ++i)
        {
            output = output + to_string(my_stack.start[i]);
            if (i != my_stack.stack_size - 1)
            {
                output = output + ' ';
            }
        }
        
        cout << output;
    }
    
    //Error handling
    catch(stack_empty)
    {
        cerr << "Stack is empty" << endl;
        cout << "ERROR";
    }
    catch(incorrect_stack_size)
    {
        cerr << "Incorrect stack size" << endl;
        cout << "ERROR";
    }
    catch(division_by_zero)
    {
        cerr << "Division by zero" << endl;
        string output;

        for (int i = 0; i < my_stack.stack_size; ++i)
        {
            output = output + to_string(my_stack.start[i]);
            output = output + ' ';
        }
        output = output + "ERROR";
        cout << output;
    }
    catch(incorrect_command)
    {
        cerr << "Incorrect command" << endl;
        cout << "ERROR";
    }
    catch(incorrect_stack_size_rol)
    {
        cout << "ERROR";
    }    
    
}
