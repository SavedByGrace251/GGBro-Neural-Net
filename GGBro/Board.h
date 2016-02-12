//
//  Board.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#ifndef Board_h
#define Board_h

#include "Piece.h"
#include <algorithm>
using std::find;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::pair;
using std::make_pair;

class Board {
public:

	vector<Piece> redPieces;
	vector<Piece> blackPieces;
	bool redTurn = true;
	vector<int> freeSpaces{};

	// Default ctor
	Board() {
		for (int i = 0; i < 12; i++) {
			// First 12 indices are red pieces (not kings)
			redPieces.push_back(Piece(i, true, false));
		}
		for (int i = 20; i < 32; i++) {
			// Last 12 indices are black pieces (not kings)
			blackPieces.push_back(Piece(i, false, false));
		}
		freeSpaces = { 12, 13, 14, 15, 16, 17, 18, 19 };
	}

	// Secondary ctor that takes a string for the state
	Board(string state, bool redTurn) {
		for (int i = 0; i < state.length(); i++) {
			if (state[i] != '_') {
				bool redCheck = state[i] == 'r' || state[i] == 'R';
				bool kingCheck = state[i] == 'R' || state[i] == 'B';
				if (redCheck) {
					this->redPieces.push_back(Piece(i, redCheck, kingCheck));
				} else {
					this->blackPieces.push_back(Piece(i, redCheck, kingCheck));
				}
			} else {
				freeSpaces.push_back(i);
			}
		}
		this->redTurn = redTurn;
	}

	// Secondary ctor that takes a vector of Piece's
    Board(vector<Piece> redPieces, vector<Piece> blackPieces, bool redTurn) {
		this->redPieces = redPieces;
		this->blackPieces = blackPieces;
		this->redTurn = redTurn;
    }
    
    // Secondary ctor that takes a vector of Piece's
    Board(vector<Piece> redPieces, vector<Piece> blackPieces, bool redTurn, std::pair<int, bool> pieceToRemove) {
        this->redPieces = redPieces;
        this->blackPieces = blackPieces;
        this->redTurn = redTurn;
        removePiece(pieceToRemove.first, pieceToRemove.second);
    }

	// Whether or not this board has no legal moves
	bool hasNoMoves() {
		return true;
	}
    
    void removePiece(int idx, bool isRedPiece) {
        if (isRedPiece) {
            redPieces.erase(redPieces.begin() + idx);
        } else {
            blackPieces.erase(blackPieces.begin() + idx);
        }
    }

	// Generate all legal boards
	vector<Board> generateLegalMoves() {
        bool foundJump = false;
        
		vector<Board> possibleBoards;
		vector<Piece> tempPieces;

		vector<Piece> * apponentPieces;
		vector<Piece> * ownerPieces;

		// red's turn
		if (redTurn) {
			apponentPieces = &blackPieces;
			ownerPieces = &redPieces;
		// if black's turn
		} else {
			apponentPieces = &redPieces;
			ownerPieces = &blackPieces;
		}
		
		for (auto & piece : *ownerPieces) {
            int n = 0;
            vector<pair<int, bool>> piecesToRemove;
			// check if jump available
			// using pointer for "erase" function
            for (auto & apponent : *apponentPieces) {
				for (auto & jump : piece.getPossibleJumps()) {
					if (apponent.position == jump[0]) {
						auto foundFreeSpace = find(freeSpaces.begin(), freeSpaces.end(), jump[1]);
						// if there is an available free space
						if (foundFreeSpace != freeSpaces.end()) {
							// save current board
							tempPieces = *ownerPieces;
							// change piece's position
							piece.position = jump[1];
                            // add changed board
                            possibleBoards.push_back(Board(this->redPieces, this->blackPieces, !this->redTurn, make_pair(n, apponent.isRed)));
							// set piece to be removed apponent piece
                            piecesToRemove.push_back(make_pair(n, apponent.isRed));
                            // put pieces
                            *ownerPieces = tempPieces;
                            // notify jump is found
                            foundJump = true;
						}
					}
				}
                ++n;
			}
            
            if (!foundJump) {
                // check if space available on board
                for (auto & space : piece.getPossibleMoves()) {
                    auto foundFreeSpace = find(freeSpaces.begin(), freeSpaces.end(), space);
                    // if there is an available free space
                    if (foundFreeSpace != freeSpaces.end()) {
                        // save current board
                        tempPieces = *ownerPieces;
                        // change piece's position
                        piece.position = space;
                        // add changed board
                        possibleBoards.push_back(Board(this->redPieces, this->blackPieces, !this->redTurn));
                        // replace pieces
                        *ownerPieces = tempPieces;
                    }
                }
            }
		}

		return possibleBoards;
	}

	string toString() {
		vector<char> boardStr(32, '_');
		for (auto piece : redPieces) {
			if (piece.isKing) {
				boardStr[piece.position] = 'R';
			} else {
				boardStr[piece.position] = 'r';
			}
		}
		for (auto piece : blackPieces) {
			if (piece.isKing) {
				boardStr[piece.position] = 'B';
			} else {
				boardStr[piece.position] = 'b';
			}
		}
		string strOut(boardStr.begin(), boardStr.end());
		return strOut;
	}
};

#endif /* Board_h */
