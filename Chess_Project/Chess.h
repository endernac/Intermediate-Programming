// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "Piece.h"
#include "Board.h"

class Chess {

public:
  // This default constructor initializes a board with the standard
  // piece positions, and sets the state to white's turn
  Chess();

  // Returns a constant reference to the board 
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  const Board& get_board() const { return board; }

  ~Chess() {}

  // Returns true if it is white's turn
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  bool turn_white() const { return is_white_turn; }

  // Attemps to make a move. If successful, the move is made and
  // the turn is switched white <-> black
  bool make_move(std::pair<char, char> start, std::pair<char, char> end);

  int not_legal_move(std::pair<char, char> start, std::pair<char, char> end);

  // Returns true if the designated player is in check
  bool in_check(bool white) const;

  // Returns true if the designated player is in mate
  bool in_mate(bool white) const;

  // Returns true if the designated player is in mate
  bool in_stalemate(bool white) const;

  void wipe_board();

  void set_turn(bool white) {is_white_turn = white;}

  void can_move(bool white);

  bool can_move_result(bool white);

  void mod_board(std::pair<char, char> space, char p) {board.add_piece(space, p);}

private:
  // The board
  Board board;

  // Is it white's turn?
  bool is_white_turn;

  // naive_move checks if a move is valid not accounting for checks, will print error statements
  int naive_move(std::pair<char, char> start, std::pair<char, char> end, bool white) const;

  bool white_can_move = true;
  bool black_can_move = true;

};

// Writes the board out to a stream
std::ostream& operator<< (std::ostream& os, const Chess& chess);

// Reads the board in from a stream
std::istream& operator>> (std::istream& is, Chess& chess);


#endif // CHESS_H
