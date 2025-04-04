#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include <mutex>
#include <queue>
#include <vector>

#include "node.h"
#include "search_algorithm.h"

class BestFirstSearch : public SearchAlgorithm {
private:
private:
  std::queue<std::shared_ptr<Node>> data_queue;
  std::mutex data_queue_mutex;
  std::shared_ptr<Node> goal = nullptr;

public:
  virtual double evaluation_function(std::shared_ptr<Node> node) = 0;
  virtual ~BestFirstSearch() = default;

  std::shared_ptr<Node> goal_node() override { return goal; }

  std::shared_ptr<Node> pop_node() override {
    std::lock_guard<std::mutex> lock(data_queue_mutex);
    if (data_queue.empty())
      return nullptr;
    auto node = data_queue.front();
    data_queue.pop();
    return node;
  }

  std::shared_ptr<Node> solve(Map *map) override {
    std::cout << "Solving..." << std::endl;

    /*auto cmp = [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
      return a->heuristic > b->heuristic; // Min-heap (smallest distance first)
    };*/
    auto cmp = [this](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
      return evaluation_function(a) > evaluation_function(b); // A*
    };
    std::priority_queue<std::shared_ptr<Node>,
                        std::vector<std::shared_ptr<Node>>, decltype(cmp)>
        frontier(cmp);
    std::vector<std::shared_ptr<Node>> reached;

    std::shared_ptr<Node> node = std::make_shared<Node>();
    node->state = map->get_start();
    node->heuristic = node->state.l2_distance(map->get_goal());
    node->path_cost = 0;

    frontier.push(node);
    reached.push_back(node);
    std::cout << "Initial push..." << std::endl;

    while (true) {
      if (frontier.empty())
        return nullptr;

      node = frontier.top();
      frontier.pop();
      std::cout << "Node State:" << node->state.x << " " << node->state.y
                << std::endl;

      // for gui
      std::lock_guard<std::mutex> lock(data_queue_mutex);
      data_queue.push(node);

      if (node->state == map->get_goal()) {
        goal = node;
        return node;
      }

      for (const Coordinate &c : map->expand_node(node->state)) {
        std::shared_ptr<Node> child = std::make_shared<Node>();
        child->state = c;
        std::cout << "child State:" << child->state.x << " " << child->state.y
                  << std::endl;
        child->parent = node;
        child->heuristic = child->state.l2_distance(map->get_goal());
        std::cout << "child heuristic:" << child->heuristic << std::endl;
        std::cout << "child heuristic:" << child->heuristic << std::endl;
        child->path_cost = child->parent->path_cost + 1;

        auto it = std::find_if(
            reached.begin(), reached.end(),
            [&child](const std::shared_ptr<Node> &n) { return *n == *child; });

        // check if child exists in reached
        if (it == reached.end()) {
          reached.push_back(child);
          frontier.push(child);
          //
        } else if (child->path_cost < it->get()->path_cost) {
          *it = child;
          frontier.push(child);
        }
      }
    }
  };
};

#endif