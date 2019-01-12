#ifndef PENTANE_HPP
#define PENTANE_HPP

#include "main.h"
#include <functional>

namespace hc {
  namespace pentane {
    void drawFeild();
    void drawTiles(std::function <void(int)> onChange);
  }
}

#endif
