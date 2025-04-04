#include "gui.h"

sf::Color Gui::map_fieldvalue_color(FieldValue field_value) {
  switch (field_value) {
  case 1:
    return sf::Color::White;
  case 2:
    return sf::Color::Green;
  case 3:
    return sf::Color::Black;
  case 4:
    return sf::Color::Blue;
  case 5:
    return sf::Color::Red;
  default:
    return sf::Color::Yellow;
  }
}

void Gui::set_color_of_pixel(int x, int y, sf::Color color) {
  int flippedY = map->height - 1 - y;               // Flip row index
  int pixelIndex = (flippedY * map->width + x) * 4; // Offset in 1D array

  pixels[pixelIndex] = color.r;
  pixels[pixelIndex + 1] = color.g;
  pixels[pixelIndex + 2] = color.b;
  pixels[pixelIndex + 3] = color.a;
}

void Gui::simulate_search_path() {
  for (int y = 0; y < map->height; ++y) {
    for (int x = 0; x < map->width; ++x) {
      sf::Color color = map_fieldvalue_color(map->get_layout()[x][y]);
      set_color_of_pixel(x, y, color);
    }
  }

  sf::Texture texture;
  texture.create(map->width, map->height);
  texture.update(pixels.data());

  sf::Sprite sprite(texture);
  sprite.setScale(scale_factor, scale_factor); // Scale up by 10x
  sf::RenderWindow window(
      sf::VideoMode(map->width * scale_factor, map->height * scale_factor),
      "Map");

  // --- Timing Setup ---
  sf::Clock clock;                                    // Measures elapsed time
  sf::Time timeSinceLastUpdate = sf::Time::Zero;      // Accumulates time
  const sf::Time timePerUpdate = sf::seconds(0.025f); // How often to update

  // needed that we know when we can show the final path
  int search_did_not_update_counter = 0;

  while (window.isOpen()) {
    timeSinceLastUpdate += clock.restart();

    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    // show final path
    std::shared_ptr<Node> goal_node = search_algorithm->goal_node();
    if (goal_node && search_did_not_update_counter > 10) {
      std::shared_ptr<Node> current_node = goal_node;
      while (current_node) {
        set_color_of_pixel(current_node->state.x, current_node->state.y,
                           sf::Color::Red);
        current_node = current_node->parent;
      }
      texture.update(pixels.data());
    }

    // show search exploration
    if (timeSinceLastUpdate >= timePerUpdate) {
      timeSinceLastUpdate -= timePerUpdate;

      std::shared_ptr<Node> node = search_algorithm->pop_node();
      sf::Color color = sf::Color::Blue;

      if (node) {
        set_color_of_pixel(node->state.x, node->state.y, color);

        texture.update(pixels.data());
      } else {
        search_did_not_update_counter++;
      }
    }
    window.clear();
    window.draw(sprite);
    window.display();
  }
}
