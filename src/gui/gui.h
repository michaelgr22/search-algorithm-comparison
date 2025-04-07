#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../map/map.h"
#include "../search_algorithm/node.h"
#include "../search_algorithm/search_algorithm.h"

class Gui {
private:
  const int width_res = 1920;
  const int height_res = 1080;

  Map *map;
  SearchAlgorithm *search_algorithm;
  int scale_factor;

  // std::vector<sf::Uint8> pixels;

  sf::Color map_fieldvalue_color(FieldValue field_value);
  void set_color_of_pixel(std::vector<sf::Uint8> &pixel_map, int x, int y,
                          sf::Color color);
  std::vector<sf::Uint8> create_map_pixel_array();

public:
  Gui(Map *map, SearchAlgorithm *search_algorithm, int scale_factor)
      : map(map), search_algorithm(search_algorithm),
        scale_factor(scale_factor) {
    // pixels.resize(map->width * map->height * 4);
  }

  void simulate_search_path();
};
#endif
