#pragma once

#include "BaseComponent.hpp"
#include "Export.hpp"

namespace Component {
  class Id : public BaseComponent {
  private:
    int _id;

  public:
    Id();
    ~Id();
    Id(Id const& rhs);
    Id& operator=(Id const& rhs);

    int getId(void) const;
    void setId(int const& id);

    Export * serialize() const;
  };
}
