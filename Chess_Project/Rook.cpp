// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "Rook.h"

bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if(start.first == end.first || start.second == end.second){
    return true;
  }
  return false;
}
