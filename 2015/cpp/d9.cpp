/*========================================================================
    Creator: Grimleik $

    STUDY: Previously we did row sumation here. However, this represents the
    traveling salesman which means that each time we 'move' from one index to
    another we traverse that 'path'. This means we have to test the available
    permutations of the map, which is the rows/cols number of the map, where
    each index then represents a move. Then by summing those paths we get the
    path cost of that move and can compare it with other runs. Also there was an
    assumption to start at a particular city, 0, which is not necessarily the
    case.

    LEARNINGS: Assumptions and preconcieved notions how to do things are a
    killer. Also more failures should be practiced.
========================================================================*/
#include "utils.h"
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

void d9() {
  int test_map[3][3] = {};
  test_map[0][0] = 0;   // LONDON
  test_map[0][1] = 464; // LONDON -> DUBLIN
  test_map[0][2] = 518; // LONDON -> BELFAST

  test_map[1][0] = 464; // DUBLIN -> LONDON
  test_map[1][1] = 0;   // DUBLIN
  test_map[1][2] = 141; // DUBLIN -> BELFAST

  test_map[2][0] = 518; // BELFAST -> LONDON
  test_map[2][1] = 141; // BELFAST -> DUBLIN
  test_map[2][2] = 0;   // BELFAST

  int bestPath = INT_MAX;
  for (int i = 0; i < 3; ++i) {
    int pathCost = 0;
    for (int j = 0; j < 3; ++j) {
      pathCost += test_map[i][j];
    }
    bestPath = std::min(bestPath, pathCost);
  }

  std::cout << "\tTest: " << bestPath << std::endl;
  int map[8][8] = {};
  map[0][0] = 0;   // Faerun
  map[0][1] = 129; // Faerun -> Norrath
  map[0][2] = 58;  // Faerun -> Tristram
  map[0][3] = 13;  // Faerun -> AlphaCentauri
  map[0][4] = 24;  // Faerun -> Arbre
  map[0][5] = 60;  // Faerun -> Snowdin
  map[0][6] = 71;  // Faerun -> Tambi
  map[0][7] = 67;  // Faerun -> Straylight

  map[1][0] = 129; // Norrath -> Faerun
  map[1][1] = 0;   // Norrath
  map[1][2] = 142; // Norrath -> Tristram
  map[1][3] = 15;  // Norrath -> AlphaCentauri
  map[1][4] = 135; // Norrath -> Arbre
  map[1][5] = 75;  // Norrath -> Snowdin
  map[1][6] = 82;  // Norrath -> Tambi
  map[1][7] = 54;  // Norrath -> Straylight

  map[2][0] = 58;  // Tristram -> Faerun
  map[2][1] = 142; // Tristram -> Norrath
  map[2][2] = 0;   // Tristram
  map[2][3] = 118; // Tristram -> AlphaCentauri
  map[2][4] = 122; // Tristram -> Arbre
  map[2][5] = 103; // Tristram -> Snowdin
  map[2][6] = 49;  // Tristram -> Tambi
  map[2][7] = 97;  // Tristram -> Straylight

  map[3][0] = 13;  // AlphaCentauri -> Faerun
  map[3][1] = 15;  // AlphaCentauri -> Norrath
  map[3][2] = 118; // AlphaCentauri -> Tristram
  map[3][3] = 0;   // AlphaCentauri
  map[3][4] = 116; // AlphaCentauri -> Arbre
  map[3][5] = 12;  // AlphaCentauri -> Snowdin
  map[3][6] = 18;  // AlphaCentauri -> Tambi
  map[3][7] = 91;  // AlphaCentauri -> Straylight

  map[4][0] = 24;  // Arbre -> Faerun
  map[4][1] = 135; // Arbre -> Norrath
  map[4][2] = 122; // Arbre -> Tristram
  map[4][3] = 116; // Arbre -> AlphaCentauri
  map[4][4] = 0;   // Arbre
  map[4][5] = 129; // Arbre -> Snowdin
  map[4][6] = 53;  // Arbre -> Tambi
  map[4][7] = 40;  // Arbre -> Straylight

  map[5][0] = 60;  // Snowdin -> Faerun
  map[5][1] = 75;  // Snowdin -> Norrath
  map[5][2] = 103; // Snowdin -> Tristram
  map[5][3] = 12;  // Snowdin -> AlphaCentauri
  map[5][4] = 129; // Snowdin -> Arbre
  map[5][5] = 0;   // Snowdin
  map[5][6] = 15;  // Snowdin -> Tambi
  map[5][7] = 99;  // Snowdin -> Straylight

  map[6][0] = 71; // Tambi -> Faerun
  map[6][1] = 82; // Tambi -> Norrath
  map[6][2] = 49; // Tambi -> Tristram
  map[6][3] = 18; // Tambi -> AlphaCentauri
  map[6][4] = 53; // Tambi -> Arbre
  map[6][5] = 15; // Tambi -> Snowdin
  map[6][6] = 0;  // Tambi
  map[6][7] = 70; // Tambi -> Straylight

  map[7][0] = 67; // Straylight -> Faerun
  map[7][1] = 54; // Straylight -> Norrath
  map[7][2] = 97; // Straylight -> Tristram
  map[7][3] = 91; // Straylight -> AlphaCentauri
  map[7][4] = 40; // Straylight -> Arbre
  map[7][5] = 99; // Straylight -> Snowdin
  map[7][6] = 70; // Straylight -> Tambi
  map[7][7] = 0;  // Straylight

  std::vector<int> cities = {0, 1, 2, 3, 4, 5, 6, 7};
  int shortestPath = INT_MAX;
  int longestPath = -INT_MAX;
  do {
    int pathCost = 0;
    // Calculate cost of traveling through the permutation in order
    for (int i = 0; i < (int)cities.size() - 1; ++i) {
      int from = cities[i];
      int to = cities[i + 1];
      int cost = map[from][to];

      pathCost += cost;
    }

    if (pathCost > longestPath) {
      longestPath = pathCost;
    }
    if (pathCost < shortestPath) {
      shortestPath = pathCost;
    }

  } while (std::next_permutation(cities.begin(), cities.end()));
  std::cout << "\t1: " << shortestPath << std::endl;
  std::cout << "\t2: " << longestPath << std::endl;
}
