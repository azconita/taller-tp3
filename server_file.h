#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class File { // TODO: que herede de otra clase junto con Tag
private:
  std::string name;
  std::vector<std::string> hashes;

public:
  File(std::string &line);
  File(std::string &name, std::string &hash);
  File(File &&other);
  virtual ~File() {}

  bool has_hash(std::string &hash);
  void add_hash(std::string &hash);
  void print(std::ostream s);
  std::string hashes_to_str();
   std::string get_name();
};

std::ofstream& operator<<(std::ofstream &os,  File& f);
std::ostream& operator<<(std::ostream &os,  File& f);
#endif
