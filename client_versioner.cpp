#include <string>
#include "client_versioner.h"

VersionClient::VersionClient(std::string hostname, std::string port) :
                            client(hostname, port) { }

void VersionClient::push_file(std::string filename, std::string hash) {
  std::cout << "[debug] [VersionClient] push_file: send 1\n";
  this->client.send_int(1);
  std::cout << "[debug] [VersionClient] push_file: send filename\n";
  this->client.send_string(filename);
  std::cout << "[debug] [VersionClient] push_file: send hash\n";
  this->client.send_string(hash);
  int response = this->client.recv_respcode();
  std::cout << "[debug] [VersionClient] push_file: respcode: " << response << "\n";
  if (response == 1) {
    std::cout << "[debug] [VersionClient] push_file: send file \n";
    this->client.send_file(filename);
  } else if (response == 0) {
    return;
  }
}

void save_file(std::string filename, std::string filecontent) {
  std::cout << "client pull tag: " << filename << '\n' << filecontent << '\n';
}

void VersionClient::pull_tag(std::string tag) {
  this->client.send_int(3);
  this->client.send_string(tag);
  if (this->client.recv_respcode() == 1) {
    int q = this->client.recv_tagquantity();
    for (int i = 0; i < q; ++i) {
      save_file(this->client.recv_filename(), this->client.recv_file());
    }
  }
}

void VersionClient::tag_hashes(std::string tag, std::vector<std::string> hashes) {
  this->client.send_int(2);
  this->client.send_int(hashes.size());
  this->client.send_string(tag);
  for (auto &h: hashes) {
    this->client.send_string(h);
  }
  int r = this->client.recv_respcode();
  std::cout << "[debug] [VersionClient] tag_hashes resp: " << r << "\n";
}
