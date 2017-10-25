#include <iostream>
#include <string.h>
#include <stdbool.h>
using namespace std;

char board[8][8];

class Game
{
public:
	Game() { cout << "created" << endl; }
	~Game() { cout << "A Game was Destroyed" << endl; }
	void setName() {
		static int counter = 1;
		cout << "What is your name Player"<< counter<< ":?" << endl;
		cin >> name;
		counter++;
					}

protected:
	string name;
	

};

class Player:public Game
{
public:
	void setColumn();

protected:
	int column;
};

class Board :public Player {
private:

public:
	void FillBoard();
	void DisplayBoard();
	int Winner();
	bool UpDiagonal(int r, int c);
	bool DownDiagonal(int r, int c);
	bool Horizontal(int r, int c);
	bool Vertical(int r, int c);


};

void Player::setColumn() {
	static int count = 0;
	count++;

	//Player1
	if (count%2 != 0) {
		cout << "What column would you like to place the token in Player1 ?:" << endl;
		cin >> column;
		//if(board[row][column] == '_')
		//row--
		board[7][column] = 'x';



	}
	//Player2
	else {
		cout << "What column would you like to place the token in Player2 ?:" << endl;
		cin >> column;
		board[7][column] = 'o';


	}
}
void FillBoard()
{

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			board[i][j] = '_';
}

void DisplayBoard()
{
	cout << "  1    2    3    4    5    6    7\n";
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			//board[i][j] = '_';

			cout << "|_" << board[i][j] << "_|";
		}

		cout << endl;
	}
}
bool UpDiagonal(int r, int c){
	if (board[r][c] == board[r - 1][c + 1] == board[r - 2][c + 2] == board[r - 3][c + 3]){
		return true;
	}
	else{
		return false;
	}
}
bool Horizontal(int r, int c){
	if ((board[r][c] == board[r][c + 1]) && (board[r][c] == board[r][c + 2]) && (board[r][c] == board[r][c + 3])) {
		return true;
	}
		else{
			return false;
	}

}
bool Vertical(int r, int c){
	if (board[r][c] == board[r - 1][c] == board[r-2][c] == board[r-3][c]){
		return true;
	}
		else{
			return false;
		}
}
bool DownDiagonal(int r, int c){
	int x = 6;
	r = r - x;
	if (board[r][c] == board[r + 1][c + 1] == board[r + 2][c + 2] == board[r + 3][c + 3]){
		return true;
	}
	else{
		x--;
		return false;
	}


}
int Winner() {
	bool winner;
	for (int i = 7; i >= 1; i--) {
		for (int j = 1; j <= 7; j++) {
			winner = UpDiagonal(i, j);
			if (winner == true){
				return 1;
			}
			else if (winner == false){
				return 0;
			}
			winner = DownDiagonal(i, j);
			if (winner == true){
				return 1;
			}
			else if (winner == false){
				return 0;
			}
			winner = Vertical(i, j);
			if (winner == true){
				return 1;
			}
			else if (winner == false){
				return 0;
			}
			winner = Horizontal(i, j);
			if (winner == true){
				return 1;
			}
			else if (winner == false){
				return 0;
			}
			
		}
	}
}




int main() {
	int result,hold = 1;
	Player p1,p2;
	FillBoard();
	p1.setName();
	p2.setName();
	while (hold == 1) {
		p1.setColumn();
		//Display
		DisplayBoard();
		//Winner Checking
		result = Winner();
		cout << result << endl;
		p2.setColumn();
		//Display
		DisplayBoard();
		//check winner function
		result = Winner();
		cout << result << endl;
		//hold = 4;
	}
	
}
