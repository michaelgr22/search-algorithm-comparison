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

    std::shared_ptr<Node> node = std::make_shared<Node>(
        map->get_start(), nullptr,
        map->get_start().l2_distance(map->get_goal()), 0);

    frontier.push(node);
    reached.push_back(node);
    std::cout << "Initial push..." << std::endl;

    while (true) {
      if (frontier.empty())
        return nullptr;

      node = frontier.top();
      frontier.pop();
      std::cout << "Node State:" << node->get_state().x << " "
                << node->get_state().y << std::endl;

      // for gui
      std::lock_guard<std::mutex> lock(data_queue_mutex);
      data_queue.push(node);

      if (node->get_state() == map->get_goal()) {
        goal = node;
        return node;
      }

      for (const Coordinate &c : map->expand_node(node->get_state())) {
        std::shared_ptr<Node> child = std::make_shared<Node>(
            c, node, c.l2_distance(map->get_goal()), node->get_path_cost() + 1);

        auto it = std::find_if(
            reached.begin(), reached.end(),
            [&child](const std::shared_ptr<Node> &n) { return *n == *child; });

        // check if child exists not in reached
        if (it == reached.end()) {
          reached.push_back(child);
          frontier.push(child);
          // if in reached compare path costs
        } else if (child->get_path_cost() < it->get()->get_path_cost()) {
          (*it)->update_node(child->get_state(), child->get_parent(),
                             child->get_heuristic(), child->get_path_cost());
          frontier.push(child);
        }
      }
    }
  };
};

#endif