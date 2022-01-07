// Rebecca Yu, ryu16
// Andrew Cornelio, acornel9
// Arjun Somayazulu, asomaya1

#include "Board.h"
#include "Chess.h"
#include <iostream>

using std::cout; using std::endl;
using std::cerr;
using std::map; using std::pair;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess() : is_white_turn(true) {
  // Add the pawns
  for (int i = 0; i < 8; i++) {
    board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
    board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
  }

  // Add the rooks
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

  // Add the knights
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

  // Add the bishops
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

  // Add the kings and queens
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
}

void Chess::can_move(bool white) {
  white_can_move = false;  // pieces can't move until at least one legal move is found
  black_can_move = false;

  map<pair<char,char>,Piece*>::const_iterator it;
  const map<pair<char,char>,Piece*> ledger = board.get_map();

  for (it = ledger.cbegin(); it != ledger.cend(); ++it) {

    if(it->second && white == it->second->is_white()){  // make sure you check the correct color
      for(char r = '8'; r >= '1'; r--) {
        for(char c = 'A'; c <= 'H'; c++) {
	  
          std::pair<char, char> space (c, r);
          bool legal_moves = true;
            if(not_legal_move(it->first, space)){
              legal_moves = false;
            }
	  
          if(legal_moves && white) {
	    white_can_move = true;
            return;
          } else if(legal_moves && !white) {
            black_can_move = true;
            return;
          }
        }
      }
    }
  }
}

bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
  int err_val = not_legal_move(start, end);
  if(err_val) { 
    switch(err_val){
      case 1:
        cerr << "Please input valid board locations." << endl << endl;
        break;
      case 2:
        cerr << "There is no piece at that specified location." << endl << endl;
        break;
      case 3:
        cerr << "That is not a ";
        if(is_white_turn){
          cerr << "white piece." << endl << endl;
        }   
        else{
          cerr << "black piece." << endl << endl;
        }
        break;  
      case 4:
        cerr << "That is not a valid move." << endl << endl;
        break;
      case 5:
        cerr << "There is nothing to capture." << endl << endl;
        break;
      case 6:
        cerr << "There are pieces in the way." << endl << endl;
        break;
      case 7:
        cerr << "That move puts you in check." << endl << endl;
        break;
      default: ;
    }
    return false;  // make sure the move is valid
  }

  delete board.get_piece(end);  // rdelete the piece at the end for a capture
  board.place_piece(end, board.get_piece(start));  // place the starting piece at the end
  board.remove_tile(start);  // remove the starting tile to prevent duplication

  board.promote(end);  // promote the piece if it's a pawn

  is_white_turn = !is_white_turn; // Change whose turn it is
  can_move(is_white_turn);  // see if the next poor sap can move after this move

  cout << endl;

  return true;
}

int Chess::not_legal_move(std::pair<char, char> start, std::pair<char, char> end){ // returns error values from make_move OR 7 if in check
  int err_val = naive_move(start, end, is_white_turn);
  if(err_val){  // make sure the geometry of the move is correct
    return err_val;
  }

  bool check = false;  // start out by saying the move doesn't cause a check

  Piece* piece_1 = board.get_piece(start);
  Piece* piece_2 = board.get_piece(end);

  board.place_piece(end, piece_1);  // place first piece on second piece's tile 
  board.remove_tile(start);  // remove the starting piece

  if(in_check(is_white_turn)) {
    check = true; // if the new config causes a check
  }

  board.place_piece(start, piece_1);  // reset pieces
  board.place_piece(end, piece_2);

  if(check == true){
    return 7; //if the move causes a check on yourself, it's not legal
  }  
  return 0; 
}

bool Chess::in_check(bool white) const {

  map<pair<char,char>,Piece*>::const_iterator it;
  const map<pair<char,char>,Piece*> ledger = board.get_map();
  pair<char,char> end = board.find_king(white);

  for (it = ledger.cbegin(); it != ledger.cend(); ++it) {

    // Only consider pieces of opposite color as current
    if(it->second && it->second->is_white() != white) {

      pair<char,char> start = it->first;

      //can opponent make a move that would put himself in check?
      //check for stalemate
      if(!naive_move(start, end, !is_white_turn)) {
        return true;
      }
    }
  }

  return false;
}


bool Chess::in_mate(bool white) const {
  if(!in_check(white)){
    return false;
  }
  if(white){
    return !white_can_move;  // if it can't move and it's in a check, then it's checkmate
  }
  else{
    return !black_can_move;
  }
  return false;
}


bool Chess::in_stalemate(bool white) const {
  if(in_check(white)){
    return false;
  }

  if(white){
    return !white_can_move;  // if player can't move and not in a check, it's a stalemate
  }
  else{
    return !black_can_move;
  }
  return false;
}

int Chess::naive_move(std::pair<char, char> start, std::pair<char, char> end, bool white) const {
  if(start.first < 65 || end.first < 65 || start.first > 73 || end.first > 73 ||
     start.second < 49 || end.second < 49 || start.second > 56 || end.second > 56){
       return 1;
  }
  if(!board(start)) {
    return 2;  // nothing in the starting position/starting position not valid
  }
  if(white != board(start)->is_white()) {
    return 3; // trying to move the other player's pieces (u sly dawg)		  
  }
  if(!board.valid_pos(end) || (!board(start)->legal_move_shape(start, end) && !board(start)->legal_capture_shape(start,end))) {
    return 4; // end positon off board or not valid as either a move shape or capture shape
  }
  if(!board(end) && !(board(start)->legal_move_shape(start, end))){
    return 5; // can't capture an empty tile (if capture different from regular move)
  }
  if(!board.is_clear(start,end)){
    return 6; // white or black pieces blocking move
  }
  return 0; 
}

bool Chess::can_move_result(bool white) {
  if(white) {
    return white_can_move;
  }
  else {
    return black_can_move;
  }
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<< (std::ostream& os, const Chess& chess) {
  // Write the board out and then either the character 'w' or the character 'b',
  // depending on whose turn it is
  return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}


std::istream& operator>> (std::istream& is, Chess& chess) {
  chess.wipe_board();
  char p;

  for(char r = '8'; r >= '1'; r--) {
    for(char c = 'A'; c <= 'H'; c++) {
      is >> p;
      if(p == '\n' || p == '-') {
        continue;
      } else {//add piece to blank board
	std::pair<char, char> space (c, r);
	chess.mod_board(space, p);
      }
    }
  }

  is >> p;
  //read whose turn it is 
  if(p == 'w') {
    chess.set_turn(true);
  } else if(p == 'b') {
    chess.set_turn(false);
  }

  chess.can_move(chess.turn_white());

  return is;
}

void Chess::wipe_board() {
  board.clear_board(); 
}
