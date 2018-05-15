#include "server_controller.h"
#include <string>
#include <thread>

int main(int argc, char const *argv[]) {
  //Inicializa servidor con puerto y archivo con index de files/tags->hashes
  VersionController server(argv[1], argv[2]);
  //ejecuta servidor en nuevo thread
  server.start();
  //este thread espera que usuario ingrese "q" para terminar ejecución
  while (getchar() != 'q') {
    continue;
  }
  //server.stop();
  return 0;
}
