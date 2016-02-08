#ifndef AMUTEX_HPP_
# define AMUTEX_HPP_

# include <pthread.h>

class AMutex {
protected:
  pthread_mutex_t _mutex;

public:
  AMutex();
  pthread_mutex_t const& getMutex(void) const;

  virtual ~AMutex();
  virtual void lock() = 0;
  virtual bool trylock() = 0;
  virtual void unlock() = 0;
};

#endif
