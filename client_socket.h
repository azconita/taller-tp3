#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H value

#include "common_socket.h"
#include <string>

/*Wrapper de Socket optimizado para un cliente
que quiere conectarse con un servidor*/
class ClientSocket : public Socket {
public:
  /*constructor: recibe el host y puerto al que debe conectarse
  devuelve un clientSocket ya conectado */
  ClientSocket(const char* hostname, const char* port);
  /*destructor: cierra el socket*/
  ~ClientSocket();

  /*Recibe int (wrapper de funciones de Socket para recibir int)*/
  int recv_respcode();
  int recv_tagquantity();
  /*Recibe string (wrapper de funciones de Socket para recibir string)*/
  std::string recv_filename();
};

#endif
