// 12BEADS GAME
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
const int BOARDSIZE = 5;
int movesPlayer1 = 0, movesPlayer2 = 0;
bool player1win = false, attack;
string player1, player2;
// Array for Pieces and spaces
char pieces[5][5] = { {'X', 'X', 'X', 'X', 'X'},
					 {'X', 'X', 'X', 'X', 'X'},
					 {'X', 'X', ' ', 'O', 'O'},
					 {'O', 'O', 'O', 'O', 'O'},
					 {'O', 'O', 'O', 'O', 'O'} };
// function prototypes
void display(string player1, string player2);
void Pattern();
void spaces();
void inputMove(int* presentI, int* presentJ, int* i, int* j);
void move(int presentI, int presentJ, int i, int j);
bool Attacked(int presentI, int presentJ, int& i, int& j);
bool extraMove(int nextRow, int nextColumn, bool attack, bool player);
bool checkWin();
int inputValid();
bool validation(int row, int column, int nextRow, int nextcolumn, int preRow, int preCol, bool player, bool extra);
bool validationComp(int row, int column, int nextRow, int nextcolumn, int preRow, int preCol, bool player, bool extra);
int main()
{
	fstream fout;
	ifstream  fin;
	fin.open("instruction.txt");
	fout.open("record.txt", ios::app);
	if (!fout.fail() && !fin.fail())
	{
		string input;
		SetConsoleTextAttribute(h, 11);
		while (!fin.eof()) {
			getline(fin, input);
			cout << input << endl;
		}
		cin.get();
		system("cls");
		int choice;
		cout << "Enter 1 to play with computer and 2 for multipayer:";
		cin >> choice;
		while ((choice != 1 || choice != 2) && cin.fail()) {
			cin.clear();
			cin.ignore();
			SetConsoleTextAttribute(h, 4);
			cout << "Invalid!" << endl;;
			cout << "Enter 1 to play with computer and 2 for multipayer:";
			cin >> choice;
		}
		if (choice == 1) {
			int row, column, nextRow, nextColumn, preRow = 0, preCol = 0;
			bool player = false, extra;
			string status1 = "lose", status2 = "won";
			player2 = "Computer";
			cin.ignore();
			SetConsoleTextAttribute(h, 11);
			cout << "Please enter your name:";
			getline(cin, player1);
			while (!checkWin())
			{
				// player = 0 for player1 and 1 for player 2
				do
				{
					// printing the pattern
					extra = false;
					if (!player) {
						display(player1, player2);
					}
					else {
						display(player1, player2);
						Sleep(2000);
					}

					if (!player) {
						inputMove(&row, &column, &nextRow, &nextColumn);
					}
					else {
						do {
							row = rand() % 4 + 1;
							column = rand() % 4 + 1;
							nextRow = rand() % 4 + 1;
							nextColumn = rand() % 4 + 1;
						} while (!validationComp(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
					}
					system("cls");
				} while (!validation(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
				// calling the function
				move(row, column, nextRow, nextColumn);
				if (!player) {
					display(player1, player2);
				}
				else {
					display(player1, player2);
					Sleep(2000);
				}
				system("cls");
				while (extraMove(nextRow, nextColumn, attack, player))
				{
					extra = true;
					preRow = nextRow;
					preCol = nextColumn;
					do {
						if (!player) {
							display(player1, player2);
						}
						else {

							display(player1, player2);
							Sleep(2000);
						}
						if (!player) {
							inputMove(&row, &column, &nextRow, &nextColumn);
						}
						else {
							do {
								row = rand() % 4 + 1;
								column = rand() % 4 + 1;
								nextRow = rand() % 4 + 1;
								nextColumn = rand() % 4 + 1;
							} while (!validationComp(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
						}
						system("cls");
					} while (!validation(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
					move(row, column, nextRow, nextColumn);
					if (!player) {
						display(player1, player2);
					}
					else {

						display(player1, player2);
						Sleep(2000);
					}
					system("cls");
				}
				player = !player;
			}
			if (!player1win == 1) {
				status1 = "won";
				status2 = "lose";
			}
			fout << player1 << " " << status1 << " the match in " << movesPlayer1 << " moves." << endl;
			fout << player2 << " " << status2 << " the match in " << movesPlayer2 << " moves." << endl;
		}
		if (choice == 2)
		{
			int row, column, nextRow, nextColumn, preRow = 0, preCol = 0;
			bool player = false, extra;
			string status1 = "lose", status2 = "won";
			cin.ignore();
			SetConsoleTextAttribute(h, 11);
			cout << "Player 1 please enter your name:";
			getline(cin, player1);
			cout << "Player 2 please enter your name:";
			getline(cin, player2);

			// The loop will contine untill one player wins
			while (!checkWin())
			{
				// player = 0 for player1 and 1 for player 2
				do
				{
					// printing the pattern
					extra = false;
					display(player1, player2);
					inputMove(&row, &column, &nextRow, &nextColumn);
					system("cls");
				} while (!validation(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
				// calling the function
				move(row, column, nextRow, nextColumn);
				display(player1, player2);
				system("cls");
				while (extraMove(nextRow, nextColumn, attack, player))
				{
					extra = true;
					preRow = nextRow;
					preCol = nextColumn;
					do {
						display(player1, player2);
						inputMove(&row, &column, &nextRow, &nextColumn);
						if (!player && pieces[row][column] == 'X')
						{
							extra = false;
							player = !player;
						}
						else if (player && pieces[row][column] == 'O')

						{
							extra = false;
							player = !player;
						}
						system("cls");
					} while (!validation(row, column, nextRow, nextColumn, preRow, preCol, player, extra));
					move(row, column, nextRow, nextColumn);
					display(player1, player2);
					system("cls");
				}
				player = !player;

			}


			if (!player1win == 1) {
				status1 = "won";
				status2 = "lose";
			}
			fout << player1 << " " << status1 << " the match in " << movesPlayer1 << " moves." << endl;
			fout << player2 << " " << status2 << " the match in " << movesPlayer2 << " moves." << endl;



		}
		fout.close();
		fin.close();
	}
	else
	{
		cout << "file is not opened.";
	}
	return 0;
}
// function declartions
void display(string player1, string player2)
{
	Pattern();
	SetConsoleTextAttribute(h, 14);
	cout << "--------------------------------------------------------------------------------------" << endl;
	SetConsoleTextAttribute(h, 15);
	spaces();
	cout << player1 << "'s pieces are 'O' " << endl;
	spaces();
	cout << player2 << "'s Pieces are 'X" << endl;
	SetConsoleTextAttribute(h, 14);
	cout << "--------------------------------------------------------------------------------------" << endl;
	SetConsoleTextAttribute(h, 15);

}
void inputMove(int* presentI, int* presentJ, int* i, int* j)
{
	SetConsoleTextAttribute(h, 11);
	spaces();
	cout << "Make your move!" << endl;
	SetConsoleTextAttribute(h, 15);
	cout << "Present row(0 - 4)\n";
	*presentI = inputValid();
	SetConsoleTextAttribute(h, 15);
	cout << "Present column (0 - 4) \n";
	*presentJ = inputValid();
	SetConsoleTextAttribute(h, 15);
	cout << "Move row(0 - 4)\n";
	*i = inputValid();
	SetConsoleTextAttribute(h, 15);
	cout << "Move column(0 - 4)\n";
	*j = inputValid();
	SetConsoleTextAttribute(h, 15);
}
// Function for extraMove
bool extraMove(int nextRow, int nextColumn, bool attack, bool player)
{
	if (!attack)
	{
		return false;
	}
	int oppPiecePosI, oppPiecePosJ;
	char oppPieces;
	if (!player)
	{
		oppPieces = 'X';
	}
	else
	{
		oppPieces = 'O';
	}
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			oppPiecePosI = nextRow;
			oppPiecePosJ = nextColumn;
			if ((i != 0 || j != 0) && pieces[nextRow + i][nextColumn + j] == oppPieces)
			{
				oppPiecePosI += i * 2;
				oppPiecePosJ += j * 2;
				if (pieces[oppPiecePosI][oppPiecePosJ] == ' ')
				{
					return true;
				}
				oppPiecePosI = 0;
				oppPiecePosJ = 0;
			}
		}
	}
	return false;
}

// function for drawing the patterns
void Pattern()
{
	// for five rows
	SetConsoleTextAttribute(h, 14);
	cout << "--------------------------------------------------------------------------------------" << endl
		<< endl;
	SetConsoleTextAttribute(h, 15);
	for (int i = 0; i <= BOARDSIZE; i++)
	{
		spaces();
		//  for five columns
		for (int j = 0; j < BOARDSIZE; j++)
		{
			// condition for printing row number
			if (j == 0)
			{
				if (i != BOARDSIZE)
				{
					cout << i << '|';
				}
				else
				{
					cout << "  ";
				}
			}
			if (i == BOARDSIZE)
			{
				cout << j << "     ";
			}
			else
			{
				if (pieces[i][j] == 'O')
				{
					SetConsoleTextAttribute(h, 1);
				}
				else
				{
					SetConsoleTextAttribute(h, 4);
				}
				cout << pieces[i][j];
				SetConsoleTextAttribute(h, 15);
				if (j != BOARDSIZE - 1)
				{
					SetConsoleTextAttribute(h, 14);
					cout << "-----";
					SetConsoleTextAttribute(h, 15);
				}
			}
		}
		cout << endl
			<< endl;
	}
	SetConsoleTextAttribute(h, 14);
	cout << "--------------------------------------------------------------------------------------" << endl;
	SetConsoleTextAttribute(h, 15);
}
// function for making moves
void move(int presentI, int presentJ, int i, int j)
{
	char temp = pieces[presentI][presentJ];
	pieces[presentI][presentJ] = pieces[i][j];
	pieces[i][j] = temp;

	if (Attacked(presentI, presentJ, i, j))
	{
		pieces[i][j] = ' ';
	}
}
// function for checking who is the winner
bool checkWin()
{
	bool win1 = true, win2 = true;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (pieces[i][j] == 'X')
			{
				win1 = false;
				player1win = false;
			}
			if (pieces[i][j] == 'O')
			{
				win2 = false;
			}
		}
	}
	if (win1)
	{
		SetConsoleTextAttribute(h, 10);
		spaces();
		cout << "Congratulatiios!!! " << player1 << " you are the winner";
		win1;
		SetConsoleTextAttribute(h, 7);
	}
	if (win2)
	{
		SetConsoleTextAttribute(h, 10);
		spaces();
		cout << "Congratulatiios!!! " << player2 << " you are the winner";
		return win2;
		SetConsoleTextAttribute(h, 7);
	}
	return win1 || win2;
}
// function for checking if the pieces are attacked or not
bool Attacked(int presentI, int presentJ, int& i, int& j)
{
	attack = false;
	if ((presentI - i) == -2)
	{
		i--;
		attack = true;
	}
	if ((presentI - i) == +2)
	{
		i++;
		attack = true;
	}
	if ((presentJ - j) == -2)
	{
		j--;
		attack = true;
	}
	if ((presentJ - j) == +2)
	{
		j++;
		attack = true;
	}
	return attack;
};
// function for aligning at the center
void spaces()
{
	cout << "                              ";
}
// function for validation
bool validation(int row, int column, int nextRow, int nextColumn, int preRow, int preCol, bool player, bool extra)
{
	int tempRow = nextRow, tempCol = nextColumn;
	SetConsoleTextAttribute(h, 4);
	if (pieces[nextRow][nextColumn] != ' ')
	{
		cout << "Illegal Move!!! Move not allowed" << endl;
		SetConsoleTextAttribute(h, 15);
		return false;
	}
	if (!extra) {
		if (!player && pieces[row][column] != 'O')
		{
			cout << "Illegal move!!! your pieces are 'O'" << endl;
			SetConsoleTextAttribute(h, 15);
			return false;
		}
		if (player && pieces[row][column] != 'X')
		{
			cout << "Illegal move!!! your pieces are 'X'" << endl;
			SetConsoleTextAttribute(h, 15);
			return false;
		}
		if (Attacked(row, column, nextRow, nextColumn))
		{
			if (!player && pieces[nextRow][nextColumn] != 'X')
			{
				cout << "Illegal move!!! you can take only 'X' pieces" << endl;
				SetConsoleTextAttribute(h, 15);
				return false;
			}
			else if (player && pieces[nextRow][nextColumn] != 'O')
			{
				cout << "Illegal move!!! you can take only 'O' pieces" << endl;
				SetConsoleTextAttribute(h, 15);
				return false;
			}
			if (((row - tempRow) % 2 != 0) || ((column - tempCol) % 2 != 0))
			{
				cout << "Error:" << endl
					<< "Not a valid move" << endl;
				return false;
			}
		}
		else
		{
			if ((row - nextRow < -1) || (row - nextRow > 1) || (column - nextColumn < -1) || (column - nextColumn > 1))
			{

				cout << "Illegal move!!Move not allowed" << endl;
				SetConsoleTextAttribute(h, 15);
				return false;
			}
		}

	}
	else
	{
		if (preRow != row || preCol != column)
		{

			cout << "Error:" << endl
				<< "Move goes against the rules" << endl;
			SetConsoleTextAttribute(h, 15);
			return false;
		}
		if (!Attacked(row, column, nextRow, nextColumn))
		{
			cout << "This move goes against the rules" << endl;
			SetConsoleTextAttribute(h, 15);
			return false;
		}
		if (((row - tempRow) % 2 != 0) || ((column - tempCol) % 2 != 0))
		{
			cout << "Error:" << endl
				<< "Not a valid move" << endl;
			return false;
		}

	}
	if (!player)
	{
		movesPlayer1++;
	}
	else
	{
		movesPlayer2++;
	}
	return true;
}
int inputValid()
{
	int num;
	cout << "Enter number:";
	cin >> num;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore();
		SetConsoleTextAttribute(h, 4);
		cout << "Invalid! Please enter a correct number(0 - 4):";
		cin >> num;
	}
	if (num == 0 || num == 1 || num == 2 || num == 3 || num == 4)
	{
		return num;
	}
	else
	{
		SetConsoleTextAttribute(h, 4);
		while (true)
		{
			cout << "Invalid! ";
			cout << "enter correct number(0 - 4):";
			cin >> num;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			else
			{
				if (num == 0 || num == 1 || num == 2 || num == 3 || num == 4)
				{
					break;
				}
			}
		}
		return num;
	}
}
bool validationComp(int row, int column, int nextRow, int nextColumn, int preRow, int preCol, bool player, bool extra)
{
	int tempRow = nextRow, tempCol = nextColumn;
	if (pieces[nextRow][nextColumn] != ' ')
	{
		return false;
	}
	if (!extra) {
		if (!player && pieces[row][column] != 'O')
		{
			return false;
		}
		if (player && pieces[row][column] != 'X')
		{
			return false;
		}
		if (Attacked(row, column, nextRow, nextColumn))
		{
			if (!player && pieces[nextRow][nextColumn] != 'X')
			{

				return false;
			}
			if (player && pieces[nextRow][nextColumn] != 'O')
			{

				return false;
			}
			if (((row - tempRow) % 2 != 0) || ((column - tempCol) % 2 != 0))
			{

				return false;
			}
		}
		else
		{
			if ((row - nextRow < -1) || (row - nextRow > 1) || (column - nextColumn < -1) || (column - nextColumn > 1))
			{


				return false;
			}
		}

	}
	else
	{
		if (preRow != row || preCol != column)
		{


			return false;
		}
		if (!Attacked(row, column, nextRow, nextColumn))
		{

			return false;
		}
		if (((row - tempRow) % 2 != 0) || ((column - tempCol) % 2 != 0))
		{

			return false;
		}

	}
	if (!player)
	{
		movesPlayer1++;
	}
	else
	{
		movesPlayer2++;
	}
	return true;
}