#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <iostream>
#include <vector>


class Socket {
private:
  int sock;

public:
  Socket();
  Socket(int sock);
  Socket(Socket &&other);
  ~Socket();

  int bind_and_listen(const char* port);
  int connect_to_server(const char* host, const char* port);
  Socket accept_connection();
  void shut();
  int send_buffer(size_t size, const unsigned char *buffer);
  int receive_buffer(size_t size, const unsigned char *buffer);
private:
  int get_hosts(struct addrinfo **result, const char* port, const char* host);
};

#endif
