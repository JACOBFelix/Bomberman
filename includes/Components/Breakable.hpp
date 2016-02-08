#pragma once

#include "BaseComponent.hpp"
#include "Export.hpp"

namespace Component {
  class Breakable : public BaseComponent {
  private:

  public:
    Breakable();
    ~Breakable();
    Breakable(Breakable const& rhs);
    Breakable& operator=(Breakable const& rhs);

    Export * serialize() const;
  };
}
