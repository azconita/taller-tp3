#ifndef TAG_H
#define TAG_H

#include <string>
#include <vector>

class Tag {
private:
  std::string name;
  std::vector<std::string> hashes;

public:
  Tag(std::string line);
  Tag(Tag &&other);
  Tag(std::string t, std::vector<std::string> v) : name(t), hashes(v) {}
  virtual ~Tag() {}
  void print(std::ostream s);
  std::string hashes_to_str();
  std::vector<std::string> get_files();
  std::string get_name();
};

std::ofstream& operator<<(std::ofstream &os, Tag& t);

#endif
