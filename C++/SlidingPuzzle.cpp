#include<iostream>
#include<ctime>
#include<climits>
using namespace std;
int const Max_Grid_size = 5; //The maximum grid size 
int grid_size = 5; //Grid size that changes based on the type
int grid[Max_Grid_size][Max_Grid_size]; //The actual grid
int move_counter = 0; //Counts how many times the player moved 
int high_scores[3] = { INT_MAX,INT_MAX,INT_MAX }; //Using INT_MAX as the default values, because the "highest" score is the lowest number
void game(); //The main engine where we control the game
void options(int choice); //Helps the menu navigate the options 
void change_grid_size(); //Changes the grid's size
void show_current_score(); //Shows the current high scores for every size
void new_game(); //Starts up a new game (Deletes old high scores as well)
void shuffle_grid(); //Shuffles the grid's components 
void restart(); //Restarts the game (Without deleting old high scores)
void resume(); //Resumes the game
void original_grid(); //Generates the grid based on the size
void update_high_scores(int move_counter); //Updates the high scores for every grid size
bool win_checker(); //Checks if the player won 
void display_grid(); //Shows the whole grid
void move_tile(char move, int null_row, int null_collumn); //Moves the numbers around on the grid
void null_coordinate(int& null_row, int& null_collumn); //Finds the coordinate of the 0 tile (Used & so that we could use the values in other functions)
void quit_game(); //Quits from the game
void menu() //The menu where the player chooses 1-7
{
    cout << "--- Sliding Puzzle Game ---" << endl;
    cout << "1. Start new game" << endl;
    cout << "2. Change grid size" << endl;
    cout << "3. Show current score" << endl;
    cout << "4. Shuffle current grid" << endl;
    cout << "5. Restart game" << endl;
    cout << "6. Resume" << endl;
    cout << "7. Quit" << endl;
    cout << "Choose the option: ";
    int choice;
    cin >> choice;
    cout << endl;
    options(choice);
}
void options(int choice)
{
    switch (choice) //Using switch function to determine which option the player chose
    {
    case 1:
        new_game();
        break;
    case 2:
        game();
        break;
    case 3:
        show_current_score();
        break;
    case 4:
        shuffle_grid();
        move_counter = 0; // to make sure it doesnt get affected by 100 times shuffling
        break;
    case 5:
        restart();
        break;
    case 6:
        resume();
        break;
    case 7:
        quit_game();
        break;
    }
}
void game()
{
    char move; //Using a char variable to determine what the user clicked
    int null_row, null_collumn; //The coordinates of the 0 space
    bool answer; //Answer for if the game was won or not
    char answer_yes_no; //variable for if they want to continue
    change_grid_size(); //We first determine the grid size
    original_grid(); //Then generate one
    shuffle_grid(); //Shuffle it to make it random
    cout << endl;
    display_grid(); //And then display it for the user
    move_counter = 0; //counting moves and making sure its 0 at the start
    cout << "Enter W A S D to move around and R to return to menu ";
    while (true) //We use a while loop to start the actual game that lasts till the player wins 
    {
        answer = win_checker(); //Determining if the player won 
        if (answer == 0) //If the player has won then we stop the loop
        {
            cout << "Enter another move: ";
            cin >> move; //We take moves each time
            null_coordinate(null_row, null_collumn); //Find the empty space
            move_tile(move, null_row, null_collumn); //Move numbers based on that empty space and user input 
            display_grid(); //Display the result every time
            cout << endl;
            cout << "Moves made: " << move_counter << endl; //Tell the player the amount of times they've moved already
        }
        else
        {
            cout << "You won in: " << move_counter << " moves!" << endl; //If they have won we give a congratulatory message and their score
            update_high_scores(move_counter); //Save the highest scores
            cout << "Would you like to continue" << endl;
            cin >> answer_yes_no;
            if (answer_yes_no == 'y')
                menu(); //Give the menu again
            else
                quit_game();
            break;
        }
    }
}
void change_grid_size()
{
    cout << "Choose the grid size" << endl;
    cout << "1. 3x3" << endl;
    cout << "2. 4x4" << endl;
    cout << "3. 5x5" << endl;
    int grid_size_choice;
    cin >> grid_size_choice; //Let the player choose their preffered mode and then give it back to the game function
    switch (grid_size_choice)
    {
    case 1:
        grid_size = 3;
        break;
    case 2:
        grid_size = 4;
        break;
    case 3:
        grid_size = 5;
        break;
    }
}
void original_grid()
{
    int i, j; //We generate a basic square grid based on the size 
    int value = 1; //Pick a value that lets the function fill the grid from 1
    for (i = 0; i < grid_size; i++)
        for (j = 0; j < grid_size; j++)
        {
            if (i == grid_size-1 && j == grid_size-1) //makes the last value empty
            grid[i][j] = 0;
            else
            grid[i][j] = value;
            value++;
        }
    
}
void shuffle_grid()
{
    int i;
    int null_row, null_collumn;
    srand(time(0));
    char moves[4] = { 'W', 'A', 'S', 'D' }; //We use a randomizer 0-3 100 times that chooses a move from the char array and then performs it on the grid with the move_tile function 
    for (i = 0; i < 100; i++)
    {
        null_coordinate(null_row, null_collumn);
        move_tile(moves[rand() % 4], null_row, null_collumn);
    }
}
void null_coordinate(int& null_row, int& null_collumn) //We compare every element of the grid to 0 so we can find the exact coordinates of the empty space
{
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (grid[i][j] == 0)
            {
                null_row = i;
                null_collumn = j;
                return;
            }
}
void move_tile(char move, int null_row, int null_collumn)
{
    switch (move) //Based on the move we swap the empty space with an adjacent space (Also added the Menu option right here for convinience)
    {
    case 'D':
    case 'd':
        if (null_collumn - 1 >= 0)
        {
            swap(grid[null_row][null_collumn], grid[null_row][null_collumn - 1]);
            move_counter++; //Count the amount of times the player moved
        }
        break;
    case 'W':
    case 'w':
        if (null_row + 1 < grid_size)
        {
            swap(grid[null_row][null_collumn], grid[null_row + 1][null_collumn]);
            move_counter++;
        }
        break;
    case 'A':
    case 'a':
        if (null_collumn + 1 < grid_size)
        {
            swap(grid[null_row][null_collumn], grid[null_row][null_collumn + 1]);
            move_counter++; 
        }
        break;
    case 'S':
    case 's':
        if (null_row - 1 > -1)
        {
            swap(grid[null_row][null_collumn], grid[null_row - 1][null_collumn]);
            move_counter++; 
        }
        break;
    case 'R':
    case 'r':
        menu();
        break;
    }
}
void display_grid() //Just go through the whole grid and output every number
{
    int i, j;
    for (i = 0; i < grid_size; i++)
    {
        for (j = 0; j < grid_size; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}
bool win_checker() //We use a bool function to return true or false value
{
    int i, j, num = 0;
    bool answer = 0;
    if (grid[grid_size - 1][grid_size - 1] == 0) //Make sure the empty space is at the end and not at the start
    {
        for (i = 0; i < grid_size; i++)
        {
            for (j = 0; j < grid_size; j++) //Go through the whole grid 
            {
                if (grid[i][j] > num) //Check if the numbers are actually ascending 
                {
                    answer = 1;
                    num = grid[i][j];
                }
                else
                {
                    if (grid[i][j] == 0 && num == grid_size * grid_size - 1) //When we reach the end, the 0 is going to be less than num so we make sure if that's the case answer won't be 0
                        answer = 1;
                    else
                    {
                        answer = 0;
                        break;
                    }
                }
            }
            if (answer == 0)
                break; //If both factors fail we exit out of the function
        }
    }
    return answer; //Give the answer back
}
void update_high_scores(int move_counter)
{
    switch (grid_size) //check if the new score is actually lower than the older one and if it is, change the value based on size
    {
    case 3:
        if (move_counter < high_scores[0])
            high_scores[0] = move_counter;
        break;
    case 4:
        if (move_counter < high_scores[1])
            high_scores[1] = move_counter;
        break;
    case 5:
        if (move_counter < high_scores[2])
            high_scores[2] = move_counter;
        break;
    }
}
void show_current_score()
{
    if (high_scores[0] == INT_MAX) //If the value is still max that means the player has yet to play that base, otherwise we show the score
        cout << "Highest score in 3x3: NONE" << endl;
    else
        cout << "Highest score in 3x3: " << high_scores[0] << endl;
    if (high_scores[1] == INT_MAX)
        cout << "Highest score in 4x4: NONE" << endl;
    else
        cout << "Highest score in 4x4: " << high_scores[1] << endl;
    if (high_scores[2] == INT_MAX)
        cout << "Highest score in 5x5: NONE" << endl;
    else
        cout << "Highest score in 5x5: " << high_scores[2] << endl;
    cout << endl;
    cout << "Do you want to see the menua again?" << endl; //Checks to see if they want to continue
    char menu_answer;
    cin >> menu_answer;
    if (menu_answer == 'y')
    {
        menu();
        cout << endl;
    }
    if (menu_answer == 'n')
        quit_game();
}
void new_game() //Resets the high scores and loads a new game
{
    high_scores[0] = INT_MAX;
    high_scores[1] = INT_MAX;
    high_scores[2] = INT_MAX;
    game();
}

void restart()
{
    new_game(); //Restarts by loading a new game
}
void resume()
{
    //Because the game function doesn't stop running we can just leave the resume function blank
}
void quit_game()
{
    cout << "Goodbye!"; //Simply exits the game and says goodbye
    exit(0); //exits out
}
int main()
{
    menu(); //Only need to call the menu function in main
}