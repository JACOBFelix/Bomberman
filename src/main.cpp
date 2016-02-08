#include <iostream>
#include "Exceptions.hpp"
#include "Display.hpp"

int	main(void) {
  try {
    Display d(1440, 900);
    d.initialize();
    while (true) {
      d.loop();
    }
  } catch(BomberException const& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
