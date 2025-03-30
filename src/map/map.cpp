#include "map.h"

// ======================[ Private Methods ]===================== //

sf::Color Map::map_fieldvalue_color(FieldValue field_value) {
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

// ======================[ Public Methods ]===================== //
void Map::draw() {
  std::vector<sf::Uint8> pixels(width * height * 4); // RGBA format

  // Fill pixel buffer, flipping vertically to match SFML's expected format
  for (int y = 0; y < height; ++y) {
    int flippedY = height - 1 - y; // Flip row index
    for (int x = 0; x < width; ++x) {
      sf::Color color = map_fieldvalue_color(layout[x][y]);
      int pixelIndex = (flippedY * width + x) * 4; // Offset in 1D array

      pixels[pixelIndex] = color.r;
      pixels[pixelIndex + 1] = color.g;
      pixels[pixelIndex + 2] = color.b;
      pixels[pixelIndex + 3] = color.a;
    }
  }

  sf::Texture texture;
  texture.create(width, height);
  texture.update(pixels.data());

  const int scaleFactor = 5; // Scale each pixel by 10x
  sf::Sprite sprite(texture);
  sprite.setScale(scaleFactor, scaleFactor); // Scale up by 10x
  sf::RenderWindow window(
      sf::VideoMode(width * scaleFactor, height * scaleFactor), "Map");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    window.clear();
    window.draw(sprite);
    window.display();
  }
}

void Map::set_scenario(Coordinate s, Coordinate g) {
  start.x = s.x;
  start.y = s.y;
  goal.x = g.x;
  goal.y = g.y;

  layout[start.x][start.y] = START;
  layout[goal.x][goal.y] = GOAL;
}

std::vector<Coordinate> Map::expand_node(Coordinate node) {
  std::vector<Coordinate> directions = {Coordinate(1, 0), Coordinate(0, 1),
                                        Coordinate(-1, 0), Coordinate(0, -1)};

  for (Coordinate &c : directions) {
    c = c + node;
  }

  // check if coordinate is valid
  directions.erase(std::remove_if(directions.begin(), directions.end(),
                                  [this](Coordinate c) {
                                    return layout[c.x][c.y] == BORDER ||
                                           layout[c.x][c.y] == OBSTACLE;
                                  }),
                   directions.end());

  return directions;
}

// ======================[ Static Methods ]===================== //
// Create Map from txt file
Map Map::from_txt(const std::string &filename) {
  int width = 0;
  int height = 0;
  std::vector<std::vector<FieldValue>> layout;

  std::string line;
  std::ifstream file(filename);

  int linecount = 0;

  while (getline(file, line)) {
    if (linecount == 1) {
      int start_index = 7;
      int end_index = line.size() - 1;

      height = std::stoi(line.substr(start_index, end_index - start_index + 1));
    }
    if (linecount == 2) {
      int start_index = 6;
      int end_index = line.size() - 1;

      width = std::stoi(line.substr(start_index, end_index - start_index + 1));
      layout.resize(width);
      for (int x = 0; x < width; x++) {
        layout[x].resize(height);
      }
    }
    if (linecount > 3) {
      int y = height - 1 - (linecount - 4);

      for (int x = 0; x < width; x++) {
        FieldValue value;
        if (line[x] == '.') {
          value = FREE;
        }
        if (line[x] == 'T') {
          value = OBSTACLE;
        }
        if (line[x] == '@') {
          value = BORDER;
        }
        layout[x][y] = value;
      }
    }

    linecount++;
  }

  file.close();

  return Map(width, height, layout);
}