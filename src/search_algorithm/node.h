#ifndef NODE_H
#define NODE_H

#include "../coordinate/coordinate.h"
#include <algorithm>
#include <limits>
#include <memory>

class Node {
private:
  Coordinate state;
  std::shared_ptr<Node> parent;
  double heuristic;
  unsigned int path_cost;

public:
  Node()
      : state(Coordinate(-1, -1)), parent(nullptr), heuristic(-1),
        path_cost(std::numeric_limits<unsigned int>::max()) {}

  Node(Coordinate state, std::shared_ptr<Node> parent, double heuristic,
       unsigned int path_cost)
      : state(state), parent(parent), heuristic(heuristic),
        path_cost(path_cost) {}

  unsigned int get_path_cost() const { return path_cost; }
  Coordinate get_state() const { return state; }
  std::shared_ptr<Node> get_parent() const { return parent; }
  double get_heuristic() const { return heuristic; }

  void update_node(Coordinate s, std::shared_ptr<Node> p, double h,
                   unsigned int pc) {
    state = s;
    parent = p;
    heuristic = h;
    path_cost = pc;
  }

  bool operator==(const Node &other) const { return state == other.state; }
};

#endif