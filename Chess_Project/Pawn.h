// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <math.h>
#include <utility>
#include <iostream>

class Pawn : public Piece {

public:

  ~Pawn(){}

  int legal_first_move_double(std::pair<char, char> start, std::pair<char, char> end)const;

  bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const;

  bool legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const;

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  char to_ascii() const {
    return is_white() ? 'P' : 'p';
  }

private:
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Pawn(bool is_white) : Piece(is_white) {}

  friend Piece* create_piece(char piece_designator);
};

#endif // PAWN_H
