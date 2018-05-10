#include "server_file.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

File::File(std::string line) {
  this->name = line.substr(0, line.find_first_of(" "));
  line = line.substr(line.find_first_of(" "));
  std::istringstream iss(line);
  copy(std::istream_iterator<std::string>(iss),
       std::istream_iterator<std::string>(),
       back_inserter(this->hashes));
}

File::File(std::string name, std::string hash) : name(name), hashes(1,hash) {

}


File::File(File &&other) : name(other.name), hashes(std::move(other.hashes)) {
}

void p(std::string s) {
  std::cout << s << "\n";
}

std::string File::hashes_to_str() {
  std::string r(" ");
  for (auto &h:this->hashes) {
    r += h;
    r += " ";
  }
  return r;
}

void File::print(std::ostream s) {
  p(this->name);
  std::for_each(this->hashes.begin(),this->hashes.end(), p);
}

bool File::has_hash(std::string hash) {
  return (std::find(this->hashes.begin(),this->hashes.end(),hash)
              != this->hashes.end());
}

void File::add_hash(std::string hash) {
  this->hashes.push_back(hash);
}

std::string File::get_name() {
  return this->name;
}

std::ofstream& operator<<(std::ofstream &os,  File& f) {
  os << "f " << f.get_name() << f.hashes_to_str();
  return os;
}
