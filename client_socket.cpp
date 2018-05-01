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

/*int ClientSocket::recv_int() {
  int r;
  if (this->receive_buffer(sizeof(int), (unsigned char *) &r) < sizeof(int))
    return -1;//TODO:excepciones
  return ntohl(r);
}*/

int ClientSocket::recv_respcode() {
  return this->recv_int();
}

int ClientSocket::recv_tagquantity() {
  return this->recv_int();
}

std::string ClientSocket::recv_filename() {
  int size = this->recv_int();
  //std::string s;
  char r[size];
  this->receive_buffer(size, reinterpret_cast<unsigned char*>(r));
  return std::string(r);
}

/*void ClientSocket::send(int i) {
  int s = htonl(i);
  this->send_buffer(sizeof(int), (unsigned char *) &s);
}

void ClientSocket::send(std::string s) {
  this->send_buffer(s.size(), (unsigned char *) s.c_str());
}*/
