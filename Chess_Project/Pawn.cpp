// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Piece.h"
#include "Pawn.h"
#include <math.h>
#include <iostream>

using std::cout; using std::endl;

int Pawn::legal_first_move_double(std::pair<char, char> start, std::pair<char, char> end)const{
  if(((this->to_ascii() == 'P' && start.second == '2') || (this->to_ascii() == 'p' && start.second == '7')) &&
       (end.first == start.first) &&
       ((abs((int)end.second - (int)start.second)) == 2)){
      return 2; // returns 2 if valid move
    }
  return 0;
}

bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  if(legal_first_move_double(start, end) == 2){
    return true;
  }

  if(end.first == start.first) {
    if(end.second - start.second == 1 && is_white() == true) {  // white must move up
      return true;
    }
    if(end.second - start.second == -1 && is_white() == false) {  // black must move down
      return true;
    }
  }
  return false;
}

bool Pawn::legal_capture_shape(std::pair<char, char> start,std::pair<char, char> end) const{
  if(is_white() == true) {
    if(abs(end.first - start.first) == 1 && end.second - start.second == 1) {  // can move to either side
      return true;
    }
  } else {
    if(abs(end.first - start.first) == 1 && end.second - start.second == -1) { 
      return true;
    }
  }
  return false;
}
