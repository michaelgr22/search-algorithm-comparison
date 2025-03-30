#include "src/search_algorithm/best_first_search.h/best_first_search.h"
#include "src/search_algorithm/search_algorithm.h"
#include "src/search_problem/search_problem.h"
#include <memory>

int main() {
  std::string filename = "arena";
  // std::string filename = "dao-map/arena2.map";
  SearchProblem sp = SearchProblem(filename, 1);
  std::unique_ptr<SearchAlgorithm> bfs =
      std::unique_ptr<SearchAlgorithm>(new BestFirstSearch());

  Node goal = sp.solve(bfs.get());

  std::cout << goal.state.x << " " << goal.state.y << std::endl;

  /*
  for (int y = 48; y > 38; y--) {
    for (int x = 0; x < map.width; x++) {
      std::cout << map.get_layout()[x][y];
    }
    std::cout << std::endl;
  }*/

  return 0;
}
