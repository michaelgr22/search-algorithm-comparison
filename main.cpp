#include "src/gui/gui.h"
#include "src/search_algorithm/a_star_search/a_star_search.h"
#include "src/search_algorithm/dijkstra_search/dijkstra_search.h"
#include "src/search_algorithm/greedy_best_first_search/greedy_best_first_search.h"
#include "src/search_algorithm/search_algorithm.h"
#include "src/search_problem/search_problem.h"

#include <memory>
#include <thread>

int main() {
  std::string filename = "Berlin_0_256";

  SearchProblem sp = SearchProblem(filename, 122);
  // 289

  std::unique_ptr<SearchAlgorithm> gbfs =
      std::unique_ptr<SearchAlgorithm>(new AStarSearch());
  std::unique_ptr<SearchAlgorithm> astar =
      std::unique_ptr<SearchAlgorithm>(new GreedyBestFirstSearch());
  std::unique_ptr<SearchAlgorithm> dijkstra =
      std::unique_ptr<SearchAlgorithm>(new DijkstraSearch());

  Gui gui = Gui(sp.map.get(), {gbfs.get(), astar.get(), dijkstra.get()});

  std::thread bfs_solver([&]() { sp.solve(gbfs.get()); });
  std::thread astar_solver([&]() { sp.solve(astar.get()); });
  std::thread dijkstra_solver([&]() { sp.solve(dijkstra.get()); });

  gui.simulate_search_path();

  bfs_solver.join();
  astar_solver.join();
  dijkstra_solver.join();

  return 0;
}
