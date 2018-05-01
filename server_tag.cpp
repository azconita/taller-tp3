#include "server_tag.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

Tag::Tag(std::string line) {
  this->name = line.substr(0, line.find_first_of(" "));
  line = line.substr(line.find_first_of(" "));
  std::istringstream iss(line);
  copy(std::istream_iterator<std::string>(iss),
       std::istream_iterator<std::string>(),
       back_inserter(this->hashes));
}

Tag::Tag(Tag &&other) : name(other.name), hashes(std::move(other.hashes)) {
}

void pr(std::string s) {
  std::cout << s << "\n";
}

void Tag::print(std::ostream s) {
  pr(this->name);
  std::for_each(this->hashes.begin(),this->hashes.end(), pr);
}

std::string Tag::hashes_to_str() {
  std::string r(" ");
  for (auto &h:this->hashes) {
    r += h;
    r += " ";
  }
  return r;
}

std::vector<std::string> Tag::get_files() {
  return this->hashes;
}
