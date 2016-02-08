#ifndef ISAI_H_
# define ISAI_H_

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class IsAI : public BaseComponent {
  public:
    IsAI();
    virtual ~IsAI();

    Export * serialize() const;
  };
}

#endif /* !ISAI_H_ */
