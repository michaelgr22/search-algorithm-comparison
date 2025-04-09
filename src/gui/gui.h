#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../map/map.h"
#include "../search_algorithm/node.h"
#include "../search_algorithm/search_algorithm.h"
#include "pixel_map.h"
#include "pixel_map_widget.h"
#include "text_widget.h"

class Gui {
private:
  const int number_of_widgets = 3;
  const int width_res = 1920;
  const int height_res = 1080;

  Map *map;
  std::vector<SearchAlgorithm *> algorithms_to_simulate;

  sf::RenderWindow window;
  std::vector<std::unique_ptr<PixelMap>> pixel_maps;
  std::vector<std::unique_ptr<PixelMapWidget>> pixel_widgets;
  std::vector<std::unique_ptr<TextWidget>> text_widgets;

  void display_widgets();

public:
  Gui(Map *map, std::vector<SearchAlgorithm *> algorithms_to_simulate);

  void simulate_search_path();
};
#endif
