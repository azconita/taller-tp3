#include "server_index.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "server_tag.h"
#include "server_file.h"

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
  std::ofstream ofile(this->config_filename);
  for(auto &par: this->files) {
    ofile << "f " << par.first << par.second.hashes_to_str() << ";\n";
  }
  for(auto &par: this->tags) {
    ofile << "t " << par.first << par.second.hashes_to_str() << ";\n";
  }
}

bool Index::file_has_hash(std::string filename, std::string hash) {
  std::unique_lock<std::mutex> l(this->m);
  std::map<std::string, File>::iterator it = this->files.find(filename);
  return (it != this->files.end()) ? it->second.has_hash(hash) : false;
}

void Index::add_file_hash(std::string filename, std::string hash) {
  std::unique_lock<std::mutex> l(this->m);
  this->files.find(filename)->second.add_hash(hash);
}

bool Index::tag_exists(std::string tag) {
  std::unique_lock<std::mutex> l(this->m);
  return (this->tags.find(tag) != this->tags.end());
}

std::vector<std::string> Index::get_files_with_tag(std::string tag) {
  std::unique_lock<std::mutex> l(this->m);
  return this->tags.find(tag)->second.get_files();
}

void Index::create_tag_with_hashes(std::string tag, std::vector<std::string> hashes) {
  std::unique_lock<std::mutex> l(this->m);
  this->tags.emplace(tag, Tag(tag, hashes));
}

bool Index::hash_exists(std::string hash) {
  std::unique_lock<std::mutex> l(this->m);
  for (auto &f: this->files) {
    if (f.second.has_hash(hash))
      return true;
  }
  return false;
}