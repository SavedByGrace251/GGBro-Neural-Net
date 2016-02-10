//
//  Piece.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#ifndef Piece_h
#define Piece_h

#include <vector>
using std::vector;
#include <map>
using std::map;

class Piece {
public:
    int position;
    bool isRed;
    bool isKing = false;
    
    // Secondary ctor
    Piece(int position, bool isRed, bool isKing) {
        this->position = position;
        this->isRed = isRed;
        this->isKing = isKing;
    }

	vector<vector<int>> getPossibleJumps() {
		vector<vector<vector<int>>> redJumps{ { { 5, 9 } },{ { 5, 8 },{ 6, 10 } },{ { 6, 9 },{ 7, 11 } },{ { 7, 10 } }, // Top row legal jumps
												{ { 8, 13 } },{ { 8, 12 },{ 9, 14 } },{ { 9, 13 },{ 10, 15 } },{ { 10, 14 } }, // 2nd row legal jumps
												{ { 13, 17 } },{ { 13, 16 },{ 14, 18 } },{ { 14, 17 },{ 15, 19 } },{ { 15, 18 } }, // 3rd row legal jumps
												{ { 16, 21 } },{ { 16, 20 },{ 17, 22 } },{ { 17, 21 },{ 18, 23 } },{ { 18, 22 } }, // 4th row legal jumps
												{ { 21, 25 } },{ { 21, 24 },{ 22, 26 } },{ { 22, 25 },{ 23, 27 } },{ { 23, 26 } }, // 5th row legal jumps
												{ { 24, 29 } },{ { 24, 28 },{ 25, 30 } },{ { 25, 29 },{ 26, 31 } },{ { 26, 30 } }, // 6th row legal jumps
												{},{},{},{}, // 7th row legal jumps
												{},{},{},{} }; // Bottom row legal jumps
		vector<vector<vector<int>>> blackJumps{ {},{},{},{}, // Top row legal jumps
												{},{},{},{}, // And so on...
												{ { 5, 1 } },{ { 5, 0 },{ 6, 2 } },{ { 6, 1 },{ 7, 3 } },{ { 7, 2 } },
												{ { 8, 5 } },{ { 8, 4 },{ 9, 6 } },{ { 9, 5 },{ 10, 7 } },{ { 10, 6 } },
												{ { 13, 9 } },{ { 13, 8 },{ 14, 10 } },{ { 14, 9 },{ 15, 11 } },{ { 16, 10 } },
												{ { 16, 13 } },{ { 16, 12 },{ 17, 14 } },{ { 17, 13 },{ 18, 15 } },{ { 19, 14 } },
												{ { 21, 17 } },{ { 21, 16 },{ 22, 18 } },{ { 23, 17 },{ 24, 19 } },{ { 24, 18 } },
												{ { 24, 21 } },{ { 24, 20 },{ 25, 22 } },{ { 25, 21 },{ 26, 23 } },{ { 26, 22 } } };
		vector<vector<vector<int>>> kingJumps{ { { 5, 9 } },{ { 5, 8 },{ 6, 10 } },{ { 6, 9 },{ 7, 11 } },{ { 7, 10 } },
												{ { 8, 13 } },{ { 8, 12 },{ 9, 14 } },{ { 9, 13 },{ 10, 15 } },{ { 10, 14 } },
												{ { 5, 1 },{ 13, 17 } },{ { 5, 0 },{ 6, 2 },{ 13, 16 },{ 14, 18 } },{ { 6, 1 },{ 7, 3 },{ 14, 17 },{ 15, 19 } },{ { 7, 2 },{ 15, 18 } },
												{ { 8, 5 },{ 16, 21 } },{ { 8, 4 },{ 9, 6 },{ 16, 20 },{ 17, 22 } },{ { 9, 5 },{ 10, 7 },{ 17, 21 },{ 18, 23 } },{ { 10, 6 },{ 18, 22 } },
												{ { 13, 9 },{ 21, 25 } },{ { 13, 8 },{ 14, 10 },{ 21, 24 },{ 22, 26 } },{ { 14, 9 },{ 15, 11 },{ 22, 25 },{ 23, 27 } },{ { 15, 10 },{ 23, 26 } },
												{ { 16, 13 },{ 24, 29 } },{ { 16, 12 },{ 17, 14 },{ 24, 28 },{ 25, 30 } },{ { 17, 13 },{ 18, 15 },{ 25, 29 },{ 26, 31 } },{ { 18, 14 },{ 26, 30 } },
												{ { 21, 17 } },{ { 21, 16 },{ 22, 18 } },{ { 23, 17 },{ 24, 19 } },{ { 24, 18 } },
												{ { 24, 21 } },{ { 24, 20 },{ 25, 22 } },{ { 25, 21 },{ 26, 23 } },{ { 26, 22 } } };
		if (isKing) return kingJumps[position];
		if (isRed) return redJumps[position];
		return blackJumps[position];
	}

    // Return possible moves depending on position and type
    vector<int> getPossibleMoves() {
        vector<vector<int>> redMoves { { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 }, // Top row legal moves
										{ 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, // 2nd row legal moves
										{ 12, 13 }, { 13, 14 }, { 14, 15 }, { 15 }, // 3rd row legal moves
										{ 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, // 4th row legal moves
										{ 20, 21 }, { 21, 22 }, { 23, 24 }, { 24 }, // 5th row legal moves
										{ 25 }, { 25, 26 }, { 26, 27 }, { 27, 28 }, // 6th row legal moves
										{ 28, 29 }, { 29, 30 }, { 30, 31 }, { 31 }, // 7th row legal moves
										{}, {}, {}, {} }; // Bottom row legal moves
        vector<vector<int>> blackMoves { {}, {}, {}, {}, // Top row legal moves
										{ 0 }, { 0, 1 }, { 1, 2 }, { 2, 3 }, // And so on...
										{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 },
										{ 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 },
										{ 12, 13 }, { 13, 14 }, { 14, 15 }, { 15 },
										{ 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 },
										{ 20, 21 }, { 21, 22 }, { 22, 23 }, { 23 },
										{ 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 } };
        vector<vector<int>> kingMoves { { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 },
										{ 0, 8 }, { 0, 1, 8, 9 }, { 1, 2, 9, 10 }, { 2, 3, 10, 11 },
										{ 4, 5, 12, 13 }, { 5, 6, 13, 14 }, { 6, 7, 14, 15 }, { 7, 15 },
										{ 8, 16 }, { 8, 9, 16, 17 }, { 9, 10, 17, 18 }, { 10, 11, 18, 19 },
										{ 12, 13, 20, 21 }, { 13, 14, 21, 22 }, { 14, 15, 22, 23 }, { 15, 24 },
										{ 16, 25 }, { 16, 17, 25, 26 }, { 17, 18, 26, 27 }, { 18, 19, 27, 28 },
										{ 20, 21, 28, 29 }, { 21, 22, 29, 30 }, { 22, 23, 30, 31 }, { 23, 31 },
										{ 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 } };
        if (isKing) return kingMoves[position];
        if (isRed) return redMoves[position];
        return blackMoves[position];
    }
};

#endif /* Piece_h */
