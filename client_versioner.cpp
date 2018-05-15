#include <string>
#include <vector>
#include "client_versioner.h"

VersionClient::VersionClient(const char *hostname, const char* port) :
                            client(hostname, port) { }

void VersionClient::push_file(std::string &filename, std::string &hash) {
  this->client.send_int(1);
  this->client.send_string(filename);
  this->client.send_string(hash);
  int response = this->client.recv_respcode();
  if (response == 1) {
    this->client.send_file(filename);
  } else if (response == 0) {
    return;
  }
}

void VersionClient::pull_tag(std::string &tag) {
  this->client.send_int(3);
  this->client.send_string(tag);
  if (this->client.recv_respcode() == 1) {
    int q = this->client.recv_tagquantity();
    for (int i = 0; i < q; ++i) {
      std::string filename = this->client.recv_filename();
      std::string fname(filename + "." + tag);
      this->client.recv_file(fname);
    }
  } else {
    std::cout << "Error: tag/hash incorrecto." << '\n';
  }
}

void VersionClient::tag_hashes(std::string &tag,
                               std::vector<std::string> &hashes) {
  this->client.send_int(2);
  this->client.send_int(hashes.size());
  this->client.send_string(tag);
  for (auto &h: hashes) {
    this->client.send_string(h);
  }
  if (this->client.recv_respcode() == 0)
    std::cout << "Error: tag/hash incorrecto." << '\n';
}
