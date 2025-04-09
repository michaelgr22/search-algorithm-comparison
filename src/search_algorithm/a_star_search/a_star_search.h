#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include "../best_first_search.h"
#include "../node.h"

class AStarSearch : public BestFirstSearch {
public:
  double evaluation_function(std::shared_ptr<Node> node) override {
    return (node->get_path_cost() + node->get_heuristic());
  }

  std::string get_name() const override { return "A* Search"; }
};

#endif