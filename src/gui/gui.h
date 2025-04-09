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

class Gui {
private:
  const int number_of_widgets = 3;
  const int width_res = 1920;
  const int height_res = 1080;

  Map *map;

  sf::RenderWindow window;
  std::vector<std::unique_ptr<PixelMap>> pixel_maps;
  std::vector<std::unique_ptr<PixelMapWidget>> pixel_widgets;

public:
  Gui(Map *map) : map(map) {
    const float map_scale = 2.4;
    const int padding = 20;

    pixel_maps.resize(number_of_widgets);
    pixel_widgets.resize(number_of_widgets);
    const std::vector<float> widget_x_positions = {
        padding, map->width * map_scale + padding * 2,
        map->width * map_scale * 2 + padding * 3};
    const float y_position_widgets = 20.0;

    for (int i = 0; i < number_of_widgets; i++) {
      pixel_maps[i] = std::make_unique<PixelMap>(map);
      pixel_widgets[i] = std::make_unique<PixelMapWidget>(
          pixel_maps[i]->get_pixel_array(), map_scale, map_scale,
          widget_x_positions[i], y_position_widgets, map->width, map->height);
    }

    window.create(sf::VideoMode(width_res, height_res),
                  "Search Algorithms Simulation");

    if (window.isOpen()) {
      window.clear(sf::Color(128, 128, 128));
      for (const auto &widget : pixel_widgets) {
        window.draw(widget->get_sprite());
      }
      window.display();
    }
  }

  void
  simulate_search_path(std::vector<SearchAlgorithm *> algorithms_to_simulate);
};
#endif
