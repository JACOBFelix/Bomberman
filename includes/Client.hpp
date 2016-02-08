#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <vector>
# include <sys/poll.h>
# include "ANetwork.hpp"

class Client : public ANetwork {
private:
  std::vector<struct pollfd> _pollfds;
  std::string const& _ip;

public:
  Client(std::string const& port, std::string const& ip);
};

#endif
