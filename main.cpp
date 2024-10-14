/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and G++
    Author: George Maratos and David Hayes
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over();


int main()
{
    // TODO: How you define main is up to you.
    display_instructions();
    initialize_board(); 
    do
    {
      display_board();
      make_move();
    } while (!game_over() && !cin.eof());
    return 0;
}

void make_move()
{
    /* TODO: Write a function that reads in a command from the user
    and  updates the  board, if  the  move  is valid.  ONLY use the
    functions get_element and set_element to update the board, do
    not access the array 'board' directly.
    */
  string validMoves[32] = {"ACG", "ABE", "ADI", "BFJ", "BGL", "BCD", "CGK", "DHL", "DCB", "DGJ", "EFG", "EJM", "EBA", "FGH", "GCA", "GKM", "GFE", "GHI", "HGF", "IHG", "IDA", "ILM", "JKL", "JGD", "JFB", "KGC", "LGB", "LKJ", "LHD", "MKG", "MJE", "MLI"};
  bool isValid = false;
  
  string userInput;
  cout << "Enter positions from, jump, and to (e.g. EFG): ";
  cin >> userInput;
  
  for (int upper = 0; upper < userInput.size(); ++upper){
    userInput[upper] = toupper(userInput[upper]);
    }

  if ((userInput.size() != 3) && (userInput != "X") && (userInput != "R")){
    cout << "*** Invalid sequence, please retry.";
    return;
    }
  
  else if (userInput == "X"){
    isValid = true;
    game_over();
    cout << "Exiting.";
    }
  else if (userInput == "R"){
    cout << "Restarting game.";
    initialize_board();
    return;
    }
  else {
    for (int range = 0; range < 3; ++range)
    if ((userInput[range] < 'A') || (userInput[range] > 'M')){
      cout << "*** Given move has positions not on the board! Please retry.";
      return;
      }
    else{
      get_element(userInput[range]);
      if ((range == 1) && (get_element(userInput[1]) != '#')){
        cout << "*** Must jump a piece. Please retry." << endl;
        return;
        }
      else if ((range == 0) && (get_element(userInput[0]) != '#')){
        cout << "*** Source needs a piece. Please retry." << endl;  
        return;
      }
      else if ((range == 2) && (get_element(userInput[2]) != '.')){
        cout << "*** Destination must be empty. Please retry." << endl;
        return;
      }
    }
        
    bool valid = false;
    for (int i = 0; i < 32; i++){
      if (userInput == validMoves[i]){
        valid = true;
        }
      } 
    if(valid){
        set_element(userInput[0], '.');
        set_element(userInput[1], '.');
        set_element(userInput[2], '#');
      }
    else{
        cout << "*** Move is invalid. Please retry." << endl;
        return;
      }
  }    
}

bool game_over()
{
    /* TODO: Write a function that returns true only if there is one
    one peg left, or if the user gives up by entering 'X' (or 'x')*/
    int peg = 0;
      for (char input = 'A'; input <= 'M'; input++)
      {
          if ('#' == get_element(input))
          {
            peg = peg + 1;
          }
      }
        if (peg == 1)
        {
          cout << "Congrats you win!" << endl;
          return true;
        }
        else
        {
          return false;
        }
}

void initialize_board()
{
    /* TODO: Initialize the board to have all peg, besides the very
    center hole.  ONLY use the functions get_element and set_element
    to update  the board,  do not access  the array 'board' directly.
    */
    set_element('A', '#');
    set_element('B', '#');
    set_element('C', '#');
    set_element('D', '#');
    set_element('E', '#');
    set_element('F', '#');
    set_element('G', '.');
    set_element('H', '#');
    set_element('I', '#');
    set_element('J', '#');
    set_element('K', '#');
    set_element('L', '#');
    set_element('M', '#');
}