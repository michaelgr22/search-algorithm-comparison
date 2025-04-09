#include "gui.h"

#include <memory>
#include <vector>

void Gui::simulate_search_path(
    std::vector<SearchAlgorithm *> algorithms_to_simulate) {

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

    window.clear(sf::Color(128, 128, 128));
    for (const auto &widget : pixel_widgets) {
      window.draw(widget->get_sprite());
    }
    window.display();
  }
}
