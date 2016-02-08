#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <vector>
# include <sys/poll.h>
# include "ANetwork.hpp"

class Server : public ANetwork {
private:
  std::vector<struct pollfd> _pollfds;

public:
  Server(std::string const& port);
};

#endif
