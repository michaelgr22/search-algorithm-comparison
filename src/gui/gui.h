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

public:
  Gui(Map *map) : map(map) {}

  void
  simulate_search_path(std::vector<SearchAlgorithm *> algorithms_to_simulate);
};
#endif
