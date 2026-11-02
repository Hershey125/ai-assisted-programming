#ifndef WIN_H
#define WIN_H

#include <array>

class Win {
public:
	static bool hasWon(const std::array<char, 9>& board, char mark) {
		static constexpr std::array<std::array<int, 3>, 8> lines{{
			{{0, 1, 2}}, {{3, 4, 5}}, {{6, 7, 8}},
			{{0, 3, 6}}, {{1, 4, 7}}, {{2, 5, 8}},
			{{0, 4, 8}}, {{2, 4, 6}}
		}};

		for (const auto& line : lines) {
			if (board[line[0]] == mark &&
				board[line[1]] == mark &&
				board[line[2]] == mark) {
				return true;
			}
		}
		return false;
	}
};

#endif
