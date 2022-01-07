#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <tuple>
#include "language_model.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::tuple;

int main(int argc, char *argv[]) {
  if(argc < 2) {
    std::cerr << "Invalid file list: " << endl;
    return 1;
  }
  std::ifstream ifile(argv[1]);
  if(!ifile.is_open()) {
    std::cerr << "Invalid file list: " << argv[1] << endl;
    return 0;
  }
  
  string file;
  vector<vector<string> > training_data;
  
  while(ifile >> file) {

    std::ifstream ifile(file);

    if(!ifile.is_open()) {
      std::cerr << "Invalid file: "  << file << endl;
    } else {

      std::string word;
      vector<string> list;

      list.insert(list.begin(), "<START_2>");
      list.insert(list.begin(), "<START_1>");
      
      while(ifile >> word) {
        list.push_back(word);
      }

      list.push_back("<END_1>");
      list.push_back("<END_2>");

      training_data.push_back(list);
    }

  }

  map<tuple<string, string, string>, int> tri = trigrams(training_data);

  if(argc < 3) {
    std::cerr << "Invalid command: valid options are a, d, c, and f" << endl;
    return 1;
  }
  else if (strcmp(argv[2], "a") == 0) {
    asort(tri);
  } 
  else if (strcmp(argv[2], "d") == 0) {
    dsort(tri);
  }
  else if (strcmp(argv[2], "c") == 0) {
    csort(tri);
  }
  else if (strcmp(argv[2], "f") == 0) {
    if(argc < 5) {
      std::cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
    }
    else { 
      if (fsort(tri, argv[3], argv[4]) == 0) {
        cout << "No trigrams of the form [" << argv[3] << " " << argv[4] <<" ?] appear" << endl;
      }
    }
  } 
  else {
    std::cerr << "Invalid command: valid options are a, d, c, and f" << endl;
    return 0;
  }
  
  return 0;
  
}
