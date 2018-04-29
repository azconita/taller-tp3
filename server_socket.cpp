#include "server_socket.h"
#include <string>
#include <arpa/inet.h>

ServerSocket::ServerSocket(const std::string port) : Socket() {
  this->bind_and_listen(port.c_str());
}

ServerSocket::ServerSocket(ServerSocket&& other) :
        Socket(std::move(other)) {
}

ServerSocket::ServerSocket(Socket&& other) :
        Socket(std::move(other)) {
}

ServerSocket::~ServerSocket() {
  this->shut();
}

ServerSocket ServerSocket::accept_client() {
  return std::move(ServerSocket(this->accept_connection()));
}

int ServerSocket::recv_int() {
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
  this->send_buffer(sizeof(int), (unsigned char *) &i);
}

void ServerSocket::send(std::string s) {
  this->send_buffer(s.size(), (unsigned char *) s.c_str());
}

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
