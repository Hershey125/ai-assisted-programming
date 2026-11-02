#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

#include "o.h"
#include "win.h"
#include "x.h"

class Game {
public:
	Game() : board_{}, xTurn_(true) {
		board_.fill(' ');
	}

	void play() {
		while (true) {
			printBoard();
			const char currentMark = xTurn_ ? x_.mark() : o_.mark();
			int position;

			std::cout << currentMark << "'s turn. Choose a square (1-9): ";
			if (!(std::cin >> position)) {
				if (std::cin.eof()) {
					return;
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Please enter a number from 1 to 9.\n";
				continue;
			}

			if (position < 1 || position > 9 || board_[position - 1] != ' ') {
				std::cout << "That square is unavailable. Choose an empty square from 1 to 9.\n";
				continue;
			}

			board_[position - 1] = currentMark;
			if (Win::hasWon(board_, currentMark)) {
				printBoard();
				std::cout << currentMark << " wins!\n";
				return;
			}

			if (std::all_of(board_.begin(), board_.end(), [](char square) {
					return square != ' ';
				})) {
				printBoard();
				std::cout << "It's a draw!\n";
				return;
			}

			xTurn_ = !xTurn_;
		}
	}

private:
	void printBoard() const {
		for (int row = 0; row < 3; ++row) {
			for (int column = 0; column < 3; ++column) {
				const int index = row * 3 + column;
				const char square = board_[index] == ' '
					? static_cast<char>('1' + index)
					: board_[index];
				std::cout << ' ' << square << ' ';
				if (column < 2) {
					std::cout << '|';
				}
			}
			std::cout << '\n';
			if (row < 2) {
				std::cout << "---+---+---\n";
			}
		}
	}

	std::array<char, 9> board_;
	bool xTurn_;
	X x_;
	O o_;
};

#endif
