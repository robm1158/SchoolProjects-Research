#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <climits>
#include<unistd.h>
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
	bool CheckDrop(int columnNumber, char player);
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
	void clearScreen();


};

void Player::setColumn()
{
	static int count = 0;
	bool state;
	count++;

	while (true)
	{
		cout << name << ", What column would you like to place the token in ?" << endl;
		cin >> column;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}

	//Player1
	if (count % 2 != 0)
	{
		// calls function CheckDrop to place token. If the drop is legal, function returns a 'true' and next player goes.
		// if the column selected is out of bound or is already full, a 'false' is returned and user is prompted to enter
		// another value until one obtained.
		state = CheckDrop(column, 'x');
		while (!state)
		{
			cin >> column;
			state = CheckDrop(column, 'x');
		}
	}
	//Player2
	else
	{
		// calls function CheckDrop to place token. If the drop is legal, function returns a 'true' and next player goes.
		// if the column selected is out of bound or is already full, a 'false' is returned and user is prompted to enter
		// another value until one obtained.
		state = CheckDrop(column, 'o');
		while (!state)
		{
			cin >> column;
			state = CheckDrop(column, 'o');
		}
	}
}
// Function that checks and places the token of each player.
bool Player::CheckDrop(int columnNumber, char player)
{
	// if statement to verify that the column bounds are not exceed. If they are, return a 'false'
	if ((columnNumber >= 1) && (columnNumber <= 7))
	{
		// if statement to verify that column still has space. If there's no space, return a 'false'
		if (board[1][columnNumber] == '_')
		{
			// for loop that starts at the bottom and checks for first available spot, once found puts token there
			for (int i = 7; i >= 1; i--)
			{
				if (board[i][columnNumber] == '_')
				{
					board[i][columnNumber] = player;
					return true;
				}
			}
		}
		else
		{
			cout << "column " << columnNumber << " is full; please try again" << endl;
			return false;
		}
	}
	else
	{
		cout << "out of bound; please try again" << endl;
		return false;
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
	if ((board[r][c] == board[r - 1][c + 1]) && (board[r][c] == board[r - 2][c + 2]) && (board[r][c] == board[r - 3][c + 3]) && (board[r][c] != '_')){
		return true;
	}
	else{
		return false;
	}
}
bool Horizontal(int r, int c){
	if ((board[r][c] == board[r][c + 1]) && (board[r][c] == board[r][c + 2]) && (board[r][c] == board[r][c + 3]) && (board[r][c] != '_')) {
		return true;
	}
		else{
			return false;
	}

}
bool Vertical(int r, int c){
	if ((board[r][c] == board[r - 1][c]) && (board[r][c] == board[r - 2][c]) && (board[r][c] == board[r - 3][c]) && (board[r][c] != '_')){
		return true;
	}
		else{
			return false;
		}
}
bool DownDiagonal(int r, int c){
	int x = 6;
	r = r - x;
	if ((board[r][c] == board[r + 1][c + 1]) && (board[r][c] == board[r + 2][c + 2]) && (board[r][c] == board[r + 3][c + 3]) && (board[r][c] != '_')){
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
			winner = DownDiagonal(i, j);
			if (winner == true){
				return 1;
			}
			winner = Vertical(i, j);
			if (winner == true){
				return 1;
			}
			winner = Horizontal(i, j);
			if (winner == true){
				return 1;
			}
			
		}
		return 0;
	}
	
}
void clearScreen(){
	sleep(5);
	cout <<"\e[2J\e[H";
}



int main() {
	int result = 0,hold = 0;
	Player p1,p2;
	FillBoard();
	p1.setName();
	p2.setName();
	while (result == 0) {
		hold++;
		p1.setColumn();
		//Display
		DisplayBoard();
		//Winner Checking
		result = Winner();
		cout << result << endl;
		//clearScreen();
		p2.setColumn();
		//Display
		DisplayBoard();
		//check winner function
		result = Winner();
		cout << result << endl;
		clearScreen();
		if (hold >= 49) {
			cout << "No winner" << endl;
			break;
		}
	}
	
}
