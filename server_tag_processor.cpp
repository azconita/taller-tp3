#include "server_tag_processor.h"
#include <string>
#include <vector>

void TagProcessor::run() {
  //recibir cantidad de hashes a tagear
  int hash_quantity = this->client.recv_int();
  //recibir tag
  std::string tag = this->client.recv_string();
  std::vector<std::string> hashes;
  //recibir hashes
  for (int i = 0; i < hash_quantity; ++i) {
    hashes.push_back(this->client.recv_string());
  }
  //intentar agregar tag con los hashes al index y avisar al cliente
  if (this->index.add_tag_if_possible(tag, hashes))
    this->client.send_int(RETURN_CODE_OK); //se pudo agregar
  else
    this->client.send_int(RETURN_CODE_FAIL); //no se pudo agregar
  this->finished = true;
  this->client.shut();
}
