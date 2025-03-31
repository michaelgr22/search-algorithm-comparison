#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../map/map.h"
#include "../search_algorithm/node.h"

class Gui {
private:
  std::vector<sf::Uint8> pixels;
  int scale_factor;
  Map *map;

  sf::Color map_fieldvalue_color(FieldValue field_value);
  void set_color_of_pixel(int x, int y, sf::Color color);
  std::vector<std::shared_ptr<Node>>
  order_nodes_start_to_goal(std::shared_ptr<Node> goal);

public:
  Gui(Map *map, int scale_factor) : map(map), scale_factor(scale_factor) {
    pixels.resize(map->width * map->height * 4);
  }

  void simulate_search_path(std::shared_ptr<Node> goal);
};
#endif
