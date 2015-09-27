#include <iostream>
#include <string>
#include <limits>
#include <ncurses.h>
#include <unistd.h>
#include <term.h>


using namespace std;

WINDOW *create_newwin(int height, int width, int starty, int startx);

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

// defines array used to store data
int game [10][10][6];
void ClearScreen()
{
    if (!cur_term)
    {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }
    
    putp( tigetstr( "clear" ) );
}
// displays board
void display(int z, string player) {
    system("clear");
    refresh();
    ClearScreen();
    cout << "    ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗" << endl <<  " " << player << " ║";
    string top [10] { " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 " };
    for (int i = 0; i < 10; i++) cout << top[i] << "║";
    cout << endl << "╔═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << endl ;
    string side [10] { " a ", " b ", " c ", " d ", " e ", " f ", " g ", " h ", " i ", " j " };
    for (int y = 0; y < 10; y++) {
        cout << "║" << side[y] << "║";
        for (int x = 0; x < 10; x++) {
            string boat [8] = { "   ", " ◄ ", " ▲ ", " ■ ", " ▼ ", " ► ", " X ", " O " };
            cout << boat [game [y][x][z]] << "║";
        }
        if (y < 9) cout << endl << "╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << endl;
    }
    cout << "\n╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n" ;
}

void add(int i, int j, int ship, int max, string name, string player) {
    //gets direction
    int direction = 0;
    cout << "Press 1 to place your " << name << " horizontally or 2 to place it vertically: ";
    while (!(cin >> direction) || (direction != 1 && direction != 2)) {
        cout << "You must enter either 1 or 2.\n";
        cout << "Press 1 to place your " << name << " horizontally or 2 to place it vertically: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (direction ==1) {
        //gets row
        cout << "Please enter the row it will be in: ";
        char input;
        cin >> input;
        int row = 10;
        switch (input) {
            case 'a' : row = 0; break;
            case 'b' : row = 1; break;
            case 'c' : row = 2; break;
            case 'd' : row = 3; break;
            case 'e' : row = 4; break;
            case 'f' : row = 5; break;
            case 'g' : row = 6; break;
            case 'h' : row = 7; break;
            case 'i' : row = 8; break;
            case 'j' : row = 9; break;
        }
        while ( row > 10 || row < 0 ) {
            cout << name << " must be in a row between a and j.\n";
            cout << "Please enter the row it will be in: ";
            cin >> input;
            switch (input) {
                case 'a' : row = 0; break;
                case 'b' : row = 1; break;
                case 'c' : row = 2; break;
                case 'd' : row = 3; break;
                case 'e' : row = 4; break;
                case 'f' : row = 5; break;
                case 'g' : row = 6; break;
                case 'h' : row = 7; break;
                case 'i' : row = 8; break;
                case 'j' : row = 9; break;
            }
        }
        //gets column
        cout << "Please enter which column it will begin at: ";
        int column = 10;
        while (!(cin >> column) || column > max || column < 0) {
            cout << name << " must begin at a column between 0 and " << max << ".\n";
            cout << "Please enter which column it will begin at: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //adds ship
        int index = 1;
        game [row][column][i] = 1;
        game [row][column][j] = ship;
        while (index < ship) {
            game [row][column+index][i] = 3;
            game [row][column+index][j] = ship;
            index++;
        }
        game [row][column+index][i] = 5;
        game [row][column+index][j] = ship;
    }
    
    if (direction == 2) {
        //gets column
        cout << "Please enter the column it will be in: ";
        int column = 10;
        while (!(cin >> column) || column > 9 || column < 0) {
            cout << name << " must be in a column between 0 and 9.\n";
            cout << "Please enter the column it will be in: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //gets row
        cout << "Please enter which row it will begin at: ";
        char input;
        cin >> input;
        int row = 10;
        switch (input) {
            case 'a' : row = 0; break;
            case 'b' : row = 1; break;
            case 'c' : row = 2; break;
            case 'd' : row = 3; break;
            case 'e' : row = 4; break;
            case 'f' : row = 5; break;
            case 'g' : row = 6; break;
            case 'h' : row = 7; break;
            case 'i' : row = 8; break;
            case 'j' : row = 9; break;
        }
        while ( row > max || row < 0) {
            char letter [10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
            cout << name << " must begin at a row between a and " << letter[max] << ".\n";
            cout << "Please enter the row it will be in: ";
            cin >> input;
            switch (input) {
                case 'a' : row = 0; break;
                case 'b' : row = 1; break;
                case 'c' : row = 2; break;
                case 'd' : row = 3; break;
                case 'e' : row = 4; break;
                case 'f' : row = 5; break;
                case 'g' : row = 6; break;
                case 'h' : row = 7; break;
                case 'i' : row = 8; break;
                case 'j' : row = 9; break;
            }
        }
        //adds ship
        int index = 1;
        game [row][column][i] = 2;
        game [row][column][j] = ship;
        while (index < ship) {
            game [row+index][column][i] = 3;
            game [row+index][column][j] = ship;
            index++;
        }
        game [row+index][column][i] = 4;
        game [row+index][column][j] = ship;
    }
    
    display(i, player);
    return;
}

void move(int i, int j, int k, string player) {
    int row = 10, column = 10, win [2];
    char input;
    cout << "Please enter which row to strike: ";
    cin >> input;
    switch (input) {
        case 'a' :
            row = 0;
            break;
        case 'b' :
            row = 1;
            break;
        case 'c' :
            row = 2;
            break;
        case 'd' :
            row = 3;
            break;
        case 'e' :
            row = 4;
            break;
        case 'f' :
            row = 5;
            break;
        case 'g' :
            row = 6;
            break;
        case 'h' :
            row = 7;
            break;
        case 'i' :
            row = 8;
            break;
        case 'j' :
            row = 9;
            break;
    }
    while (row > 9 || row < 0) {
        cout << "Row must be between a and j.\n";
        cout << "Please enter which row to strike: "; cin >> input;
        switch (input) {
            case 'a' :
                row = 0;
                break;
            case 'b' :
                row = 1;
                break;
            case 'c' :
                row = 2;
                break;
            case 'd' :
                row = 3;
                break;
            case 'e' :
                row = 4;
                break;
            case 'f' :
                row = 5;
                break;
            case 'g' :
                row = 6;
                break;
            case 'h' :
                row = 7;
                break;
            case 'i' :
                row = 8;
                break;
            case 'j' :
                row = 9;
                break;
        }
    }
    cout << "Please enter which column to strike: ";
    cin >> column;
    while (column > 9 || column < 0) {
        cout << "Column must be between 0 and 9.\n";
        cout << "Please enter which column to strike: "; cin >> column;
    }
    if (game [row][column][j] == 0) {
        game [row][column][k] = 7;
        display(k, player);
        cout << "Miss!\n";
    }
    if (game [row][column][j] == 1) {
        game [row][column][i] = 6;
        game [row][column][k] = 6;
        display(k, player);
    }
    if (game [row][column][j] == 2) {
        game [row][column][i] = 6;
        game [row][column][k] = 6;
        display(k, player);
    }
    if (game [row][column][j] == 3) {
        game [row][column][i] = 6;
        game [row][column][k] = 6;
        display(k, player);
    }
    if (game [row][column][j] == 4) {
        game [row][column][i] = 6;
        game [row][column][k] = 6;
        display(k, player);
    }
}

int main() {/*
    WINDOW *my_win;
    int startx, starty, width, height;
    int ch;
    
    initscr();
    cbreak();
    
    keypad(stdscr, TRUE);
    
    height = 10;
    width = 10;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;
    refresh();
    my_win = create_newwin(height, width, starty, startx);
    */
    string player;
    string boat [5] = { "Aircraft Carrier", "Battleship", "Cruiser", "Destroyer", "Destroyer" };
    display(0, "p1");
    for (int i = 0; i < 5; i++) add(0,1,4-i,5,boat[i], "p1");
    cout << "Press enter to clear screan for player 2: ";
    cin.ignore();
    cin.get();
    system("clear");
    display(3, "p2");
    while (1) {
        for (int i = 0; i < 100; i++) {
            if (i%2 == 0) {
                display(0, player);
                int board;
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "Press 1 to view your board: ";
                cin >> board;
                if (board == 1) display(0, "p1");
                cout << "Press 2 to view your enemies board: ";
                cin >> board;
                if (board == 2) display(5, "p1");
                move(3,4,5, "p2");
                cout << "Press enter to continue";
                cin.get();
                cin.get();
            }
            if (i%2 == 1) {
                int board;
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "Press 1 to view your board: ";
                cin >> board;
                if (board == 1) display(3, "p2");
                cout << "Press 2 to view your enemies board: ";
                cin >> board;
                if (board == 2) display(2, "p2");
                move(0,1,2, "p2");
                cout << "Press enter to continue";
                cin.get();
                cin.get();
            }
        }
    }
}

