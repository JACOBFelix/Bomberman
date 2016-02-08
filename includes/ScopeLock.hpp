#ifndef SCOPELOCK_HPP_
# define SCOPELOCK_HPP_

# include "AMutex.hpp"

class ScopeLock {
private:
  AMutex& _mutex;

public:
  ScopeLock(AMutex& mutex);
  ~ScopeLock();
};

#endif
