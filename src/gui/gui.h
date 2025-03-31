#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

#include "../map/map.h"
#include "../search_algorithm/node.h"

class Gui {
private:
  std::vector<sf::Uint8> pixels;
  int scaleFactor = 5;
  Map *map;

  sf::Color map_fieldvalue_color(FieldValue field_value);
  void set_color_of_pixel(int x, int y, sf::Color color);

public:
  Gui(Map *map) : map(map) { pixels.resize(map->width * map->height * 4); }

  void simulate_search_path(std::shared_ptr<Node> goal);
};
#endif
