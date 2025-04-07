#include "src/gui/gui.h"
#include "src/search_algorithm/greedy_best_first_search/greedy_best_first_search.h"
#include "src/search_algorithm/search_algorithm.h"
#include "src/search_problem/search_problem.h"

#include <memory>
#include <thread>

int main() {
  std::string filename = "Berlin_0_256";

  SearchProblem sp = SearchProblem(filename, 301);

  std::unique_ptr<SearchAlgorithm> gbfs =
      std::unique_ptr<SearchAlgorithm>(new GreedyBestFirstSearch());

  std::thread bfs_solver([&]() { sp.solve(gbfs.get()); });

  Gui gui = Gui(sp.map.get(), gbfs.get(), 5);
  gui.simulate_search_path();

  bfs_solver.join();

  return 0;
}
