#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include <SFML/Graphics.hpp>

class TextWidget {
private:
  sf::Text text;
  sf::Font font;

public:
  const float position_x;
  const float position_y;

  TextWidget(const std::string &str, const float position_x,
             const float position_y)
      : position_x(position_x), position_y(position_y) {

    font.loadFromFile("assets/fonts/ARIAL.TTF");
    text.setCharacterSize(30);
    text.setString(str);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position_x, position_y);
    text.setFont(font);
  }

  sf::Text get_drawable() const { return text; }
};

#endif