#include <vector>
#include <string>
#include "common_socket.h"
#include "client_socket.h"

/*Controlador principal del cliente:
  contiene las funciones principales que debe ejecutar el cliente*/
class VersionClient {
private:
  ClientSocket client;

public:
  /*Al construirse se crea el socket (que en su constructor
  se conecta al server)*/
  VersionClient(const char *hostname, const char* port);
  ~VersionClient() {}
  /*Funciones principales*/
  /*push_file: Recibe un filename valido (existente)*/
  void push_file(std::string &filename, std::string &hash);
  /*tag_hashes
    Si el tag ya existe en el servidor o no existe alguno de los hashes,
    imprime por pantalla el error.*/
  void tag_hashes(std::string &tag, std::vector<std::string> &hashes);
  /*pull_tag
    Si el tag no existe en el servidor, imprime por pantalla el error.*/
  void pull_tag(std::string &tag);
};
