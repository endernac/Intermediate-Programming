// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "Queen.h"
#include <math.h>

bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  // Can't stay still
  if(end.first == start.first && end.second == start.second) {
    return false;
  }   

  //checks if move is legal by rook movement
  if((start.first == end.first) || (start.second == end.second)) {
    return true;
  }   
    
  //checks if move is legal by bishop movement
  if (abs((end.second - start.second)) == abs((end.first - start.first))) {
    return true;
  }   

  return false;
}
