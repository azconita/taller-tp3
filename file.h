#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

class File { // TODO: que herede de otra clase junto con Tag
private:
  std::string name;
  std::vector<std::string> hashes;

public:
  File(std::string line);
  File(File &&other);
  virtual ~File() {}
  void print(std::ostream s);//TODO: sobrescribir <<
};

#endif
