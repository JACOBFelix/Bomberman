#ifndef MOVE_HPP_
# define MOVE_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Move : public BaseComponent {
  public:
    enum dir{NONE, NORTH, EAST, SOUTH, WEST}; // TODO LUCIE

  private:
    dir _dir;
    unsigned int _speed;

  public:
    Move();
    ~Move();
    Move(Move const& rhs);
    Move& operator=(Move const& rhs);

    dir const& getDir(void) const;
    void setDir(dir const& dir);
    unsigned int getSpeed(void) const;
    void setSpeed(unsigned int speed);

    Export * serialize() const;
  };
}

#endif
