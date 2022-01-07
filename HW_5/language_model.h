#ifndef LANGUAGE_MODEL
#define LANGUAGE_MODEL

#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

std::map<std::tuple<std::string, std::string, std::string>, int> trigrams(std::vector<std::vector<std::string>>);

void add_gram(std::map<std::tuple<std::string, std::string, std::string>, int> &trigrams, std::tuple<std::string, std::string, std::string> tup);

void asort(std::map<std::tuple<std::string, std::string, std::string>, int>);

void dsort(std::map<std::tuple<std::string, std::string, std::string>, int>);

void csort(std::map<std::tuple<std::string, std::string, std::string>, int>);

int fsort(std::map<std::tuple<std::string, std::string, std::string>, int>, std::string, std::string);

#endif
