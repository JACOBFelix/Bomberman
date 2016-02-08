#pragma once

#include "BaseComponent.hpp"
#include "Export.hpp"

namespace Component {
  class Solid : public BaseComponent {
  private:

  public:
    Solid();
    ~Solid();
    Solid(Solid const& rhs);
    Solid& operator=(Solid const& rhs);

    Export * serialize() const;
  };
}
