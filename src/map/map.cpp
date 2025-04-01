#include "map.h"
#include <stdexcept>

// ======================[ Public Methods ]===================== //

void Map::set_scenario(Coordinate s, Coordinate g) {
  start.x = s.x;
  start.y = s.y;
  goal.x = g.x;
  goal.y = g.y;

  if (layout[start.x][start.y] == FREE && layout[goal.x][goal.y] == FREE) {
    layout[start.x][start.y] = START;
    layout[goal.x][goal.y] = GOAL;
  } else {
    throw std::runtime_error("Scenario not valid!");
  }
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