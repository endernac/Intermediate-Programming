// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "King.h"
#include <math.h>

bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if(end.first == start.first && end.second == start.second) {
    return false;
  }
  if((abs(end.first - start.first) == 1 && abs(end.second - start.second) == 1)
     || (abs(end.first - start.first) == 0 && abs(end.second - start.second) == 1)
     || (abs(end.first - start.first) == 1 && abs(end.second - start.second) == 0)) {
    return true;
  }
  return false;
}
