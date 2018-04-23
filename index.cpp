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
