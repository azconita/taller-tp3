#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H value

#include "socket.h"
#include <string>
#include <vector>

class ServerSocket : private Socket {
public:
  ServerSocket(std::string port);
  ServerSocket(ServerSocket&& other);
  ServerSocket(Socket&& other);
  ~ServerSocket();

  int recv_int();
  std::string recv_string();
  void send(int i);
  void send(std::string s);

  std::string recv_filename();
  std::string recv_tag();
  std::string recv_hash();
  int recv_tagquantity();
  int recv_respcode();

  std::string recv_file() {return "texto de prueba";}
  std::vector<std::string> recv_hashes() {
    std::vector<std::string> v;
    v.push_back("a14242");
    return v;
  };
  void send_file(std::string filename) { std::cout << "sending file: " << filename << '\n';}

  ServerSocket accept_client();
};

#endif
