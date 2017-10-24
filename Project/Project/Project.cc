#include <iostream>
#include <string.h>
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
int Winner() {
	int winner = 0;
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			if (board[i][j] == board[i][j + 1]) {
				winner++;
			}
		}
	}
}



int main() {
	int hold = 1;
	Player p1,p2;
	FillBoard();
	p1.setName();
	p2.setName();
	while (hold == 1) {
		p1.setColumn();
		//Display
		DisplayBoard();
		p2.setColumn();
		//Display
		DisplayBoard();
		//check winner function
		hold = 4;
	}
	
}