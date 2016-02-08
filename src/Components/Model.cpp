#include "Components/Model.hpp"
#include "Exceptions.hpp"

/* Echelle : */
/*
** Koala -> 0.002
** Bonus (crystal) -> 0.0002
** Autre -> 0.003
** Murs -> 0.005
** Ground -> 0.02, à aligner sur le point central de la caméra (c'est juste un grand bout de carton plat)
** Menu -> 1
*/

Component::Model::Model(gdl::Model &model, float scale) :
  BaseComponent(Component::MODEL), _model(model) {
  _scale = scale;
}

Component::Model::~Model() {
}

gdl::Model &	Component::Model::getModel() const {
  return _model;
}


float		Component::Model::getScale() const {
  return _scale;
}

Export * Component::Model::serialize() const {
  Export * save = new Export;
  save->addData(getType());
  save->addData(1);
  save->addData(_scale); // the real data is not saved, it is predictive. restore it during the save
  return save;
}

