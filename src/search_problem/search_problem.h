#ifndef SEARCH_PROBLEM_H
#define SEARCH_PROBLEM_H

#include <memory>

#include "../map/map.h"
#include "../scenario/scenario.h"
#include "../search_algorithm/search_algorithm.h"

class SearchProblem {
public:
  std::unique_ptr<Map> map;
  std::unique_ptr<Scenario> scenario;

  SearchProblem(const std::string &map_file_name, int scenario_id) {
    const std::string map_folder = "dao-map";
    const std::string scenario_folder = "dao-scen";
    const std::string map_path = map_folder + "/" + map_file_name + ".map";
    const std::string scenario_path =
        scenario_folder + "/" + map_file_name + ".map.scen";

    map = std::make_unique<Map>(Map::from_txt(map_path));

    scenario = std::make_unique<Scenario>(
        Scenario::from_txt(scenario_path, scenario_id));

    map->set_scenario(scenario->start, scenario->goal);
  }

  void draw() { map->draw(); }
  std::shared_ptr<Node> solve(SearchAlgorithm *algorithm) {
    return algorithm->solve(map.get());
  }
};

#endif