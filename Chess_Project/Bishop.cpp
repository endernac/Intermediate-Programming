// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "Bishop.h"
#include <math.h>

bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {

  //check if movement is diagonal
  if (abs((end.second - start.second)) == abs((end.first - start.first))) {
    return true;
  }
  return false;
}
