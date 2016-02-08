#ifndef RANGE_HPP_
# define RANGE_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Range : public BaseComponent {
  private:
    unsigned int _range;

  public:
    Range();
    ~Range();
    Range(Range const& rhs);
    Range& operator=(Range const& rhs);

    unsigned int getRange(void) const;
    void setRange(unsigned int const& range);

    Export * serialize() const;
  };
}

#endif
