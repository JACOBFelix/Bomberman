#include "Components/Timer.hpp"

Component::Timer::Timer() : BaseComponent(Component::TIMER),
			    _ms(100) {
}

Component::Timer::~Timer() {}

Component::Timer::Timer(Timer const& rhs) : BaseComponent(Component::TIMER) {
  _ms = rhs._ms;
}

Component::Timer& Component::Timer::operator=(Timer const& rhs) {
  if (this != &rhs) {
    _ms = rhs._ms;
  }
  return *this;
}

unsigned long Component::Timer::getMs(void) const {
  return _ms;
}

void Component::Timer::setMs(unsigned long const& ms) {
  _ms = ms;
}

Export * Component::Timer::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_ms);
  return save;
}
