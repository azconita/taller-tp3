#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H value

#include "common_socket.h"
#include <string>

class ClientSocket : public Socket {
public:
  ClientSocket(const std::string hostname, const std::string port);
  ~ClientSocket();

  int recv_respcode();
  int recv_tagquantity();
  std::string recv_filename();
};

#endif
