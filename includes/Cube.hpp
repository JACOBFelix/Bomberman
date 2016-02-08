#ifndef CUBE_HPP_
# define CUBE_HPP_

# include "SdlContext.hh"
# include "Game.hh"
# include "Geometry.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

class Cube
{
public:
  Cube(unsigned int x, unsigned int y);
  ~Cube();
  gdl::Geometry _geometry;

private:
  Cube(const Cube &) {};
  Cube &operator=(const Cube &) { return *this; };

  unsigned int _x;
  unsigned int _y;
};

#endif
