#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "server_tag.h"
#include "server_file.h"

class Index {
 private:
  std::mutex m;
  std::condition_variable cv;
  const std::string config_filename;
  std::map<std::string, Tag> tags;
  std::map<std::string, File> files;
 public:
  Index(const char* filename);
  virtual ~Index();
  //void push_file(std::string filename, std::string hash);
  //void tag_hashes(std::string tagname, std::list<std::string> hashes);
  //std::vector<std::string> pull_hashes(std::string tagname);
  bool file_has_hash(std::string filename, std::string hash);
  void add_file_hash(std::string filename, std::string hash);
  bool tag_exists(std::string tag);
  std::vector<std::string> get_files_with_tag(std::string tag);
  void create_tag_with_hashes(std::string tag, std::vector<std::string> v);
  bool hash_exists(std::string hash);
  std::string get_filename_of_hash(std::string hash);
};

#endif
