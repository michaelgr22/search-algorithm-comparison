#include "src/gui/gui.h"
#include "src/search_algorithm/a_star_search/a_star_search.h"
#include "src/search_algorithm/greedy_best_first_search/greedy_best_first_search.h"
#include "src/search_algorithm/search_algorithm.h"
#include "src/search_problem/search_problem.h"

#include <memory>
#include <thread>

int main() {
  std::string filename = "Berlin_0_256";

  SearchProblem sp = SearchProblem(filename, 102);

  std::unique_ptr<SearchAlgorithm> gbfs =
      std::unique_ptr<SearchAlgorithm>(new GreedyBestFirstSearch());
  std::unique_ptr<SearchAlgorithm> astar =
      std::unique_ptr<SearchAlgorithm>(new AStarSearch());
  std::unique_ptr<SearchAlgorithm> gbfs2 =
      std::unique_ptr<SearchAlgorithm>(new GreedyBestFirstSearch());

  std::thread bfs_solver([&]() { sp.solve(gbfs.get()); });
  std::thread astar_solver([&]() { sp.solve(astar.get()); });
  std::thread bfs_solver2([&]() { sp.solve(gbfs2.get()); });

  Gui gui = Gui(sp.map.get());
  gui.simulate_search_path({gbfs.get(), astar.get(), gbfs2.get()});

  bfs_solver.join();
  astar_solver.join();
  bfs_solver2.join();

  return 0;
}
