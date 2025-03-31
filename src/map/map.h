#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../coordinate/coordinate.h"

enum FieldValue { FREE = 1, OBSTACLE = 2, BORDER = 3, START = 4, GOAL = 5 };

class Map {
private:
  std::vector<std::vector<FieldValue>> layout;
  Coordinate start;
  Coordinate goal;

public:
  const int width;
  const int height;
  Map(const int width, const int height,
      const std::vector<std::vector<FieldValue>> &layout)
      : width(width), height(height), layout(layout), start(Coordinate(-1, -1)),
        goal(Coordinate(-1, -1)) {}

  static Map from_txt(const std::string &filename);
  void set_scenario(Coordinate start, Coordinate goal);
  std::vector<Coordinate> expand_node(Coordinate node);

  std::vector<std::vector<FieldValue>> get_layout() { return layout; }
  Coordinate get_start() { return start; }
  Coordinate get_goal() { return goal; }
};

#endif