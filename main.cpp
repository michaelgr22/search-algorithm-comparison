#include "src/gui/gui.h"
#include "src/search_algorithm/best_first_search.h/best_first_search.h"
#include "src/search_algorithm/search_algorithm.h"
#include "src/search_problem/search_problem.h"

#include <memory>
#include <thread>

int main() {
  std::string filename = "arena2";

  SearchProblem sp = SearchProblem(filename, 385);

  std::unique_ptr<SearchAlgorithm> bfs =
      std::unique_ptr<SearchAlgorithm>(new BestFirstSearch());

  std::thread bfs_solver([&]() { sp.solve(bfs.get()); });

  Gui gui = Gui(sp.map.get(), bfs.get(), 5);
  gui.simulate_search_path();

  bfs_solver.join();

  return 0;
}
