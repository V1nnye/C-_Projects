#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const int row = 3;
const int columns = 3;
int turn = 0, moves = 0;
char player = 'X', opponent = 'O';
char screen[row][columns];

void instructions();
void clearScreen();
void printScreen();
void movePlayer();
void moveOpponent();
bool verifySpace();
bool verifyGameOver();
void verifyEnd();

int main(){
  char tecla;
  clearScreen();
  while(verifyGameOver() == false && moves != 9){
    if(turn == 0){
      instructions();
      movePlayer();
      moves++;
      system("clear");
      printScreen();
      sleep(3);
      system("clear");
      if(verifyGameOver() == true)
        break;
    } else {
      moveOpponent();
      moves++;
      printScreen();
      if(verifyGameOver() == true)
        break;
    }
  }
  verifyEnd();
  cout << "\nThaks for playing!\nBye Bye" << endl;
  sleep(5);
  return 0;
}

void instructions(){
	printf("\t\t Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered and play\n\n");
	
	printf("\t [0][0] | [0][1] | [0][2] \n");
	printf("\t--------|--------|--------\n");
	printf("\t [1][0] | [1][1] | [1][2] \n");
	printf("\t--------|--------|--------\n");
	printf("\t [2][0] | [2][1] | [2][2] \n\n");
}

void clearScreen(){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < columns; j++){
      screen[i][j] = ' ';
    }
  }
}

void printScreen(){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < columns; j++){
      cout << " " << screen[i][j] << " ";
      if(j < 2) cout << "|";
    }
    cout << endl;
    if(i < 2) cout << "---|---|---" << endl;
  }
  cout << endl;
}

bool verifySpace(int x, int y){
  if(screen[x][y] == ' '){
    return true;
  } else {
    return false;
  }
}

void movePlayer(){
  int x,y;
  bool keepTrying = true;
  cout << "Write the numbers to row and columns: " << endl;
  while(keepTrying == true){
    cin >> x >> y;
    if((x >= 3 || y >= 3) || (x < 0 || y < 0)){
        cout << "Invalid move!" << endl;
        cout << "The numbers, to X or Y, must to be zero, one or two\nTry again: " << endl;
    } else if(verifySpace(x,y) == false) {
      cout << "This space cant be used\nTry again: " << endl;
    } else {
      keepTrying = false;
    }
  }
  screen[x][y] = player;
  turn = 1;
}

void moveOpponent(){
  int x, y;
  
  srand((unsigned)time(0));
  x = rand()%(2-0+1) + 0;
  y = rand()%(2-0+1) + 0;
  while(verifySpace(x, y) == false){
    srand((unsigned)time(0));
    x = rand()%(2-0+1) + 0;
    y = rand()%(2-0+1) + 0;
  }
  screen[x][y] = opponent;
  turn = 0;
}

bool verifyGameOver(){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < columns; j++){
      if(screen[0][j] == screen[1][j] && screen[0][j] == screen[2][j] && screen[0][j] != ' '){
        //cout << "Vertical" << endl;
        return true;
      } else if(screen[i][0] == screen[i][1] && screen[i][0] == screen[i][2] && screen[i][0] != ' '){
        //cout << "Horizontal" << endl;
        return true;
      } else if(screen[0][0] == screen[1][1] && screen[1][1] == screen[2][2] && screen[0][0] != ' '){
        //cout << "Diagonal principal" << endl;
        return true;
      } else if(screen[0][2] == screen[1][1] && screen[1][1] == screen[2][0] && screen[0][2] != ' '){
        //cout << "Diagonal secundaria" << endl;
        return true;
      }
    }
  }
  return false;
}

void verifyEnd(){
if(moves == 9 && verifyGameOver() == false){
    cout << "It's a tie!" << endl;
  } else {
    if(turn == 0){
      cout << "The machine won!" << endl;
    } else if(turn == 1){
      cout << "The player won!" << endl;
    }
  }
}
