#ifndef PLAYERINFO_HPP_
# define PLAYERINFO_HPP_

# include <string>
# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class PlayerInfo : public BaseComponent {
  private:
    std::string _name;
    unsigned int _id;
    int _score;

  public:
    PlayerInfo();
    ~PlayerInfo();
    PlayerInfo(PlayerInfo const& rhs);
    PlayerInfo& operator=(PlayerInfo const& rhs);

    std::string const& getName(void) const;
    void setName(std::string const& name);

    unsigned int getId(void) const;
    void setId(unsigned int const& id);

    int getScore(void) const;
    void setScore(int const& id);

    Export * serialize() const;
  };
}

#endif
