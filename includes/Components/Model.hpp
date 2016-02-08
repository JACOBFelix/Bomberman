#ifndef MODEL_HPP_
# define MODEL_HPP_

# include "Model.hh"

# include "BaseComponent.hpp"
# include "Export.hpp"

namespace Component {
  class Model : public BaseComponent {
  public:
    Model(gdl::Model &, float);
    ~Model();

    gdl::Model & getModel() const;
    float getScale() const;

    Export * serialize() const;

  private:
    float _scale;
    gdl::Model & _model;
  };
};

#endif
