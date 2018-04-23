#include "file.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

File::File(std::string line) {
  this->name = line.substr(0, line.find_first_of(" "));
  line = line.substr(line.find_first_of(" "));
  std::istringstream iss(line);
  copy(std::istream_iterator<std::string>(iss),
       std::istream_iterator<std::string>(),
       back_inserter(this->hashes));
}

File::File(File &&other) : name(other.name), hashes(std::move(other.hashes)) {
}

void p(std::string s) {
  std::cout << s << "\n";
}

void File::print(std::ostream s) {
  p(this->name);
  std::for_each(this->hashes.begin(),this->hashes.end(), p);
}
