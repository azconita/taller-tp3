#include "server_socket.h"
#include <string>
#include <arpa/inet.h>

ServerSocket::ServerSocket(const std::string port) : Socket() {
  if (this->bind_and_listen(port.c_str()) == 0)
    std::cout << "[debug] [ServerSocket] listening \n";
}

ServerSocket::ServerSocket(ServerSocket&& other) :
        Socket(std::move(other)) {
}

ServerSocket::ServerSocket(Socket&& other) :
        Socket(std::move(other)) {
}

ServerSocket::~ServerSocket() {
  std::cout << "[debug] [ServerSocket] closing serversocket: " << this->sock << '\n';
  //this->shut();
}

Socket ServerSocket::accept_client() {
  std::cout << "[debug] [ServerSocket] accepting client" << '\n';
  Socket s = this->accept_connection();
  //if ( s.sock != -1)
  //  std::cout << "new client " << '\n';
  //return std::move(s);
  std::cout << "[debug] [ServerSocket] new client" << '\n';
  return  s;
}

/*int ServerSocket::recv_int() {
  int r;
  if (this->receive_buffer(sizeof(int), (unsigned char *) &r) < sizeof(int))
    return -1;//TODO:excepciones
  return ntohl(r);
}

std::string ServerSocket::recv_string() {
  int size = this->recv_int();
  //std::string s;
  char r[size];
  this->receive_buffer(size, reinterpret_cast<unsigned char*>(r));
  return std::string(r);
}

void ServerSocket::send(int i) {
  int s = htonl(i);
  this->send_buffer(sizeof(int), (unsigned char *) &s);
}

void ServerSocket::send(std::string s) {
  this->send_buffer(s.size(), (unsigned char *) s.c_str());
}*/

std::string ServerSocket::recv_filename() {
  this->recv_string();
}

std::string ServerSocket::recv_tag() {
  this->recv_string();
}

std::string ServerSocket::recv_hash() {
  this->recv_string();
}

int ServerSocket::recv_tagquantity() {
  this->recv_int();
}

int ServerSocket::recv_respcode() {
  this->recv_int();
}
