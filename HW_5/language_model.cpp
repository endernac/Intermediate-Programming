#include <map>
#include <tuple>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include "language_model.h"

using std::string;
using std::vector;
using std::tuple;
using std::map;
using std::endl;
using std::cout;

void add_gram(map<tuple<string, string, string>, int> &trigrams, tuple<string, string, string> tup) {
  if(trigrams.find(tup) == trigrams.end()) {
    trigrams[tup] = 1;
  } 
  else {
    trigrams[tup] = trigrams[tup] + 1;
  }
}


map<tuple<string, string, string>, int> trigrams(vector<vector<string>> data) {
  map<tuple<string, string, string>, int> tri;

  for(vector<vector<string>>::iterator i = data.begin(); i != data.end(); ++i) {
    int s = (*i).size();

    for(int j = 0; j < s-2; j++) {
      
      add_gram(tri, std::make_tuple((*i)[j], (*i)[j+1], (*i)[j+2]));
    }
  }
 
  return tri;
}




void asort(map<tuple<string, string, string>, int> tri) {
  for(map<tuple<string, string, string>, int>::iterator i = tri.begin(); i != tri.end(); ++i) {
    cout << i->second << " - [" << std::get<0>(i->first) << " " <<  std::get<1>(i->first) << " " <<  std::get<2>(i->first) << "]" << endl;
  }
}

void dsort(map<tuple<string, string, string>, int> tri) {
  for(map<tuple<string, string, string>, int>::reverse_iterator i = tri.rbegin(); i != tri.rend(); ++i) {
    cout << i->second << " - [" << std::get<0>(i->first) << " " <<  std::get<1>(i->first) << " " <<  std::get<2>(i->first) << "]" << endl;
  }
}

void csort(map<tuple<string, string, string>, int> tri) {
  int max = 0;
  for(map<tuple<string, string, string>, int>::iterator i = tri.begin(); i != tri.end(); ++i) {
    if(i->second > max)
      max = i->second;
  }

  for(int freq = max; freq > 0; freq--) {
    for(map<tuple<string, string, string>, int>::iterator i = tri.begin(); i != tri.end(); ++i) {
      if(i->second == freq) {
        cout << i->second << " - [" << std::get<0>(i->first) << " " <<  std::get<1>(i->first) << " " <<  std::get<2>(i->first) << "]" << endl;
      }
    }
  }
}

int fsort(map<tuple<string, string, string>, int> tri, string s1, string s2) {
  int max = 0;
  for(map<tuple<string, string, string>, int>::iterator i = tri.begin(); i != tri.end(); ++i) {
    if(i->second > max)
      max = i->second;
  }

  for(int freq = max; freq > 0; freq--) {
    for(map<tuple<string, string, string>, int>::iterator i = tri.begin(); i != tri.end(); ++i) {
      if(i->second == freq && std::get<0>(i->first) == s1 && std::get<1>(i->first) == s2) {
        cout << i->second << " - [" << std::get<0>(i->first) << " " <<  std::get<1>(i->first) << " " <<  std::get<2>(i->first) << "]" << endl;
	return 1;
      }
    }
  }
  return 0;
}
