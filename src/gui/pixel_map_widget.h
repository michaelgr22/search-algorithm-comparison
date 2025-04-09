#ifndef PIXEL_MAP_WIDGET_H
#define PIXEL_MAP_WIDGET_H

#include "pixel_map.h"
#include <SFML/Graphics.hpp>

class PixelMapWidget {
private:
  sf::Texture texture;
  sf::Sprite sprite;

public:
  const float scale_x;
  const float scale_y;
  const float position_x;
  const float position_y;
  const int width;
  const int height;

  PixelMapWidget(const std::vector<sf::Uint8> &data, float scale_x,
                 float scale_y, float position_x, float position_y, int width,
                 int height)
      : scale_x(scale_x), scale_y(scale_y), position_x(position_x),
        position_y(position_y), width(width), height(height) {
    texture.create(width, height);
    texture.update(data.data());
    sprite = sf::Sprite(texture);
    sprite.setScale(scale_x, scale_y);
    sprite.setPosition(position_x, position_y);
  }

  void update(const std::vector<sf::Uint8> &data) {
    texture.update(data.data());
  }

  sf::Sprite get_drawable() const { return sprite; }
};

#endif