#include "client_socket.h"
#include "socket.h"
#include "server_socket.h"
#include <arpa/inet.h>
#include <string>

int cli(int i) {
  int s = htonl(i);
  ClientSocket sock(std::string("127.0.0.1"), std::string("9999"));
  sock.send_int(i);
  return i;
  //sock.receive_buffer(sizeof(int), (unsigned char *) &s);
  //return ntohl(s);
}

int srv2(int p) {
  int c = 0;

  Socket sock;
  sock.bind_and_listen("9999");
  Socket nsock = sock.accept_connection();

  nsock.receive_buffer(4, (unsigned char*) &c);
  std::cout << "srv: " << ntohl(c) << '\n';

  return 0;
}

int srv(int i) {
  int p = 0;

  ServerSocket s(std::string("9999"));
  Socket nsock = s.accept_client();

  nsock.receive_buffer(4, (unsigned char *) &p);

  std::cout << "srv: " << ntohl(p) << '\n';

  //return 0;
  //p = *((int*) &r);
  return ntohl(p);
}

int main(int argc, char const *argv[]) {
  int c = 123;
  int r = cli(c);
  //std::cout << htonl(1) << '\n';
  //int r = srv(c);
  //std::cout << r << '\n';
  return 0;
}
