#include "server_push_processor.h"
#include <string>

void PushProcessor::run() {
  //recibir nombre de archivo del cliente
  std::string filename = this->client.recv_string();
  //recibir hash nuevo del cliente
  std::string hash = this->client.recv_string();
  //intentar agregar al index si el hasho no existe
  if (!this->index.file_add_hash_if_possible(filename, hash)) {
    //si no se puede, avisar al cliente
    this->client.send_int(RETURN_CODE_FAIL);
  } else {
    //si se puede, recibir archivo y guardarlo
    this->client.send_int(RETURN_CODE_OK);
    this->client.recv_file(hash);
  }
  this->finished = true;
  this->client.shut();
}
