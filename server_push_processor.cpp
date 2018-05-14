#include "server_push_processor.h"

void PushProcessor::run() {
  std::string filename = this->client.recv_string();
  std::string hash = this->client.recv_string();
  if(!this->index.file_add_hash_if_possible(filename, hash)) {
    this->client.send_int(0);
  } else {
    //se debe retornar 1 al cliente
    this->client.send_int(1);
    this->client.recv_file(hash);
  }
  this->finished = true;
  this->client.shut();
}
