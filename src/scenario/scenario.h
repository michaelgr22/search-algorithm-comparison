#ifndef SCENARIO_H
#define SCENARIO_H

#include "../coordinate/coordinate.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Scenario {
private:
  static std::vector<std::string> split(std::string s,
                                        const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      tokens.push_back(token);
      s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
  }

public:
  const Coordinate start;
  const Coordinate goal;
  const double distance;

  Scenario(const Coordinate start, const Coordinate goal, const double distance)
      : start(start), goal(goal), distance(distance) {}

  static Scenario from_txt(const std::string &filename, int id) {
    std::string line;
    std::ifstream file(filename);

    int linecount = 0;
    while (getline(file, line)) {
      if (linecount == id) {
        break;
      }
      linecount++;
    }

    const std::string delimiter = "\t";
    const std::vector<std::string> scenario_tokens =
        Scenario::split(line, delimiter);

    const int start_x = std::stoi(scenario_tokens[4]);
    const int start_y = std::stoi(scenario_tokens[5]);
    const int goal_x = std::stoi(scenario_tokens[6]);
    const int goal_y = std::stoi(scenario_tokens[7]);
    const double distance = std::stod(scenario_tokens[8]);

    return Scenario(Coordinate(start_x, start_y), Coordinate(goal_x, goal_y),
                    distance);
  }
};

#endif