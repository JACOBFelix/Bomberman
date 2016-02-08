#ifndef ANETWORK_HPP_
# define ANETWORK_HPP_

# include <string>
# include <netdb.h>
# include <cstring>
# include <unistd.h>
# include <sys/socket.h>
# include "Exceptions.hpp"

class ANetwork {
protected:
  int _socket;
  int _port;

public:
  ANetwork(std::string const& port);
  ~ANetwork();

  int getSocket(void) const;
};

#endif
