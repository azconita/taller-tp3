#include "server_pull_processor.h"
#include <string>
#include <vector>

void PullProcessor::run() {
  //recibir tag del cliente
  std::string tag = this->client.recv_string();
  //buscar hashes asociados al tag
  std::vector<std::string> files = this->index.get_files_with_tag(tag);
  if (!files.empty()) {
    //hay files, avisar al cliente
    this->client.send_int(RETURN_CODE_OK);
    //enviar cantidad de archivos que se enviaran
    this->client.send_int(files.size());
    for (auto &f : files) {
      //por cada archivo enviar su nombre y el archivo
      std::string filename = this->index.get_filename_of_hash(f);
      this->client.send_string(filename);
      this->client.send_file(f);
    }
  } else {
    //si no hay files, devolver 0: tag no existe
    this->client.send_int(RETURN_CODE_FAIL);
  }
  this->finished = true;
  this->client.shut();
}
