#ifndef MUTEX_HPP_
# define MUTEX_HPP_

# include "AMutex.hpp"

class Mutex: public AMutex {
public:
  Mutex();
  ~Mutex();

  void lock();
  bool trylock();
  void unlock();
};

#endif
