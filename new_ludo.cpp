#include <iomanip>
#include <iostream>
#include <string>
#include <ctime> 

//ANSII ESCAPE CODES -> FOR BOARD COLORING
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define WHITE "\x1B[37m"
using namespace std;

// ------------------------------
// Class Declarations
// ------------------------------

class ludo_grid_val { 
private: 
  string color, value; //Holds color and value assigned (player's token: state and content )

public:
  ludo_grid_val(){}; //constructor -> intialized by default strings 
  string get_color() { return color; } //getter method that checks the color of cell without modification
  string get_value() { return value; } //getter method that checks what is occupying the cell  
  void change_grid_val(string c, string v = "  ") { //updating cell states as player's move around
    color = c;
    value = v;
  };
  void change_grid_color(string c) { color = c; }; //updating the grid's color 
};

//represents the Board
class Board {
private:
  ludo_grid_val **g_val; //2D dynamically allocated array. Game board where all the cell's are stored 
  int ludo_track[90][2]; //specific track is 60 = 7 dots x 8 white tracks = 56 + 4 individual dots = 60
  string path_symbol; //symbol for the pathway on the board 
  string *player_token_symbol; //dynamic array storing the symbol for each player's token
  int color_code[4]; //dynamic array giving each player to specific color code 
  int rw, gw, yw, bw; //counters for how many wins for each player 
  int size; //size of board 

public:
  Board(); //constructor that intialized the components and initial state of board 
  void set_board(); // sets up entire board 
  void set_color_box(); //colors specific areas of the board 
  void dispaly_board(); //prints out the board 
  int get_color_code(string c); //retrieves numeric codes assosciated with the colored strings 
  string get_player_token_symbol(int i); //gets players token symbol
  string get_path_symbol(); //gets symbols on the board 
  void set_start_box(int r, int c, string co); //returns the symbol 
  string get_ludo_track_value(int i, int j); //checks where the value could be empty space/path symbol/player token symbol
  string get_ludo_track_color(int i, int j); //returns the color of the cell 
  void set_grid_val(int r, int c, string co, string v);
  void set_grid_color(int r, int c, string co); //changes the color of a specific cell in grid to mark paths
  void setLudo_track(); //sets up path for tokens to move(safe zones, start, and end points)
  int get_track_row_position(int tp); //returns row index for certain track position 
  int get_track_col_position(int tp);  //returns column index for certain column poisiotn 
  //increments win counts for each player 
  void add_red_win(); 
  void add_green_win();
  void add_yellow_win();
  void add_blue_win();
  //gets number of wins to check the progress of each player 
  int get_blue_win();
  int get_red_win();
  int get_yellow_win();
  int get_green_win();
};

//represents ludo token
class Ludo_Token {
private:
  int r, c; //row and column for token's position on the board 
  string color; //color of token
  string token_no, token_status; // number and status of token
  int track_position; //position on game track 

public:
  Ludo_Token(); //Default construcotr 
  void set_Ludo_Token(int r, int c, string st, string co, string token); //sets intial properties of token
  string get_token_no(); //returns token number 
  void move_ludo_token(int step, Board &b); //moves token by specified number of steps 
  void move_token_to_win(int step, Board &b); //move token to winning square
  void set_status(string status, string co, Board &b); //updates based on status 
  string get_status();// returns the current status 
  void print(); //print token's details 
  void open_token(Board &b); //opens token for playing the game 
};

//represents player 
class Player {
private:
  string name; //player's name
  int player_no; //player's number 
  Ludo_Token t_list[4]; //array of tokens for each player (4 tokens each)
  string color; //color associated with each player 

public:
  Player(); //Default constructor 
  Player(string name, string c, int player_no, Board &b);// Constructor that initializes the following attributes for player
  void set_token_on_board(int tn, Board &b);// places token on board 
  void roll_dice(); //simulates rolling dice 
  void print_det(); //prints player's details 
  string get_name(); //returns player's name 
  string get_color(); //returns player's color 
  Ludo_Token get_token(int i); //returns specific token owned by each player 
  string get_token_status(int i); //returns status of specific token 
  string get_token_no(int i); //returns token number of specified token 
  void open_token(int t, Board &b); //opens a specified token 
  void move_token(int t, int step, Board &b); //moves a specified token a number of steps 
};

// ------------------------------
// Member Functions of Classes
// ------------------------------

// member functions of class board
string Board::get_path_symbol() { return path_symbol; }

void Board::set_grid_color(int r, int c, string co) {
  g_val[r][c].change_grid_color(co);
}

string Board::get_ludo_track_color(int i, int j) {
  return g_val[i][j].get_color();
}
string Board::get_ludo_track_value(int i, int j) {
  return g_val[i][j].get_value();
}

int Board::get_track_row_position(int tp) { return (ludo_track[tp][0]); }

int Board::get_track_col_position(int tp) { return (ludo_track[tp][1]); }

string Board::get_player_token_symbol(int p) { return player_token_symbol[p]; }

void Board::set_grid_val(int r, int c, string co, string v) {
  g_val[r][c].change_grid_val(co, v);
}
void Board::add_red_win() { rw++; }
void Board::add_green_win() { gw++; }
void Board::add_yellow_win() { yw++; }
void Board::add_blue_win() { bw++; }
int Board::get_red_win() { return rw; }
int Board::get_green_win() { return gw; }
int Board::get_yellow_win() { return yw; }
int Board::get_blue_win() { return bw; }

Board::Board() {
  size = 35; // 35 x 35 board -> counting all edges and cells 
  g_val = new ludo_grid_val *[size]; //dynamically allocated array  to store info about each cell 
  for (int i = 0; i < size; i++) { 
    g_val[i] = new ludo_grid_val[size];
  }
  path_symbol = " ● "; 
  
 // player_token_symbol = new string[]{" ❶ ", " ❷ ", " ❸ ", " ❹ "}; //dynamic array for path symbols
  player_token_symbol = new string[4];
  player_token_symbol[0]=" ❶ ";
  player_token_symbol[1]=" ❷ ";
  player_token_symbol[2]=" ❸ ";
  player_token_symbol[3]=" ❹ ";
  
  for (int i=0;i<4;i++)
   {color_code[i] = i+1; }//integers to map to specific color of player
  //initializing all counters to zero 
  rw = 0;
  gw = 0;
  yw = 0;
  bw = 0;
}

//Creates colored home boxes and start colored boxes for each player of different colors  
void Board::set_color_box() {
  for (int i = 6; i <= 10; i++)
    for (int j = 6; j <= 10; j++) {
      g_val[i][j].change_grid_color(RED);
    }
  for (int i = 6; i <= 10; i++)
    for (int j = size - 7; j >= 24; j--) {
      g_val[i][j].change_grid_color(GREEN);
    }
  for (int i = 24; i <= 28; i++)
    for (int j = size - 7; j >= 24; j--) {
      g_val[i][j].change_grid_color(YELLOW);
    }
  for (int i = 24; i <= 28; i++)
    for (int j = 6; j <= 10; j++) {
      g_val[i][j].change_grid_color(BLUE);
    }
  //colors individual (one) box of each color on the board for the specific column and row 
  set_start_box(14, 2, RED);
  set_start_box(2, 18, GREEN);
  set_start_box(18, 30, YELLOW);
  set_start_box(30, 14, BLUE);
}

//sets the specific area of the board for the home boxes  
void Board::set_start_box(int r, int c, string co) {
  g_val[r][c].change_grid_color(co);
  g_val[r][c + 1].change_grid_color(co);
  g_val[r][c + 2].change_grid_color(co);
  g_val[r + 1][c].change_grid_color(co);
  g_val[r + 1][c + 2].change_grid_color(co);
  g_val[r + 2][c].change_grid_color(co);
  g_val[r + 2][c + 1].change_grid_color(co);
  g_val[r + 2][c + 2].change_grid_color(co);
}

//Creates the board (grid)
void Board::set_board() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == 0) {
        if (j == 0) {
          g_val[i][j].change_grid_val(WHITE, "┌──");
        } else if (j == size - 1) {
          g_val[i][j].change_grid_val(WHITE, "──┐");
        } else if (j % 2 != 0) {
          g_val[i][j].change_grid_val(WHITE, "───");
        } else {
          g_val[i][j].change_grid_val(WHITE, "─┬─");
        }
      } else if (i == size - 1) {
        if (j == 0) {
          g_val[i][j].change_grid_val(WHITE, "└──");
        } else if (j == size - 1) {
          g_val[i][j].change_grid_val(WHITE, "──┘");
        } else if (j % 2 != 0) {
          g_val[i][j].change_grid_val(WHITE, "───");
        } else {
          g_val[i][j].change_grid_val(WHITE, "─┴─");
        }

      } else if (i % 2 == 0) {
        if (j == 0) {
          g_val[i][j].change_grid_val(WHITE, "├──");
        } else if (j == size - 1) {
          g_val[i][j].change_grid_val(WHITE, "──┤ ");
        } else if (j % 2 != 0) {
          g_val[i][j].change_grid_val(WHITE, "───");
        } else
          g_val[i][j].change_grid_val(WHITE, "─┼─");

      } else {
        if (j == 0) {
          g_val[i][j].change_grid_val(WHITE, "│  ");
        } else if (j == size - 1) {
          g_val[i][j].change_grid_val(WHITE, "  │");
        } else if (j % 2 == 0) {
          g_val[i][j].change_grid_val(WHITE, " │ ");
        } else {
          g_val[i][j].change_grid_val(WHITE, "   ");
        }
      }
    }
  }
  set_color_box();
  setLudo_track();
}

//Displays the state of the board on console 
void Board::dispaly_board() {

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << setw(3) << g_val[i][j].get_color() << g_val[i][j].get_value();
    }
    cout << "\n";
  }
}
//Mapping each player(respective to their colors) to a number 
int Board::get_color_code(string c) {
  if (c == RED)
    return 1;
  else if (c == GREEN)
    return 2;
  else if (c == YELLOW)
    return 3;
  else if (c == BLUE)
    return 4;
  return 0;
}
//Creating Ludo track 
void Board::setLudo_track() {
  int i; //loop counter 
  int k = 0; //track position counter 
  //15th Row, symbols looped (1-13) -> White 
  for (i = 1; i <= 13; i += 2) {
    ludo_track[k][0] = 15;
    ludo_track[k++][1] = i;
    g_val[15][i].change_grid_val(WHITE, path_symbol);
  }
  // 15th Column, symbols looped 13-1 backwards -> White 
  for (i = 13; i >= 1; i -= 2) {
    ludo_track[k][0] = i;
    ludo_track[k++][1] = 15;
    g_val[i][15].change_grid_val(WHITE, path_symbol);
  }
  //Individual dot on the top , row 1 and column 17 -> White 
  ludo_track[k][0] = 1;
  ludo_track[k++][1] = 17;
  g_val[1][17].change_grid_val(WHITE, path_symbol);
  //19th column, symbols looped (1-13) -> white 
  for (i = 1; i <= 13; i += 2) {
    ludo_track[k][0] = i;
    ludo_track[k++][1] = 19;
    g_val[i][19].change_grid_val(WHITE, path_symbol);
  }
  //15th column, symbols looped(21 - 33) -> White 
  for (i = 21; i <= 33; i += 2) {
    ludo_track[k][0] = 15;
    ludo_track[k++][1] = i;
    g_val[15][i].change_grid_val(WHITE, path_symbol);
  }
  //individual dot on the right, 17th row and 33 column -> white 
  ludo_track[k][0] = 17;
  ludo_track[k++][1] = 33;
  g_val[17][33].change_grid_val(WHITE, path_symbol);
  //19th row, symbols looped (21 - 33)
  for (i = 33; i >= 21; i -= 2) {
    ludo_track[k][0] = 19;
    ludo_track[k++][1] = i;
    g_val[19][i].change_grid_val(WHITE, path_symbol);
  }
  //19th column, (21-33) -> White 
  for (i = 21; i <= 33; i += 2) {
    ludo_track[k][0] = i;
    ludo_track[k++][1] = 19;
    g_val[i][19].change_grid_val(WHITE, path_symbol);
  }
  //individual dot on bottom, 17th column, 33 row 
  ludo_track[k][0] = 33;
  ludo_track[k++][1] = 17;
  g_val[33][17].change_grid_val(WHITE, path_symbol);
  //15th colum  looped (21 - 33 backwards)
  for (i = 33; i >= 21; i -= 2) {
    ludo_track[k][0] = i;
    ludo_track[k++][1] = 15;
    g_val[i][15].change_grid_val(WHITE, path_symbol);
  }
  //19th Row,  symbols looped (1-13 backwards)
  for (i = 13; i >= 1; i -= 2) {
    ludo_track[k][0] = 19;
    ludo_track[k++][1] = i;
    g_val[19][i].change_grid_val(WHITE, path_symbol);
  }
  //individual dot, 17th row and 1st column 
  ludo_track[k][0] = 17;
  ludo_track[k++][1] = 1;
  g_val[17][1].change_grid_val(WHITE, path_symbol);
  //Creating the colored tracks 
  // int c represents dots 
  // loop through 17th column, 5 dots only -> Green 
  int c = 0;
  for (int j = 3; c != 6; j = j + 2, c++) {
    g_val[j][17].change_grid_val(GREEN, path_symbol);
    ludo_track[k][0] = j;
    ludo_track[k++][1] = 17;
  }
  //Loop throuugh 17th column, 5 dots -> blue 
  c = 0;
  for (int j = size - 4; c != 6; j = j - 2, c++) {
    g_val[j][17].change_grid_val(BLUE, path_symbol);
    ludo_track[k][0] = j;
    ludo_track[k++][1] = 17;
  }
  // Loop through 17th row, 5 dots -> RED 
  c = 0;
  for (int j = 3; c != 6; j = j + 2, c++) {
    g_val[17][j].change_grid_val(RED, path_symbol);
    ludo_track[k][0] = 17;
    ludo_track[k++][1] = j;
  }
  //Loop through 17th row, 5 dots -> yellow  
  c = 0;
  for (int j = size - 4; c != 6; j = j - 2, c++) {
    g_val[17][j].change_grid_val(YELLOW, path_symbol);
    ludo_track[k][0] = 17;
    ludo_track[k++][1] = j;
  }
  //color individual dots on [r][c] and set them to their colors respectively 
  g_val[15][3].change_grid_val(RED, path_symbol);
  g_val[19][31].change_grid_val(YELLOW, path_symbol);
  g_val[3][19].change_grid_val(GREEN, path_symbol);
  g_val[31][15].change_grid_val(BLUE, path_symbol);
}
// ------------------------------
// member function of class ludo token
string Ludo_Token::get_status() { return token_status;}
string Ludo_Token::get_token_no() { return token_no; }
//default constrctor -> intialized token with default values 
Ludo_Token::Ludo_Token() {
  r = 0;
  c = 0;
  token_no = " ";
  token_status = "";
}
//methods to set the details of ludo token 
void Ludo_Token::set_Ludo_Token(int row, int col, string st, string co, string tn) {
  r = row;
  c = col;

  token_no = tn;
  token_status = st;
  color = co;
}
//print details of ludo token 
void Ludo_Token::print() {
  cout << "Token Detalis: " << endl;
  cout << "Token No: " << token_no << endl;
  cout << "Token Status: " << token_status;
  cout << "Token Position: " << r << "   " << c << endl;
}
//set status of ludo token on board and its position 
void Ludo_Token::set_status(string s, string co, Board &b) {
  token_status = s;
  if (s == "win") { //when the token reaches the winning position
    b.set_grid_val(r, c, WHITE, b.get_path_symbol()); //then depending on color -> move the token to winning track pos
    if (color == RED) {
      b.set_grid_val(1, b.get_red_win() * 2 + 1, color, token_no);
      b.add_red_win();
    }
    if (color == GREEN) {
      b.set_grid_val(1, b.get_green_win() * 2 + 1 + 20, color, token_no);
      b.add_green_win();
    }
    if (color == BLUE) {
      b.set_grid_val(33, b.get_blue_win() * 2 + 1, color, token_no);
      b.add_blue_win();
    }
    if (color == YELLOW) {
      b.set_grid_val(33, b.get_yellow_win() * 2 + 1 + 20, color, token_no);
      b.add_yellow_win();
    }
    cout << "token details: " << color << token_no << " " << token_status << " "  //print details after moving it
         << color << "  " << endl;
  } else if (s == "home") { //if the token is in its open position
    track_position = 0;
    if (co == RED && token_no == " ❶ ") { //set the following red tokens in their home position (row and col)
      r = 7, c = 7;
    }
    if (co == RED && token_no == " ❷ ") {
      r = 7, c = 9;
    }
    if (co == RED && token_no == " ❸ ") {
      r = 9, c = 7;
    }
    if (co == RED && token_no == " ❹ ") {
      r = 9, c = 9;
    }
  //set the following green tokens in their home position (row and col)
    if (co == GREEN && token_no == " ❶ ") {
      r = 7, c = 25;
    }
    if (co == GREEN && token_no == " ❷ ") {
      r = 7, c = 27;
    }
    if (co == GREEN && token_no == " ❸ ") {
      r = 9, c = 25;
    }
    if (co == GREEN && token_no == " ❹ ") {
      r = 9, c = 27;
    }
  //set the following blue tokens in their home position (row and col)
    if (co == BLUE && token_no == " ❶ ") {
      r = 25, c = 7;
    }
    if (co == BLUE && token_no == " ❷ ") {
      r = 25, c = 9;
    }
    if (co == BLUE && token_no == " ❸ ") {
      r = 27, c = 7;
    }
    if (co == BLUE && token_no == " ❹ ") {
      r = 27, c = 9;
    }
    //set the following yellow tokens in their home position (row and col)
    if (co == YELLOW && token_no == " ❶ ") {
      r = 25, c = 25;
    }
    if (co == YELLOW && token_no == " ❷ ") {
      r = 25, c = 27;
    }
    if (co == YELLOW && token_no == " ❸ ") {
      r = 27, c = 25;
    }
    if (co == YELLOW && token_no == " ❹ ") {
      r = 27, c = 27;
    }
  }
  else if (s == "open") { // open -> the individual colored dots  
    track_position = 0;
    b.set_grid_val(r, c, co, "   "); // set the grid value to show empty space at the current token position
    if (co == RED) {
      r = 15, c = 3; //new position for a red token
    }
    if (co == GREEN) {
      r = 3, c = 19; //new position for a green token
    }
    if (co == YELLOW) {
      r = 19, c = 31; //new position for a yellow token
    }
    if (co == BLUE) {
      r = 31, c = 15; //new position for a blue token 
    }
    b.set_grid_val(r, c, co, token_no); //set the grid value to show the token at its new position

  } 
}

void Ludo_Token::move_token_to_win(int step, Board &b) {
  cout << "token " << color << token_no << "on winning track checking "
       << token_status << endl; //print token details and status 
  int co = b.get_color_code(color), upper_limit = 0; //get the color code of the token's color
  switch (co) {
  case 1:
    upper_limit = 77; //Red
    break;
  case 2:
    upper_limit = 65;//Green
    break;
  case 3:
    upper_limit = 83;//Yellow
    break;
  case 4:
    upper_limit = 71;//Blue
    break;
  }
  //check if the token can move to the win position
  if (track_position + step - 1 > upper_limit)
    cout << " cant move " << token_no << endl;
  else if (track_position + step - 1 == upper_limit) {
  //If the token reaches the win position, update status to "win"
    cout << token_no << " win" << endl;
    set_status("win", color, b);
    b.set_grid_val(r, c, color, b.get_path_symbol());

  } else if (track_position + step - 1 < upper_limit) {
    // move the token along the winning track
    // update grid values to show the token's movement
    b.set_grid_val(r, c, color, b.get_path_symbol());
    r = b.get_track_row_position(track_position + step);
    c = b.get_track_col_position(track_position + step);
    track_position += step;
    cout << " new r" << r << "  c" << c << "track position" << track_position
         << endl;
    b.set_grid_val(r, c, color, token_no);
  }
}

void Ludo_Token::move_ludo_token(int step, Board &b) {
  if (token_status == "open") { //checking if the token is open for movement
    if (track_position + step > 58 + 7) //58(white dots to move + 6 on winning track + 1 to win)
      cout << "cant move" << color << token_no << endl;
    else if (track_position + step == 58 + 7) { //checking if the token will reach the winning position
      set_status("win", color, b); //set the status to "win" if the token reaches the end
    } 
    else if (track_position + step > 58 and track_position + step < 58 + 7) { //update the grid to show the token moving from the track to the winning track
      b.set_grid_val(r, c, WHITE, b.get_path_symbol()); //set the current position to empty
      //set the color of the pathway to the player's color
      if (r == 15 and c == 3) 
        b.set_grid_color(r, c, RED);
      if (r == 3 and c == 19)
        b.set_grid_color(r, c, GREEN);
      if (r == 31 and c == 3)
        b.set_grid_color(r, c, BLUE);
      if (r == 31 and c == 19)
        b.set_grid_color(r, c, YELLOW);
      //Update the track position
      track_position = track_position + step - 58 - 1;
      //move the token along the winning track based on the color
      if (color == RED) {
        r = b.get_track_row_position(track_position + 72); //Red -> 72 to 77
        c = b.get_track_col_position(track_position + 72);
        track_position += 72;
      } else if (color == GREEN) {
        r = b.get_track_row_position(track_position + 60); // Green -> 60 to 65 
        c = b.get_track_col_position(track_position + 60);
        track_position += 60;
      } else if (color == YELLOW) {
        r = b.get_track_row_position(track_position + 78); // Yellow -> 78 to 83
        c = b.get_track_col_position(track_position + 78);
        track_position = track_position + 78;

      } else if (color == BLUE) {
        r = b.get_track_row_position(track_position + 66); // Blue -> 66 to 71
        c = b.get_track_col_position(track_position + 66);
        track_position += 66;
      }
      //update the status to winning track, set the new position of the token on the winning track
      set_status("winning track", color, b);
      b.set_grid_val(r, c, color, token_no);
    } else {
      cout << "move :" << step << "   " << token_no << endl;
      b.set_grid_val(r, c, WHITE, b.get_path_symbol());
      if (r == 15 and c == 3)
        b.set_grid_color(r, c, RED);
      if (r == 3 and c == 19)
        b.set_grid_color(r, c, GREEN);
      if (r == 31 and c == 15)
        b.set_grid_color(r, c, BLUE);
      if (r == 19 and c == 31)
        b.set_grid_color(r, c, YELLOW);

      track_position += step;
      if (color == RED) {
        r = b.get_track_row_position(track_position + 1); //
        c = b.get_track_col_position(track_position + 1);
      }
      if (color == GREEN) {

        r = b.get_track_row_position((track_position + 16) % 60); //
        c = b.get_track_col_position((track_position + 16) % 60);
      }
      if (color == YELLOW) {

        r = b.get_track_row_position((track_position + 31) % 60); //
        c = b.get_track_col_position((track_position + 31) % 60);
      }
      if (color == BLUE) {

        r = b.get_track_row_position((track_position + 46) % 60); //
        c = b.get_track_col_position((track_position + 46) % 60);
      }
      b.set_grid_val(r, c, color, token_no);
    }
  }
}
void Ludo_Token::open_token(Board &b) {
  b.set_grid_val(r, c, color, token_no);
  token_status = "open";
}
// ------------------------------
// Member function of class player
Ludo_Token Player::get_token(int i) { return t_list[i]; }
string Player::get_token_no(int i) { return t_list[i].get_token_no(); }
string Player::get_token_status(int i) { return t_list[i].get_status(); }
string Player::get_color() { return color; }
string Player::get_name() { return name; }

//Constructor for player class (non paramaterized)
Player::Player() {
  //Initialize player attributes
  name = " ";
  color = " ";
  player_no = 0;
}

//constructor: parametrized 
Player::Player(string n, string co, int pn, Board &b) {
  //Initialize player attributes
  name = n;
  color = co;
  player_no = pn;
  string token_code[] = {
      b.get_player_token_symbol(0), b.get_player_token_symbol(1),
      b.get_player_token_symbol(2), b.get_player_token_symbol(3)}; //Array to hold token symbols for each player
      int c = b.get_color_code(co); //Get the color code for the player's color
  switch (c) {
  case 1: //For RED player
    t_list[0].set_Ludo_Token(7, 7, "home", RED, token_code[0]);
    t_list[1].set_Ludo_Token(7, 9, "home", RED, token_code[1]);  //Set token positions and statuses for RED player
    t_list[2].set_Ludo_Token(9, 7, "home", RED, token_code[2]);
    t_list[3].set_Ludo_Token(9, 9, "home", RED, token_code[3]);

    b.set_grid_val(7, 7, RED, token_code[0]);
    b.set_grid_val(7, 9, RED, token_code[1]);  //Update board grid with token positions for RED player
    b.set_grid_val(9, 7, RED, token_code[2]);
    b.set_grid_val(9, 9, RED, token_code[3]);
    break;
  case 2: //For GREEN player
    t_list[0].set_Ludo_Token(7, 25, "home", GREEN, token_code[0]);
    t_list[1].set_Ludo_Token(7, 27, "home", GREEN, token_code[1]);  
    t_list[2].set_Ludo_Token(9, 25, "home", GREEN, token_code[2]); //Set token positions and statuses for GREEN player
    t_list[3].set_Ludo_Token(9, 27, "home", GREEN, token_code[3]);

    b.set_grid_val(7, 25, GREEN, token_code[0]);
    b.set_grid_val(7, 27, GREEN, token_code[1]);  //Update board grid with token positions for GREEN player
    b.set_grid_val(9, 25, GREEN, token_code[2]);
    b.set_grid_val(9, 27, GREEN, token_code[3]);
    break;
  case 3:  // For YELLOW player
    t_list[0].set_Ludo_Token(25, 25, "home", YELLOW, token_code[0]);
    t_list[1].set_Ludo_Token(25, 27, "home", YELLOW, token_code[1]); 
    t_list[2].set_Ludo_Token(27, 25, "home", YELLOW, token_code[2]); //Set token positions and statuses for YELLOW player
    t_list[3].set_Ludo_Token(27, 27, "home", YELLOW, token_code[3]);

    b.set_grid_val(25, 25, YELLOW, token_code[0]);
    b.set_grid_val(25, 27, YELLOW, token_code[1]);
    b.set_grid_val(27, 25, YELLOW, token_code[2]);  //Update board grid with token positions for YELLOW player
    b.set_grid_val(27, 27, YELLOW, token_code[3]);

    break;
  case 4: //For BLUE player
    t_list[0].set_Ludo_Token(25, 7, "home", BLUE, token_code[0]);
    t_list[1].set_Ludo_Token(25, 9, "home", BLUE, token_code[1]);
    t_list[2].set_Ludo_Token(27, 7, "home", BLUE, token_code[2]); //Set token positions and statuses for BLUE player
    t_list[3].set_Ludo_Token(27, 9, "home", BLUE, token_code[3]);

    b.set_grid_val(25, 7, BLUE, token_code[0]);
    b.set_grid_val(25, 9, BLUE, token_code[1]); 
    b.set_grid_val(27, 7, BLUE, token_code[2]);   //Update board grid with token positions for BLUE player
    b.set_grid_val(27, 9, BLUE, token_code[3]);
    cout << "Player " << player_no << " token " << co << token_code[0]
         << token_code[1] << token_code[2] << token_code[3] << endl; //Print player and token details for BLUE player
    break;
  }
}
//prints the details of the player (name, color, and player_no) as well as the token's details(tok number, position
// and status)
void Player::print_det() {
  cout << "Player details" << endl;
  cout << name << endl;
  cout << color << endl;
  cout << player_no << endl;
  for (int i = 0; i < 4; i++) {
    t_list[i].print();
  }
}
//checks if the status is open/winning track and facilitates movement 
void Player::move_token(int t, int step, Board &b) {
  cout << "moving token " << t << "status" << t_list[t].get_status() << endl;
  if (t_list[t].get_status() == "open")
    t_list[t].move_ludo_token(step, b);
  else if (t_list[t].get_status() == "winning track") {
    cout << "winning track " << endl;
    t_list[t].move_token_to_win(step, b);
  }
}
//opens a token for play by moving it from home position to the game board   
void Player::open_token(int t, Board &b) {
  if (t_list[t].get_status() == "home") {
    t_list[t].set_status("open", color, b);
    t_list[t].open_token(b);
  }
}
// ------------------------------
// Main function 
// ------------------------------
int main() 
{
  cout << "Welcome to Ludo!\n";
  string color_list[] = {RED, GREEN, YELLOW, BLUE}; //array of colors for players
  int n; //n: number of players 
  Board b = Board(); //create a new board
  srand(time(nullptr)); //seed the random number generator
  do { //asking for the number of players (2-4) until user inputs correctly
    cout << "Enter number of players (2-4 ): "; 
    cin >> n;
  } while (n < 2 or n > 4);
  string na; //na: player name variable
  b.set_board(); //initalizes the board
  Player *player_list = new Player[n]; //create an array of players 
  int cl=0; //variable for color 
  for (int i = 0 ;i < n; i++) { //initialize players
    cout << "Enter player name: ";
    cin >> na;
    player_list[i] = Player(na, color_list[cl], i + 1, b); //create a player with name, color, number, and board
    if (n == 2)
      cl++;
    cl++;
  }
  int pn = 0; //variable for player number 
  b.dispaly_board(); //display the board
  do {  //main game loop
    int tn = 0, dn = 0, otoken = 0, wttoken = 0, notplayed; //token number, dice number, open token, win token, and not player 
    char ch; //choice variable 
    cout << player_list[pn].get_color() << "Player Name: " << player_list[pn].get_name() <<endl; //display player info 
    for (int i = 0; i < 4; i++) { //display token information and count the number of tokens in open and winning track states
      player_list[pn].get_token(i).print();
      if (player_list[pn].get_token_status(i) == "open")
        otoken++;
      if (player_list[pn].get_token_status(i) == "winning track")
        wttoken++;
    }
    dn = rand() % 6 + 1; //roll the dice

    cout << "Dice rolled you got:  " << dn << endl; //gives the dice roll number 
    //sets the game rules 
    notplayed = 0; 
    if (dn == 6) { //if the dice roll is equal to six, the player is able to move their token 
      cout << "want to open a token or move token  (o/p): ";
      cin >> ch; 
      if (ch == 'o') { 
        do {
          cout << "Enter Token number to open (1-4): ";
          cin >> tn;
        } while (tn < 1 or tn > 4); //keeps asking until the player inputs correct number (1-4) of 
        player_list[pn].open_token(tn - 1, b); //opens the selcted token and has one less token now 
        notplayed = 1; //mark that a token was opened
      }
    }
    if ((otoken >= 1 or wttoken >= 1) and notplayed == 0) { //check if there is at least one open or winning track token and no token was opened in this turn
      do {
        cout << "Enter token number to move: ( 1-4) :"; //asks user which token numbet to move 
        cin >> tn;
      } while (tn > 4 or tn < 1); //user validation
      player_list[pn].move_token(tn - 1, dn, b); //move the selected token
    } else
      cout << "Dont have open token to move" << endl;
    b.dispaly_board(); //display the updated board after the player's turn
    cout<<"Press enter key to continue........"; //pause the game and wait for the player to press enter to continue
    int c; 
    while ((c = cin.get()) != '\n' && c != EOF); //Cited on Report 
    cin.ignore();
    cin.get();
  
    pn = (pn + 1) % n; //increment to  next player in a circular manner to make sure it stays within the range of players
  } while (b.get_red_win() != 4 and b.get_blue_win() != 4 and
           b.get_green_win() != 4 and b.get_yellow_win() != 4);
  //display the winner if they got all four tokens to win 
  if (b.get_red_win() == 4)
    cout << player_list[0].get_color() << player_list[0].get_name()
         << " Red player won the game";
  else if (b.get_blue_win() == 4)
    cout << player_list[3].get_color() << player_list[3].get_name()
         << "Blue player won the game";
  else if (b.get_green_win() == 4)
    cout << player_list[1].get_color() << player_list[1].get_name()
         << "Green player won the game";
  else if (b.get_yellow_win() == 4)
    cout << player_list[2].get_color() << player_list[2].get_name()
         << "Yellow player won the game";
}

