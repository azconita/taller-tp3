#include "client_socket.h"
#include <string>
#include <arpa/inet.h>


ClientSocket::ClientSocket(const std::string hostname, const std::string port) :
                        Socket() {
  if (this->connect_to_server(hostname.c_str(), port.c_str()) == 0)
  std::cout << "[debug] [ClientSocket] connected to server\n";
}

ClientSocket::~ClientSocket() {
  this->shut();
}

int ClientSocket::recv_respcode() {
  return this->recv_int();
}

int ClientSocket::recv_tagquantity() {
  return this->recv_int();
}

std::string ClientSocket::recv_filename() {
  return this->recv_string();
}
