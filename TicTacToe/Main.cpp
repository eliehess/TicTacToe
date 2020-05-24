#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

void printBoard();
void initBoard();
bool makeMove();
void nextPlayer();
char checkWinner();

const int SIZE = 3;

char board[SIZE][SIZE];
char currentPlayer = 'X';
int numTurns = 1;

int main() {
	initBoard();
	printBoard();
	while (1) {
		if (!makeMove()) continue;

		printBoard();
		char winner = checkWinner();
		if (winner != NULL) {
			cout << winner << " wins!\n";
			break;
		} else if (numTurns >= SIZE * SIZE) {
			cout << "It's a tie!\n";
			break;
		}
		nextPlayer();
	}
}

void nextPlayer() {
	switch (currentPlayer) {
	case 'X':
		currentPlayer = 'O';
		break;
	case 'O':
		currentPlayer = 'X';
		break;
	default:
		cout << "Illegal player detected\n";
		exit(1);
	}
	numTurns++;
}

void printBoard() {
	system("cls");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void initBoard() {
	int start = 1;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = (char)(start++ + '0');
		}
	}
}

bool makeMove() {
	string input;
	int num = 0;

	cout << "Enter the number of the square you want to play: ";
	cin >> input;

	try {
		num = stoi(input);
	} catch (const invalid_argument&) {
		cout << "Input " << input << " not a number. Please try again with a number.\n";
		return false;
	}

	if (num < 1 || num > SIZE * SIZE) {
		cout << "Number " << num << " not valid. Please try again with a valid number (1 to " << SIZE * SIZE << ").\n";
		return false;
	} 
	int row = (num - 1) / SIZE;
	int col = (num - 1) % SIZE;
	int value = board[row][col] - 'A';
	if (value >= 0 && value <= 25) {
		cout << "Space " << num << " is already occupied. Please try again.\n";
		return false;
	}
	board[row][col] = currentPlayer;
	return true;
}

char checkWinner() {
	char c;
	bool b;
	for (int i = 0; i < SIZE; i++) {
		c = board[i][0];
		b = true;
		for (int j = 1; j < SIZE; j++) {
			b = b && (board[i][j] == c);
		}
		if (b) return c;
	}

	for (int i = 0; i < SIZE; i++) {
		c = board[0][i];
		b = true;
		for (int j = 1; j < SIZE; j++) {
			b = b && (board[j][i] == c);
		}
		if (b) return c;
	}

	c = board[0][0];
	b = true;
	for (int i = 1; i < SIZE; i++) {
		b = b && (board[i][i] == c);
	}
	if (b) return c;

	c = board[0][SIZE - 1];
	b = true;
	for (int i = 1; i < SIZE; i++) {
		b = b && (board[i][SIZE - i - 1] == c);
	}
	if (b) return c;

	return NULL;
}
