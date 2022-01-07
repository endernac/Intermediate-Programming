#include "Board.h"
#include <iostream>
#include <assert.h>

using std::cout; using std::endl;
using std::pair;

int main() {
  Board board;

  for (int i = 0; i < 8; i++) {
    board.add_piece(std::pair<char, char>('A' + 0, '1' + i), 'P');
    board.add_piece(std::pair<char, char>('A' + 1, '1' + i), 'p');
    board.add_piece(std::pair<char, char>('A' + 2, '1' + i), 'P');
    board.add_piece(std::pair<char, char>('A' + 3, '1' + i), 'p');
    board.add_piece(std::pair<char, char>('A' + 4, '1' + i), 'P');
    board.add_piece(std::pair<char, char>('A' + 5, '1' + i), 'p');
    board.add_piece(std::pair<char, char>('A' + 6, '1' + i), 'P');
    board.add_piece(std::pair<char, char>('A' + 7, '1' + i), 'p');
  }

  cout << board << endl;

  for(int i = '1'; i <= '8'; i++) {
    for(int j = 'A'; j <= 'H'; j++) {
      std::pair<char, char> tile (j, i);
      board.promote(tile);
    }
  }

  cout << board << endl;
/*
  cout << "after only adding pawns, board.has_valid_kings(): " << endl
  << board.has_valid_kings() << endl << endl;

  // Add the rooks
  board.add_piece(pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
  board.add_piece(pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
  board.add_piece(pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
  board.add_piece(pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

  // Add the knights
  board.add_piece(pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
  board.add_piece(pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
  board.add_piece(pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
  board.add_piece(pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

  // Add the bishops
  board.add_piece(pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
  board.add_piece(pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
  board.add_piece(pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
  board.add_piece(pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

  // Add the kings and queens
  board.add_piece(pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
  board.add_piece(pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );

  cout << "after adding one (white) pair of king/queen, board.has_valid_kings(): 0 = " << endl
  << board.has_valid_kings() << endl << endl;

  board.add_piece(pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
  board.add_piece(pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );

  cout << "after adding both pairs of king/queen, board.has_valid_kings(): 1 = " << endl
  << board.has_valid_kings() << endl << endl;

  pair<char, char> k_b = board.find_king(false);
  cout << "black king's location: " << endl
  << "E8 = " << k_b.first << k_b.second << endl << endl;

  pair<char, char> K = board.find_king(true);
  cout << "white king's location: " << endl
  << "E1 = " << K.first << K.second << endl << endl;

  board.add_piece(pair<char, char>( 'A'+4 , '1'+5 ) , 'k' );

  cout << "adding a third king, board.has_valid_kings(), 0 = " << endl
  << board.has_valid_kings() << endl << endl;

  cout << board;

  cout << endl;

  board.display();

  cout << "checking is_clear" << endl
  << "P B2B3: " << board.is_clear(pair<char, char>('B', '2'), pair<char, char>('B', '3')) << endl
  << "R A1A4: " << board.is_clear(pair<char, char>('A', '1'), pair<char, char>('A', '4')) << endl
  << "N B1C3: " << board.is_clear(pair<char, char>('B', '1'), pair<char, char>('C', '3')) << endl
  << "B C1E3: " << board.is_clear(pair<char, char>('C', '1'), pair<char, char>('E', '3')) << endl
  << "Q D1E2: " << board.is_clear(pair<char, char>('D', '1'), pair<char, char>('D', '8')) << endl
  << "K E1E2: " << board.is_clear(pair<char, char>('E', '1'), pair<char, char>('E', '2')) << endl;

  for(char r = '8'; r >= '1'; r--) {
    for(char c = 'A'; c <= 'H'; c++) {
      pair<char, char> pos = pair<char, char>(c, r);
      assert(board.valid_pos(pos));
    }
  }


  for(char r = '9'; r >= '0'; r--) {
    for(char c = '1'; c <= '8'; c++) {
      pair<char, char> pos = pair<char, char>(c, r);
      assert(!board.valid_pos(pos));
    }
  }

  for(char r = '6'; r >= '8'; r--) {
    for(char c = 'A'; c <= 'H'; c++) {
      pair<char, char> pos = pair<char, char>(c, r);
      assert(!board.valid_pos(pos));
    }
  }

  for(char r = '8'; r >= '1'; r--) {
    for(char c = 'a'; c <= 'h'; c++) {
      pair<char, char> pos = pair<char, char>(c, r);
      assert(!board.valid_pos(pos));
    }
  }

  assert(!board.valid_pos(pair<char, char>('0', 'A')));

  for(char r = '8'; r >= '2'; r--) {
    for(char c = 'I'; c <= 'Q'; c++) {
      pair<char, char> pos = pair<char, char>(c, r);
      assert(!board.valid_pos(pos));
    }
  }

  cout << "assertions passed " << endl;

  cout << "Add Piece onto another: " << endl
  << "0 = " << board.add_piece(pair<char, char>( 'A'+5 , '1'+7 ) , 'b' ) << endl;

  pair<char, char> k = board.find_king(false);
  cout << "find_kings with two kings" << endl
  << "xx = " << k.first << k.second << endl;
*/
 board.clear_board();
}
