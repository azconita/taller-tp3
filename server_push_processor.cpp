#include "server_push_processor.h"

void PushProcessor::run() {
  std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
            << "] run" << '\n';
  std::string filename = this->client.recv_string();
  std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
            << "] run: recv filename: " << filename << '\n';
  std::string hash = this->client.recv_string();
  std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
            << "] run: recv hash: " << hash << '\n';
  if(!this->index.file_add_hash_if_possible(filename, hash)) {
    std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
              << "] run: ya esta el archivo en el server" << '\n';
    this->client.send_int(0);
  } else {
    std::cout << "[debug] [PushProcessor] [thread:" << this->get_id()
              << "] run: no esta el archivo en el server" << '\n';
    //se debe retornar 1 al cliente
    this->client.send_int(1);
    this->client.recv_file(hash);
  }
  this->finished = true;
  this->client.shut();
}
