// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


class Board {

  // Throughout, we will be accessing board positions using an std::pair<char, char>.
  // The assumption is that the first value is the column with values in
  // {'A','B','C','D','E','F','G','H'} (all caps)
  // and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

public:
  // Default constructor
  Board();

  // Returns a const pointer to the piece at a prescribed location if it exists,
  // or nullptr if there is nothing there.
  const Piece* operator() (std::pair<char, char> position) const;

  // Destructor for Board;
  ~Board();

  // Attempts to add a new piece with the specified designator, at the given location.
  // Returns false if:
  // -- the designator is invalid,
  // -- the specified location is not on the board, or
  // -- if the specified location is occupied
  bool add_piece(std::pair<char, char> position, char piece_designator);

  // promotes pawn to queen if there is a pawn in that position and the position 
  // is at the end of the board
  void promote(std::pair<char, char> position);

  // Pretty much () operator, but pointer isn't constant
  Piece* get_piece(std::pair<char, char> position);

  // Places a piece on the Board if given a valid position
  void place_piece(std::pair<char, char> position, Piece* piece);

  // Remove the tile. Can be used to clear empty tiles or to remove a piece
  // from the board to test for checks without deleting the object.
  void remove_tile(std::pair<char, char> position);

  // Returns true if the board has the right number of kings on it
  bool has_valid_kings() const;

  // Displays the board by printing it to stdout
  void display() const;

  // helper function to check if the character pair is a valid pos
  bool valid_pos(std::pair<char, char> pos) const;

  // helper function to check if there are pieces in the way when traveling (ignoring knights)
  bool is_clear(std::pair<char, char> start, std::pair<char, char> end) const;

  // Find the location of the desired king
  std::pair<char,char> find_king(bool white) const;

  const std::map<std::pair<char, char>, Piece*> get_map() const{
    return occ;
  };

  void clear_board();

private:
  // The sparse map storing the pieces, keyed off locations
  std::map<std::pair<char, char>, Piece*> occ;
};


// Write the board state to an output stream
std::ostream& operator<< (std::ostream& os, const Board& board);

#endif // BOARD_H
