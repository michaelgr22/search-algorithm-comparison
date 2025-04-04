#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "node.h"
#include "search_algorithm.h"

class BestFirstSearch : public SearchAlgorithm {
public:
  virtual double evaluation_function(std::shared_ptr<Node> node) = 0;
  virtual ~BestFirstSearch() = default;
};

#endif