#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/*Componente del Index
  contiene hashes asociados a un archivo con nombre determinado*/
class File {
private:
  std::string name;
  std::vector<std::string> hashes;

public:
  explicit File(std::string &line);
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
