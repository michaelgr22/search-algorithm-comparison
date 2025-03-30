#ifndef NODE_H
#define NODE_H

#include "../coordinate/coordinate.h"
#include <algorithm>
#include <limits>
#include <memory>

class Node {
public:
  Coordinate state;
  std::shared_ptr<Node> parent;
  Coordinate action;
  double heuristic;
  unsigned int path_cost;

  Node()
      : state(Coordinate(-1, -1)), parent(nullptr), action(Coordinate(-1, -1)),
        heuristic(-1), path_cost(std::numeric_limits<unsigned int>::max()) {}

  bool operator==(const Node &other) const { return state == other.state; }
};

#endif