#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <climits>
#include<unistd.h>
#include <fstream>

using namespace std;

char board[8][8];

class Game
{
public:
	Game() { cout << "Player has been initiated" << endl; }
	//    virtual ~Game() { cout << "A Game was Destroyed" << endl; }
	void setName() {
		static int counter = 1;
		cout << "\nWhat is your name Player" << counter << ":?" << endl;
		cin >> name;
		counter++;
	}
protected:
	string name;
};



class Player :public Game
{
public:
	void setColumn();
	bool CheckDrop(int columnNumber, char player);
	void DisplayFinalBoardToFile(int player);

	Player operator+(const Player &);
	friend ostream& operator<<(ostream &os, const Player&);
protected:
	int column;
};


Player Player::operator+(const Player &p)
{
	Player sum;
	sum.name = name + " and " + p.name + " were the players of this game.\n";
	return sum;
}


ostream& operator<<(ostream &os, const Player &result)
{
	os << result.name;
	return os;
}

class Board :public Player {
private:

public:
	void FillBoard();
	void DisplayBoard();
	int Winner(int);
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
		cout << name << ", What column would you like to place the token in?" << endl;
		cin >> column;

		if (cin.fail())
		{
			cout << "Letters are not valid. ";
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
	// Implementation of the try function that would catch an invalid column that is outside game bounds
	try
	{
		// if statement to verify that the column bounds are not exceed. If they are, catch and return a 'false'
		if ((columnNumber >= 8) || (columnNumber <= 0))
			throw columnNumber;
	}
	catch (int columnNumber)
	{
		cout << "out of bound; please try again" << endl;
		return false;
	}

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
			cout << "|_" << board[i][j] << "_|";
		cout << endl;
	}
}



void Player::DisplayFinalBoardToFile(int player)
{
	ofstream myfile;
	myfile.open("Connect4.txt");
	myfile << "The following is the result of this game:\n\n";
	myfile << "  1    2    3    4    5    6    7\n";
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 1; j <= 7; j++)
			myfile << "|_" << board[i][j] << "_|";
		myfile << "\n";
	}
	if (player == 1)
		myfile << "\n" << name << " (x) has won!\n";
	else if (player == 2)
		myfile << "\n" << name << " (o) has won!\n";
	else
		myfile << "\nNo one has won\n";
	//cout << <<end;
	myfile.close();

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
	//int x = 6;
	//r = r - x;
	if ((board[r][c] == board[r + 1][c + 1]) && (board[r][c] == board[r + 2][c + 2]) && (board[r][c] == board[r + 3][c + 3]) && (board[r][c] != '_')){
		return true;
	}
	else{
		//x--;
		return false;
	}


}
int Winner(int player) {
	bool winner;

	for (int i = 7; i >= 1; i--) {
		for (int j = 1; j <= 7; j++) {
			winner = UpDiagonal(i, j);
			if (winner == true){
				return player;
			}
			winner = DownDiagonal(i, j);
			if (winner == true){
				return player;
			}
			winner = Vertical(i, j);
			if (winner == true){
				return player;
			}
			winner = Horizontal(i, j);
			if (winner == true){
				return player;
			}

		}
	}
	return 0;

}



int main() {
	int result = 0, hold = 0;
	Player p1, p2;
	FillBoard();
	p1.setName();
	p2.setName();
	DisplayBoard();
	while (result == 0) {
		hold++;
		p1.setColumn();
		//Display
		DisplayBoard();
		//Winner Checking to see if player 1 has won
		result = Winner(1);
		if (result == 1)
		{
			cout << "Player 1 has won!" << endl;
			p1.DisplayFinalBoardToFile(1);
			break;
		}
		p2.setColumn();
		//Display
		DisplayBoard();
		//Winner Checking to see if player 2 has won
		result = Winner(2);
		if (result == 2)
		{
			cout << "Player 2 has won!" << endl;
			p2.DisplayFinalBoardToFile(2);
			break;
		}
		// if no one has won, end the game
		if (hold >= 49) {
			cout << "No winner" << endl;
			break;
		}
	}
	cout << p1 + p2;
}


// BUG: When player inputs an out of bound number than a letter, things will break.






