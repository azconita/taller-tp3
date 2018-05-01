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
