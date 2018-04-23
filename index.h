#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include "tag.h"
#include "file.h"

class Index {
 private:
  const std::string config_filename;
  std::map<std::string, Tag> tags;
  std::map<std::string, File> files;
 public:
  Index(const char* filename);
  virtual ~Index();
  void push_file(std::string filename, std::string hash);
  void tag_hashes(std::string tagname, std::list<std::string> hashes);
  std::vector<std::string> pull_hashes(std::string tagname);
};

#endif
