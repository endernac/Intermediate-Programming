#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
  Chess chess;
  std::ifstream ifs;
  ifs.open("strange.txt");

  ifs >> chess;
  ifs.close();

  cout << chess << endl;

  chess.make_move(std::pair<char, char>('E','1'), std::pair<char, char>('E','2'));

  //it << chess.can_move_result(false) << endl;

//  delete &chess;
}
