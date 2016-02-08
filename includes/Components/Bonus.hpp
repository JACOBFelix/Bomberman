#ifndef BONUS_HPP_
# define BONUS_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Bonus : public BaseComponent {
  public:
    enum type{SPEED, BOMB, RANGE};
  private:
    int _value;
    Component::Bonus::type _type;
  public:
    Bonus();
    ~Bonus();
    Bonus(Bonus const& rhs);
    Bonus& operator=(Bonus const& rhs);

    int getValue(void) const;
    void setValue(int const& value);
    Component::Bonus::type getType(void) const;
    void setType(Component::Bonus::type);

    Export * serialize() const;
  };
}

#endif
