#ifndef POSITION_HPP_
# define POSITION_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Position : public BaseComponent {
  private:
    unsigned int _x;
    unsigned int _y;

  public:
    Position();
    ~Position();
    Position(Position const& rhs);
    Position& operator=(Position const& rhs);

    unsigned int getX(void) const;
    void setX(unsigned int const& x);
    unsigned int getY(void) const;
    void setY(unsigned int const& y);

    Export * serialize() const;
  };
}

#endif
