#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>

class Coordinate {
public:
  int x;
  int y;

  Coordinate(int x, int y) : x(x), y(y) {}

  bool operator==(const Coordinate &other) const {
    return (x == other.x) && (y == other.y);
  }

  Coordinate operator+(const Coordinate &other) {
    return Coordinate(x + other.x, y + other.y);
  }

  double l2_distance(const Coordinate &other) const {
    int x_diff = x - other.x;
    int y_diff = y - other.y;
    return std::sqrt(y_diff * y_diff + x_diff * x_diff);
  }
};

#endif