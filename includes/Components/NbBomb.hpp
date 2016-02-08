#pragma once

#include "BaseComponent.hpp"
#include "Export.hpp"

namespace Component {
  class NbBomb : public BaseComponent {
  private:
    int _nb;

  public:
    NbBomb();
    ~NbBomb();
    NbBomb(NbBomb const& rhs);
    NbBomb& operator=(NbBomb const& rhs);

    int getNb(void) const;
    void setNb(int const& nb);

    Export * serialize() const;
  };
}
