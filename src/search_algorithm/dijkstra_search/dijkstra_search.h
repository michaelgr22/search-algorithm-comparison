#ifndef DIJKSTRA_SEARCH_H
#define DIJKSTRA_SEARCH_H

#include "../best_first_search.h"
#include "../node.h"

class DijkstraSearch : public BestFirstSearch {
public:
  double evaluation_function(std::shared_ptr<Node> node) override {
    return node->get_path_cost();
  }

  std::string get_name() const override { return "Dijkstra Search"; }
};

#endif