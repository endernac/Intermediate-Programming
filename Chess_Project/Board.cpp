// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"
#include "Terminal.h"
#include <string>

using std::cout; using std::endl;
using std::map; using std::pair;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Board& board) {
  for(char r = '8'; r >= '1'; r--) {
    for(char c = 'A'; c <= 'H'; c++) {
      const Piece* piece = board(std::pair<char, char>(c, r));
      if (piece) {
        os << piece->to_ascii();
      } else {
        os << '-';
      }
    }
    os << std::endl;
  }
  return os;
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board() {}

Board::~Board() {

  map<pair<char,char>,Piece*>::iterator it;

  for (it = occ.begin(); it != occ.end(); ++it) {
    if(it->second) {
      delete (it->second);
      it->second = nullptr;
    }
  }
}

const Piece* Board::operator()(std::pair<char, char> position) const {
  if(occ.find(position) == occ.end()) {
    return nullptr; // checks if piece exists at that location, returns NULL if not
  }

  return occ.find(position)->second;
}

Piece* Board::get_piece(std::pair<char, char> position) {
  if(occ.find(position) == occ.end()) {
    return nullptr;
  }

  return occ.find(position)->second;
}

void Board::promote(std::pair<char, char> position) {
  Piece* p = get_piece(position);

  if((*this)(position) && (p->to_ascii() == 'P') && valid_pos(position) && position.second == '8') {
    delete p;
    place_piece(position, create_piece('Q'));
  }
  else if((*this)(position) && (p->to_ascii() == 'p') && valid_pos(position) && position.second == '1') {
    delete p;
    place_piece(position, create_piece('q'));
  }
}


bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
  bool not_piece = true;

  if(piece_designator == 'k' || piece_designator == 'K') {
    not_piece = false;
  } else if(piece_designator == 'Q' || piece_designator == 'q') {
    not_piece = false;
  } else if(piece_designator == 'B' || piece_designator == 'b') {
    not_piece = false;
  } else if(piece_designator == 'R' || piece_designator == 'r') {
    not_piece = false;
  } else if(piece_designator == 'N' || piece_designator == 'n') {
    not_piece = false;
  } else if(piece_designator == 'P' || piece_designator == 'p') {
    not_piece = false;
  } else if(piece_designator == 'M' || piece_designator == 'm') {
    not_piece = false;
  }

  if(not_piece) {
   return false;
  }

  if(!valid_pos(position)) {
    return false;
  }

  if(occ.find(position) != occ.end()) {
    return false;
  }
  
  occ[position] = create_piece(piece_designator);
  return true;
}

void Board::place_piece(std::pair<char, char> position, Piece* piece) {
  if(valid_pos(position)) {
    occ[position] = piece; // adds a piece at that position, creating a key if necessary
  }
}

void Board::remove_tile(std::pair<char, char> position) {
  std::map<std::pair<char,char>,Piece*>::iterator it = occ.find(position);

  if(it != occ.end()) {
    occ.erase(it); // if there is a key in the map at that position, erase it
  }
}


//return position of kings on board if they exist
std::pair<char,char> Board::find_king(bool white) const{
  if (!(*this).has_valid_kings()) {
    return std::make_pair('x', 'x');
  }

  std::map<std::pair<char,char>,Piece*>::const_iterator it;
  for (it = occ.cbegin(); it != occ.cend(); ++it) {
    if(it->second && white && it->second->to_ascii() == 'K') {
         return it->first;
       }
 
    if (it->second && !white && it->second->to_ascii() == 'k') {
          return it->first;
        }
  }

  //return invalid pair if no kings on board
  return std::make_pair('x','x');
}


bool Board::has_valid_kings() const {

  int num_kings = 0;
  int num_Kings = 0;

  std::map<std::pair<char,char>,Piece*>::const_iterator it;
  for(it = occ.cbegin(); it != occ.cend(); ++it) {
    if(it->second && it->second->to_ascii() == 'k') {
        num_kings++;
      }
    if(it->second && it->second->to_ascii() == 'K') {
      num_Kings++;
    }
  }

  return (num_kings == 1) && (num_Kings == 1);
}

void Board::display() const {

  //declare colors to be used from enumerated type in Terminal.h
  Terminal::Color white = Terminal::WHITE;
  Terminal::Color black = Terminal::BLACK;
  Terminal::Color red = Terminal::RED;
  Terminal::Color default_color = Terminal::DEFAULT_COLOR;
  int i =0;
  
  cout << " "; 
  for (char p = 'A'; p <= 'H'; p++) {
    Terminal::color_fg(false, black);
    cout << "\u202F";
    Terminal::color_fg(false, default_color);
    cout << p;
  }
   
  cout << endl;
   
  for(char r = '8'; r >= '1'; r--) {
    cout << r << " ";
    for(char c = 'A'; c <= 'H'; c++) {
      const Piece* piece = (*this)(std::pair<char, char>(c, r));
      //creates checkerboard pattern
      if (i%2 ==0) {
        Terminal::color_all(false, white, white);
      }
      if (i%2 == 1) {
        Terminal::color_all(false, red, red);
      }

      if (piece) {
        char piece_type = piece->to_ascii();
	//print corresponding unicode chess piece
	switch (piece_type){
          case 'K':
            Terminal::color_fg(false, black);
            std::cout << "\u2654";
            break;
          case 'Q':
            Terminal::color_fg(false, black);
            std::cout << "\u2655";
            break;
          case 'R':
            Terminal::color_fg(false, black);
            std::cout << "\u2656";
            break;
          case 'B':
            Terminal::color_fg(false, black);
            std::cout << "\u2657";
            break;
          case 'N':
            Terminal::color_fg(false, black);
            std::cout << "\u2658";
            break;
          case 'P':
            Terminal::color_fg(false, black);
            std::cout << "\u2659";
            break;
          case 'k':
            Terminal::color_fg(false, black);
            std::cout << "\u265A";
            break;
          case 'q':
            Terminal::color_fg(false, black);
            std::cout << "\u265B";
            break;
          case 'r':
            Terminal::color_fg(false, black);
            std::cout << "\u265C";
            break;
          case 'b':
            Terminal::color_fg(false, black);
            std::cout << "\u265D";
            break;
          case 'n':
            Terminal::color_fg(false, black);
            std::cout << "\u265E";
            break;
          case 'p':
            Terminal::color_fg(false, black);
            std::cout << "\u265F";
            break;
          default: ;
        }
        if (i%2 ==0) {
          Terminal::color_fg(false, red);
        }
        if (i%2 == 1) {
          Terminal::color_fg(false, white);
        }
	cout << "\u202F";
      }

      else {//if square is blank
	cout << "\u2588" << "\u2588";
      }

      i++;
    }
    Terminal::color_all(false, default_color, default_color);
    cout << std::endl;
    i++;
   }
}

bool Board::valid_pos(std::pair<char, char> pos) const {
  if(pos.first < 65 || pos.first > 72){ // checks if the end letter is between A-H
    return false; // returns false if piece is horizontally off the board
  }
  else if(pos.second < 49 || pos.second > 56){ // checks if the end number is between 1-8
    return false; // returns false if piece is vertically off the board
  }

  return true;
}


bool Board::is_clear(std::pair<char, char> start, std::pair<char, char> end) const {
  if(!((*this)(start))) {
    return false; // return false if there is no piece at the start position
  }
  if(!((*this)(start)->legal_move_shape(start,end) || (*this)(start)->legal_capture_shape(start,end))) {
    return false; // return false if it is not a legal move
  }
  if((*this)(end) && ((*this)(start)->is_white() == (*this)(end)->is_white())) {
    return false; // remove false if piece at end location is of same color
  }

  if((*this)(start)->to_ascii() == 'N' || (*this)(start)->to_ascii() == 'n'){
    return true; // knight can always move given end is free
  }
  

  int x_diff = end.first - start.first;
  int x_sign = 1;
  if(x_diff < 1){
    x_sign = -1;
  }

  int y_diff = end.second - start.second;
  int y_sign = 1;
  if(y_diff < 1){
    y_sign = -1;
  }

  if((*this)(start)->to_ascii() == 'K' || (*this)(start)->to_ascii() == 'k') {
    return true; // king can always move if end piece is open (within legal move range)
  }

  if((*this)(start)->to_ascii() == 'P' || (*this)(start)->to_ascii() == 'p') {
    if((*this)(end) && !((*this)(start)->legal_capture_shape(start, end))){
      return false;
    }
    if((int)abs(y_diff) == 2) {
      char hor_char = start.first;
      char ver_char = start.second + y_sign * 1;
      std::pair<char, char> pos (hor_char, ver_char);
      if((*this)(pos)) {
          return false;
      }
    }
    return true;
  }
  
  if((*this)(start)->to_ascii() == 'Q' || (*this)(start)->to_ascii() == 'q'
  || (*this)(start)->to_ascii() == 'M' || (*this)(start)->to_ascii() == 'm') {  // mystery is as powerful as queen, and then some
    if((int)abs(x_diff) == (int)abs(y_diff)) { // checks diagonals
      for(int i = 1; i < (int)abs(x_diff); i++) {
	char hor_char = start.first + x_sign * i;
	char ver_char = start.second + y_sign * i;
        std::pair<char, char> pos (hor_char, ver_char);
	if((*this)(pos)) {
	  return false;
	}
      }
    }

    if(x_diff == 0) { // checks in column movement
      for(int i = 1; i < (int)abs(y_diff); i++) {
        char ver_char = start.second + y_sign * i;
        std::pair<char, char> pos (start.first, ver_char);
        if((*this)(pos)) {
          return false;
        }
      }
    }

    if(y_diff == 0) { // checks in row movement
      for(int i = 1; i < (int)abs(x_diff); i++) {
        char hor_char = start.first + x_sign * i;
        std::pair<char, char> pos (hor_char, start.second);
        if((*this)(pos)) {
          return false;
        }
      }
    }
    return true;
  }

  if((*this)(start)->to_ascii() == 'B' || (*this)(start)->to_ascii() == 'b') {
    if((int)abs(x_diff) == (int)abs(y_diff)) { // checks diagonals
      for(int i = 1; i < (int)abs(x_diff); i++) {
        char hor_char = start.first + x_sign * i;
        char ver_char = start.second + y_sign * i;
        std::pair<char, char> pos (hor_char, ver_char);
        if((*this)(pos)) {
	  return false;
        }   
      }   
    }
    return true;
  }

  if((*this)(start)->to_ascii() == 'R' || (*this)(start)->to_ascii() == 'r') {
    if(x_diff == 0) { // checks in column movement
      for(int i = 1; i < (int)abs(y_diff); i++) {
        char ver_char = start.second + y_sign * i;
        std::pair<char, char> pos (start.first, ver_char);
        if((*this)(pos)) {
          return false;
        }   
      }   
    }   

    if(y_diff == 0) { // checks in row movement
      for(int i = 1; i < (int)abs(x_diff); i++) {
        char hor_char = start.first + x_sign * i;
        std::pair<char, char> pos (hor_char, start.second);
        if((*this)(pos)) {
          return false;
        }   
      }   
    }   
    return true;
  }

  return false; // returns false if none of the above cases are true
}

void Board::clear_board() {
  map<pair<char,char>,Piece*>::iterator it;

  for (it = occ.begin(); it != occ.end(); ++it) {
    if(it->second) {
      delete (it->second);
      it->second = nullptr;
    }
  }

  occ.clear();
}
