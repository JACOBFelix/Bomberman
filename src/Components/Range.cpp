#include "Components/Range.hpp"

Component::Range::Range() : BaseComponent(Component::RANGE),
			    _range(1000) {
}

Component::Range::~Range() {}

Component::Range::Range(Range const& rhs) : BaseComponent(Component::RANGE) {
  _range = rhs._range;
}

Component::Range& Component::Range::operator=(Range const& rhs) {
  if (this != &rhs) {
    _range = rhs._range;
  }
  return *this;
}

unsigned int Component::Range::getRange(void) const {
  return _range;
}

void Component::Range::setRange(unsigned int const& range) {
  _range = range;
}

Export * Component::Range::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_range);
  return save;
}
