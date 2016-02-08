#ifndef TIMER_HPP_
# define TIMER_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Timer : public BaseComponent {
  private:
    unsigned long _ms;

  public:
    Timer();
    ~Timer();
    Timer(Timer const& rhs);
    Timer& operator=(Timer const& rhs);

    unsigned long getMs(void) const;
    void setMs(unsigned long const& ms);

    Export * serialize() const;
  };
}

#endif
