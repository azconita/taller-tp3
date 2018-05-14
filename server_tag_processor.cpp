#include "server_tag_processor.h"

void TagProcessor::run() {
  std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
            << "] run" << '\n';
  int hash_quantity = this->client.recv_int();
  std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
            << "] hash quantity: " << hash_quantity << '\n';
  std::string tag = this->client.recv_string();
  std::cout << "[debug] [TagProcessor] [thread:" << this->get_id()
            << "] tag: " << tag << '\n';
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
