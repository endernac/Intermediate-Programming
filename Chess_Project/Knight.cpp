// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "Knight.h"
#include <math.h>

bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  return(!(end.first == start.first && end.second == start.second) && // piece must move
          ((abs(start.first - end.first) == 2 && abs(start.second - end.second) == 1) ||
           (abs(start.first - end.first) == 1 && abs(start.second - end.second) == 2))); // checks if end is one off two in front/back
}
