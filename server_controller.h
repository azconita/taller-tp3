#include <string>
#include <vector>
#include <thread>
#include "server_index.h"
#include "common_socket.h"
#include "server_socket.h"
#include "server_request_processor.h"
#include "server_push_processor.h"
#include "server_pull_processor.h"
#include "server_tag_processor.h"

#define PUSH_REQUEST 1
#define TAG_REQUEST 2
#define PULL_REQUEST 3

/* Controlador principal del servidor:
  Hilo principal de ejecucion: se encarga de aceptar clientes y
  lanzar los hilos de cada proceso segun el request del cliente.*/
class VersionController {
private:
  std::thread thread;
  ServerSocket acc_socket;
  Index index;
  std::vector<PushProcessor*> pushs;
  std::vector<TagProcessor*> tags;
  std::vector<PullProcessor*> pulls;
  bool keep = true;

public:
  /*constructor: crea socket para aceptar clientes (el cual realiza
    bind_and_listen en su construccion) y el index con los files/tags.*/
  VersionController(const std::string port, const char* filename);
  /*destructor: cierra el socket y realiza el join de threads*/
  ~VersionController();
  /*start: inicia thread que ejecuta run()*/
  void start();
  /*thread del servidor que espera clientes y lanza RequestProcessor*/
  void run();
private:
  void try_join_threads();
  void stop();
};
