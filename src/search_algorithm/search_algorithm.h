#ifndef SEARCH_ALGORITHM_H
#define SEARCH_ALGORITHM_H

#include "../map/map.h"
#include "node.h"

#include <memory>
#include <vector>

class SearchAlgorithm {
public:
  virtual std::shared_ptr<Node> solve(Map *map) = 0;
  virtual ~SearchAlgorithm() = default;
};

#endif