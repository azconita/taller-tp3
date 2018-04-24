#include "index.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "tag.h"
#include "file.h"

Index::Index(const char* filename) : config_filename(filename) {
  //init maps with filename
  std::ifstream ifs_cfg(filename);
  while (ifs_cfg.peek() != EOF) {
    std::string buf_str;
    std::getline(ifs_cfg, buf_str);
    buf_str.pop_back();
    char c = buf_str.front();
    buf_str.erase(0, 2);
    if (c == 'f') {
      files.emplace(buf_str.substr(0,buf_str.find_first_of(" ")), File(buf_str));
    } else if (c == 't') {
      tags.emplace(buf_str.substr(0,buf_str.find_first_of(" ")), Tag(buf_str));
    }
  }
  //std::for_each(this->files.begin(),this->files.end(), print);

}

Index::~Index() {
  //save index in file
  /*for(auto &par: this->files) {
    std::cout << par.first << '\n';
    par.second.print();
  }
  for(auto &par: this->tags) {
    std::cout << par.first << '\n';
    par.second.print();
  }*/
}

bool Index::file_has_hash(std::string filename, std::string hash) {
  std::map<std::string, File>::iterator it = this->files.find(filename);
  return (it != this->files.end()) ? it->second.has_hash(hash) : false;
}

void Index::add_file_hash(std::string filename, std::string hash) {
  this->files.find(filename)->second.add_hash(hash);
}

bool Index::tag_exists(std::string tag) {
  return (this->tags.find(tag) != this->tags.end());
}

std::vector<std::string> Index::get_files_with_tag(std::string tag) {
  return this->tags.find(tag)->second.get_files();
}

void Index::create_tag_with_hashes(std::string tag, std::vector<std::string> hashes) {
  this->tags.emplace(tag, Tag(tag, hashes));
}

bool Index::hash_exists(std::string hash) {
  for (auto &f: this->files) {
    if (f.second.has_hash(hash))
      return true;
  }
  return false;
}
