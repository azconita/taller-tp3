#include <string>
#include "version_client.h"

VersionClient::VersionClient(std::string hostname, std::string port) :
                            client(hostname, port) { }

void VersionClient::push_file(std::string filename, std::string hash) {
  this->client.send(1);
  this->client.send(filename);
  this->client.send(hash);
  int response = this->client.recv_respcode();
  if (response == 1) {
    this->client.send_file(filename);
  } else if (response == 0) {
    return;
  }
}

void save_file(std::string filename, std::string filecontent) {
  std::cout << "client pull tag: " << filename << '\n' << filecontent << '\n';
}

void VersionClient::pull_tag(std::string tag) {
  this->client.send(3);
  this->client.send(tag);
  if (this->client.recv_respcode() == 1) {
    int q = this->client.recv_tagquantity();
    for (size_t i = 0; i < q; ++i) {
      save_file(this->client.recv_filename(), this->client.recv_file());
    }
  }
}

void VersionClient::tag_hashes(std::string tag, std::vector<std::string> hashes) {
  this->client.send(2);
  this->client.send(hashes.size());
  this->client.send(tag);
  for (auto &h: hashes) {
    this->client.send(h);
  }
  int r = this->client.recv_respcode();
}
