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
  virtual ~Tag() {}
  void print(std::ostream s);
};

#endif
