#include <iostream>
#include <stdlib.h> // for srand, rand
#include <time.h> // for time
#include <iomanip>
using namespace std;

// function for no duplicate numbers
bool noDuplicates(int num, int check[], int size){
	for(int i=0;i<size;i++)
		if(num==check[i]) return false;
	return true;
}

// function to check if bingo or not
bool bingo(int board[]){
  for(int i=0; i<25; i+=5){
    if(board[i]==board[i+1] && board[i]==board[i+2] && board[i]==board[i+3] && board[i]==board[i+4])
      return true;
  }
  for(int i=0; i<5; i++){
    if(board[i]==board[i+5] && board[i]==board[i+10] && board[i]==board[i+15] && board[i]==board[i+20])
      return true;
  }
  if(board[0]==board[6] && board[0]==board[12] && board[0]==board[18] && board[0]==board[24])
    return true;
  if(board[4]==board[8] && board[0]==board[12] && board[0]==board[16] && board[0]==board[20])
    return true;
  if(board[0]==board[4] && board[0]==board[20] && board[0]==board[24])
    return true;
  return false;
}

// function to generate random number
int generateNumber(int size, int numbers[]){
  int n = rand()%30 +10;
  if(noDuplicates(n,numbers,30))
    return n;
  return generateNumber(size, numbers);
}

// function to change number to 0 if matched
void strikeNumber(int n,int (&board)[25]){
  for(int i=0; i<25; i++){
    if(board[i]==n){
      board[i] = 0;
    }
  }
}


// function for asking numbers from user
void askNumber(int (&board)[25]){
  int n;
  cout << "Enter 24 number between 10-40:" << endl;
  for(int i=0; i<25; i++){
    if(i==12){
      board[i] = 0;
    }
    else{
      cout << "Enter the "<< i+1 <<" number: ";
      cin >> n;
      if(noDuplicates(n, board,25) && 10<=n && n<=40){
        board[i] = n;
      }
      else{
        cout << "Re-enter.\n";
        --i;
      }
    }
  }
}

// function to display board of player
void displayBoard(int (&board)[25]){
  cout << "  B     I     N     G     O  " << endl;
  cout << "_____|_____|_____|_____|_____" << endl;
  cout<<endl<<"     |     |     |     |     " << endl;
  for(int i=0;i<25;i++){
    cout << setw(3) << board[i];
    cout << "  |";
    if((i+1)%5==0 && i+1<25){
      cout<<endl<<"     |     |     |     |     "<<endl;
      cout << "_____|_____|_____|_____|_____" << endl;
      cout<<endl<<"     |     |     |     |     "<<endl;
    }
  }
  cout<<endl<<"     |     |     |     |"<<endl;
}

// main function
int main() {
  srand (time(NULL)); // declaring srand time
  // declaring arrays and integer variables
  int player1[25];
  int player2[25];
  int bingoNumbers[30];
  int n, p1, p2;

  // asking user input
  cout << "Player 1:" << endl;
  askNumber(player1);
  cout << "Player 2:" << endl;
  askNumber(player2);

  // displaying board
  cout << "Player 1 Board: " << endl;
  displayBoard(player1);
  cout << endl;
  cout << "Player 2 Board: " << endl;
  displayBoard(player2);

  // generating number
  for(int i=0;i<30;i++){
    int num = generateNumber(i, bingoNumbers);
    bingoNumbers[i] = num;
    cout << "The Bingo number is: " << num << endl;
    strikeNumber(num, player1);
    strikeNumber(num, player2);
    // if player1 board is bingo
    if(bingo(player1)){
      p1 = 1;
    }
    // if player2 board is bingo
    if(bingo(player2)){
      p2 = 1;
      break;
    }
  }
  // if players win then display winner
  if(p1==1 && p2==1) cout << "Both player wins.\n" << endl;
  else{
    if(p1==1) cout << "Player 1 wins.\n" << endl;
    else cout << "Player 2 wins.\n" << endl;
  }
  // displaying board after game
  cout << "Player 1 Board: " << endl;
  displayBoard(player1);
  cout << endl;
  cout << "Player 2 Board: " << endl;
  displayBoard(player2);
}
