#include "Server.hpp"

Server::Server(std::string const& port) : ANetwork(port) {
  int err;
  struct addrinfo hints;
  struct addrinfo *ai;

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if ((err = getaddrinfo(NULL, port.data(), &hints, &ai)))
    throw ServerException(std::string("getaddrinfo : ") + gai_strerror(err));
  if ((_socket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1)
    throw ServerException(std::string("socket : ") + strerror(errno));
  if (bind(_socket, ai->ai_addr, ai->ai_addrlen) == -1) {
    close(_socket);
    throw ServerException(std::string("bind : ") + strerror(errno));
  }
  if (listen(_socket, 65536) == -1) {
    close(_socket);
    throw ServerException(std::string("listen : ") + strerror(errno));
  }
  freeaddrinfo(ai);
}
