#include "gui.h"

#include <memory>
#include <vector>

void Gui::display_widgets() {
  window.clear(sf::Color(128, 128, 128));
  for (const auto &widget : pixel_widgets) {
    window.draw(widget->get_drawable());
  }
  for (const auto &widget : text_widgets) {
    window.draw(widget->get_drawable());
  }
  window.display();
}

Gui::Gui(Map *map, std::vector<SearchAlgorithm *> algorithms_to_simulate)
    : map(map), algorithms_to_simulate(algorithms_to_simulate) {

  // define widgets
  const float map_scale = 2.4;
  const int pixel_maps_padding = 20;

  pixel_maps.resize(number_of_widgets);
  pixel_widgets.resize(number_of_widgets);
  text_widgets.resize(number_of_widgets);

  const std::vector<float> pixel_map_widgets_x_positions = {
      pixel_maps_padding, map->width * map_scale + pixel_maps_padding * 2,
      map->width * map_scale * 2 + pixel_maps_padding * 3};
  const float y_position_widgets = 20.0;

  for (int i = 0; i < number_of_widgets; i++) {
    pixel_maps[i] = std::make_unique<PixelMap>(map);

    pixel_widgets[i] = std::make_unique<PixelMapWidget>(
        pixel_maps[i]->get_pixel_array(), map_scale, map_scale,
        pixel_map_widgets_x_positions[i], y_position_widgets, map->width,
        map->height);

    text_widgets[i] = std::make_unique<TextWidget>(
        algorithms_to_simulate[i]->get_name(),
        pixel_map_widgets_x_positions[i] + (map->width / 2.0) +
            pixel_maps_padding * (i + 1),
        map->height * map_scale + y_position_widgets * 2);
    //
  }

  window.create(sf::VideoMode(width_res, height_res),
                "Search Algorithms Simulation");

  if (window.isOpen()) {
    display_widgets();
  }
}

void Gui::simulate_search_path() {

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
          pixel_maps[i]->set_color_of_pixel(current_node->get_state().x,
                                            current_node->get_state().y,
                                            sf::Color::Red);
          current_node = current_node->get_parent();
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
          pixel_maps[i]->set_color_of_pixel(node->get_state().x,
                                            node->get_state().y, color);

          pixel_widgets[i]->update(pixel_maps[i]->get_pixel_array());
        } else {
          search_did_not_update_counter[i]++;
        }
      }
    }

    display_widgets();
  }
}
