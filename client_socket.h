#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H value

#include "socket.h"
#include <string>

class ClientSocket : public Socket {
public:
  ClientSocket(const std::string hostname, const std::string port);
  ~ClientSocket();

  int recv_respcode();
  int recv_tagquantity();
  std::string recv_filename();
  std::string recv_file() {return "texto de prueba";}

  void send_file(std::string filename) { std::cout << "sending file: " << filename << '\n';}
  //void send(int i);
  //void send(std::string s);
//private:
  //int recv_int();
};

#endif
