#include "server_tag_processor.h"

void TagProcessor::run() {
  int hash_quantity = this->client.recv_int();
  std::string tag = this->client.recv_string();
  std::vector<std::string> hashes;
  for (int i = 0; i < hash_quantity; ++i) {
    hashes.push_back(this->client.recv_string());
  }
  if (this->index.add_tag_if_possible(tag, hashes))
    this->client.send_int(1);
  else
    this->client.send_int(0);
  this->finished = true;
  this->client.shut();
}
