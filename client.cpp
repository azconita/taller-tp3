#include <string>
#include "client.h"

void Client::push_file(std::string filename, std::string hash) {
  this->server.send(1);
  this->server.send(filename);
  this->server.send(hash);
  int response = this->server.recv_respcode();
  if (response == 1) {
    this->server.send_file(filename);
  } else if (response == 0) {
    return;
  }
}

void save_file(std::string filename, std::string filecontent) {
  std::cout << "client pull tag: " << filename << '\n' << filecontent << '\n';
}

void Client::pull_tag(std::string tag) {
  this->server.send(3);
  this->server.send(tag);
  if (this->server.recv_respcode() == 1) {
    int q = this->server.recv_tagquantity();
    for (size_t i = 0; i < q; ++i) {
      save_file(this->server.recv_filename(), this->server.recv_file());
    }
  }
}

void Client::tag_hashes(std::string tag, std::vector<std::string> hashes) {
  this->server.send(2);
  this->server.send(hashes.size());
  this->server.send(tag);
  for (auto &h: hashes) {
    this->server.send(h);
  }
  int r = this->server.recv_respcode();
}

int main(int argc, char const *argv[]) {
  Client client(argv[1], std::stoi(argv[2]));
  client.push_file(argv[4], argv[5]);
  client.pull_tag(argv[4]);
  std::vector<std::string> v;
  v.push_back(argv[5]);
  v.push_back(argv[6]);
  client.tag_hashes(argv[4], v);
  return 0;
}
