#ifndef FD_HPP_
# define FD_HPP_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Fd : public BaseComponent {
  private:
    int _fd;

  public:
    Fd();
    ~Fd();
    Fd(Fd const& rhs);
    Fd& operator=(Fd const& rhs);

    int getFd(void) const;
    void setFd(int const& fd);

    Export * serialize() const;
  };
}

#endif
