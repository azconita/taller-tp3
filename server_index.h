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
  explicit Index(const char* filename);
  virtual ~Index();

  bool file_add_hash_if_possible(std::string &filename, std::string &hash);
  std::vector<std::string> get_files_with_tag(std::string &tag);
  std::string get_filename_of_hash(std::string &hash);
  bool add_tag_if_possible(std::string &tag, std::vector<std::string> &hashes);
 private:
  bool hash_exists(std::string &hash);
  bool tag_exists(std::string &tag);
  void add_file_hash(std::string &filename, std::string &hash);
  bool file_has_hash(std::string &filename, std::string &hash);
};

#endif
