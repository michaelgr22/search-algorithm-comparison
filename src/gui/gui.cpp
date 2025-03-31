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

void Gui::simulate_search_path(std::shared_ptr<Node> goal) {
  for (int y = 0; y < map->height; ++y) {
    for (int x = 0; x < map->width; ++x) {
      sf::Color color = map_fieldvalue_color(map->get_layout()[x][y]);
      set_color_of_pixel(x, y, color);
    }
  }

  sf::Texture texture;
  texture.create(map->width, map->height);
  texture.update(pixels.data());

  const int scaleFactor = 5; // Scale each pixel by 10x
  sf::Sprite sprite(texture);
  sprite.setScale(scaleFactor, scaleFactor); // Scale up by 10x
  sf::RenderWindow window(
      sf::VideoMode(map->width * scaleFactor, map->height * scaleFactor),
      "Map");

  // --- Timing Setup ---
  sf::Clock clock;                                   // Measures elapsed time
  sf::Time timeSinceLastUpdate = sf::Time::Zero;     // Accumulates time
  const sf::Time timePerUpdate = sf::seconds(0.15f); // How often to update

  // --- Pixel Update Tracking ---
  int currentPixelIndex = 0;
  std::shared_ptr<Node> current_node = goal;

  while (window.isOpen()) {
    timeSinceLastUpdate += clock.restart();

    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    if (timeSinceLastUpdate >= timePerUpdate && current_node != nullptr) {
      timeSinceLastUpdate -= timePerUpdate;

      sf::Color color = sf::Color::Blue;
      set_color_of_pixel(current_node->state.x, current_node->state.y, color);

      texture.update(pixels.data());

      current_node = current_node->parent;
    }

    window.clear();
    window.draw(sprite);
    window.display();
  }
}