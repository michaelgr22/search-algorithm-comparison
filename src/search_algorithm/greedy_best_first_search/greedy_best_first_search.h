#ifndef GREEDY_BEST_FIRST_SEARCH_H
#define GREEDY_BEST_FIRST_SEARCH_H

#include "../best_first_search.h"
#include "../node.h"

class GreedyBestFirstSearch : public BestFirstSearch {
public:
  double evaluation_function(std::shared_ptr<Node> node) override {
    return node->get_heuristic();
  }

  std::string get_name() const override { return "Greedy Best First Search"; }
};

#endif