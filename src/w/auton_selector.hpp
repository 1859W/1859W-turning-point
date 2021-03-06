#ifndef AUTON_SELECTOR_HPP
#define AUTON_SELECTOR_HPP

#include "main.h"
#include "../auton/def.hpp"
#include <functional>

namespace w {
  namespace auton_selector {
    extern std::string selectedAuton;
    extern int selectedTile;
    extern lv_obj_t* list;

    // feild
    extern lv_obj_t* feildContainer;

    // tiles
    extern lv_obj_t *redA;
    extern lv_obj_t *redB;
    extern lv_obj_t *blueA;
    extern lv_obj_t *blueB;

    // style
    extern lv_style_t redTile;
    extern lv_style_t redTileActive;
    extern lv_style_t blueTile;
    extern lv_style_t blueTileActive;

    extern lv_style_t activeTile;

    // functions
    void init();
    void setActiveTile(lv_obj_t *active);
    void drawFeild();
    void drawTiles(std::function <void(int)> onChange);
  }
}

#endif
