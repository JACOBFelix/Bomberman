#include "Components/NbBomb.hpp"

Component::NbBomb::NbBomb() : BaseComponent(Component::NBBOMB),
			      _nb(1) {
}

Component::NbBomb::~NbBomb() {}

Component::NbBomb::NbBomb(NbBomb const& rhs) : BaseComponent(Component::NBBOMB){
  _nb = rhs._nb;
}

Component::NbBomb& Component::NbBomb::operator=(NbBomb const& rhs) {
  if (this != &rhs) {
    _nb = rhs._nb;
  }
  return *this;
}
int Component::NbBomb::getNb(void) const {
  return _nb;
}

void Component::NbBomb::setNb(int const& nb) {
  _nb = nb;
}

Export * Component::NbBomb::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_nb);
  return save;
}
