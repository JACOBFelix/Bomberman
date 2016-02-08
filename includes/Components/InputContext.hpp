#pragma once

#include "BaseComponent.hpp"
#include "Export.hpp"

namespace Component {
  class InputContext : public BaseComponent {
  private:
    int _up;
    int _down;
    int _left;
    int _right;
    int _drop;

  public:
    InputContext();
    ~InputContext();
    InputContext(InputContext const& rhs);
    InputContext& operator=(InputContext const& rhs);

    int getUp(void) const;
    void setUp(int const& up);
    int getDown(void) const;
    void setDown(int const& down);
    int getLeft(void) const;
    void setLeft(int const& left);
    int getRight(void) const;
    void setRight(int const& right);
    int getDrop(void) const;
    void setDrop(int const& drop);

    Export * serialize() const;
  };
}
