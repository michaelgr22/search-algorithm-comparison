#include "gui.h"

#include "pixel_map.h"
#include "pixel_map_widget.h"
#include <memory>
#include <vector>

void Gui::simulate_search_path(
    std::vector<SearchAlgorithm *> algorithms_to_simulate) {

  const float map_scale = 2.4;
  const int padding = 20;

  std::vector<std::unique_ptr<PixelMap>> pixel_maps(3);
  std::vector<std::unique_ptr<PixelMapWidget>> pixel_widgets(3);
  const std::vector<float> widget_x_positions = {
      padding, map->width * map_scale + padding * 2,
      map->width * map_scale * 2 + padding * 3};
  const float y_position_widgets = 20.0;

  for (int i = 0; i < algorithms_to_simulate.size(); i++) {
    pixel_maps[i] = std::make_unique<PixelMap>(map);
    pixel_widgets[i] = std::make_unique<PixelMapWidget>(
        pixel_maps[i]->get_pixel_array(), map_scale, map_scale,
        widget_x_positions[i], y_position_widgets, map->width, map->height);
  }

  sf::RenderWindow window(sf::VideoMode(width_res, height_res), "Map");

  // --- Timing Setup ---
  sf::Clock clock;                                    // Measures elapsed time
  sf::Time timeSinceLastUpdate = sf::Time::Zero;      // Accumulates time
  const sf::Time timePerUpdate = sf::seconds(0.025f); // How often to update

  // needed that we know when we can show the final path
  std::vector<int> search_did_not_update_counter = {0, 0, 0};

  while (window.isOpen()) {
    timeSinceLastUpdate += clock.restart();

    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    // show final path
    for (int i = 0; i < algorithms_to_simulate.size(); i++) {
      std::shared_ptr<Node> goal_node = algorithms_to_simulate[i]->goal_node();
      if (goal_node && search_did_not_update_counter[i] > 10) {
        std::shared_ptr<Node> current_node = goal_node;
        while (current_node) {
          pixel_maps[i]->set_color_of_pixel(
              current_node->state.x, current_node->state.y, sf::Color::Red);
          current_node = current_node->parent;
        }
        pixel_widgets[i]->update(pixel_maps[i]->get_pixel_array());
      }
    }

    // show search exploration
    if (timeSinceLastUpdate >= timePerUpdate) {
      timeSinceLastUpdate -= timePerUpdate;

      for (int i = 0; i < algorithms_to_simulate.size(); i++) {
        std::shared_ptr<Node> node = algorithms_to_simulate[i]->pop_node();
        sf::Color color = sf::Color::Blue;

        if (node) {
          pixel_maps[i]->set_color_of_pixel(node->state.x, node->state.y,
                                            color);

          pixel_widgets[i]->update(pixel_maps[i]->get_pixel_array());
        } else {
          search_did_not_update_counter[i]++;
        }
      }
    }

    window.clear(sf::Color(128, 128, 128));
    for (const auto &widget : pixel_widgets) {
      window.draw(widget->get_sprite());
    }
    window.display();
  }
}
