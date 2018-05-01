#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H value

#include "socket.h"
#include <string>
#include <vector>

class ServerSocket : public Socket {
public:
  ServerSocket(std::string port);
  ServerSocket(ServerSocket&& other);
  ServerSocket(Socket&& other);
  ~ServerSocket();
  ServerSocket(const ServerSocket&) = delete;
  ServerSocket& operator=(const ServerSocket&) = delete;

  /*int recv_int();
  std::string recv_string();
  void send(int i);
  void send(std::string s);*/

  std::string recv_filename();
  std::string recv_tag();
  std::string recv_hash();
  int recv_tagquantity();
  int recv_respcode();



  Socket accept_client();
};

#endif
