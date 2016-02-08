#include "AMutex.hpp"
#include "Exceptions.hpp"

AMutex::AMutex() {
  if (pthread_mutex_init(&_mutex, NULL))
    throw MutexException("Unable to init mutex");
}

AMutex::~AMutex() {
  if (pthread_mutex_destroy(&_mutex))
    throw MutexException("Unable to destroy mutex");
}

pthread_mutex_t const& AMutex::getMutex(void) const {
  return _mutex;
}
