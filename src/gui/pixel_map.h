#ifndef PIXEL_MAP_H
#define PIXEL_MAP_H

#include "../map/map.h"
#include <SFML/Graphics.hpp>

class PixelMap {
private:
  Map *map;
  std::vector<sf::Uint8> pixel_array;

public:
  const int width;
  const int height;

  sf::Color map_fieldvalue_color(FieldValue field_value) {
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

  void set_color_of_pixel(int x, int y, sf::Color color) {
    int flippedY = height - 1 - y;               // Flip row index
    int pixelIndex = (flippedY * width + x) * 4; // Offset in 1D array

    pixel_array[pixelIndex] = color.r;
    pixel_array[pixelIndex + 1] = color.g;
    pixel_array[pixelIndex + 2] = color.b;
    pixel_array[pixelIndex + 3] = color.a;
  }

  PixelMap(Map *map) : width(map->width), height(map->height) {
    pixel_array.resize(width * height * 4);
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        sf::Color color = map_fieldvalue_color(map->get_layout()[x][y]);
        set_color_of_pixel(x, y, color);
      }
    }
  }

  std::vector<sf::Uint8> get_pixel_array() const { return pixel_array; }
};

#endif