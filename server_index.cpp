#include "server_index.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "server_tag.h"
#include "server_file.h"

Index::Index(const char* filename) : config_filename(filename) {
  //init maps with filename
  std::ifstream ifs_cfg;
  ifs_cfg.open(filename);
  std::string buf_str;
  while (std::getline(ifs_cfg, buf_str)) {
    buf_str.pop_back();
    char c = buf_str.front();
    buf_str.erase(0, 2);
    std::string name(buf_str.substr(0,buf_str.find_first_of(" ")));
    if (c == 'f') {
      this->files.emplace(name, File(buf_str));
    } else if (c == 't') {
      this->tags.emplace(name, Tag(buf_str));
    }
  }
}

Index::~Index() {
  //save index in file
  std::ofstream ofile(this->config_filename);
  for (auto &par: this->files) {
    ofile << par.second << ";\n";
  }
  for (auto &par: this->tags) {
    ofile << par.second << ";\n";
  }
}

bool Index::file_has_hash(std::string &filename, std::string &hash) {
  std::map<std::string, File>::iterator it = this->files.find(filename);
  if (it == this->files.end())   {
    return false;
  } else if (it->second.has_hash(hash)) {
    return true;
  } else {
    return false;
  }
  //return (it != this->files.end()) ? it->second.has_hash(hash) : false;
}

void Index::add_file_hash(std::string &filename, std::string &hash) {
  std::map<std::string, File>::iterator it = this->files.find(filename);
  if (it != this->files.end()) {
    it->second.add_hash(hash);
  } else {
    this->files.emplace(filename, File(filename, hash));
  }
}

bool Index::file_add_hash_if_possible(std::string &filename,
                                      std::string &hash) {
  std::unique_lock<std::mutex> l(this->m);
  if (this->file_has_hash(filename, hash))
    return false;
  this->add_file_hash(filename, hash);
  return true;
}

bool Index::tag_exists(std::string &tag) {
  return (this->tags.find(tag) != this->tags.end());
}

std::vector<std::string> Index::get_files_with_tag(std::string &tag) {
  std::unique_lock<std::mutex> l(this->m);
  if (this->tag_exists(tag))
    return this->tags.find(tag)->second.get_files();
  else
    return std::vector<std::string>();
}


bool Index::add_tag_if_possible(std::string &tag,
                              std::vector<std::string> &hashes) {
  std::unique_lock<std::mutex> l(this->m);
  for (auto &h: hashes) {
    bool found = false;
    for (auto &f: this->files) {
      if (f.second.has_hash(h)) {
        found = true;
      }
    }
    if (!found)
      return false;
  }
  if (this->tags.find(tag) != this->tags.end()) {
    //tag exists
    return false;
  }
  this->tags.emplace(tag, Tag(tag, hashes));
  return true;
}

bool Index::hash_exists(std::string &hash) {
  std::unique_lock<std::mutex> l(this->m);
  for (auto &f: this->files) {
    if (f.second.has_hash(hash))
      return true;
  }
  return false;
}

std::string Index::get_filename_of_hash(std::string &hash) {
  for (auto &f: this->files) {
    if (f.second.has_hash(hash))
      return f.first;
  }
  return std::string("");
}
