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

	FUTURE: Handle a more general sized input ?
========================================================================*/
#include "utils.h"
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "d9.h"

d9::d9()
{
	input_file = read_entire_file("../../../../2015/input/d9.in");
	input.emplace_back(std::string_view(input_file->mem, input_file->sz), std::make_pair(207, 804));
}

bool d9::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

void d9::parse_map(const std::string_view &sv)
{
	std::map<std::string, int> city_ids;
	int city_id = 0;

	auto lines = string_view_split(sv, '\n');
	for (auto &line : lines)
	{
		auto parts = string_view_split(line, ' ', true);
#ifdef VERBOSE
		if (parts.size() != 5)
		{
			std::cout << "Invalid line: " << line << " input requires, origin, to, target, equals, distance. -> 5 strings " << std::endl;
		}
#endif

		std::string fromCity = std::string(parts[0]);
		std::string toCity = std::string(parts[2]);
		int distance = std::stoi(std::string(parts[4]));

		if (city_ids.find(fromCity) == city_ids.end())
		{
			city_ids[fromCity] = city_id++;
		}
		if (city_ids.find(toCity) == city_ids.end())
		{
			city_ids[toCity] = city_id++;
		}

		int fromIndex = city_ids[fromCity];
		int toIndex = city_ids[toCity];

		map[fromIndex][toIndex] = distance;
		map[toIndex][fromIndex] = distance;
	}
}

std::pair<int, int> d9::solution(const std::string_view &sv)
{
	parse_map(sv);
	std::vector<int> cities = {0, 1, 2, 3, 4, 5, 6, 7};
	std::pair<int, int> result = {INT_MAX, INT_MIN};
	do
	{
		int pathCost = 0;
		// Calculate cost of traveling through the permutation in order
		for (int i = 0; i < (int)cities.size() - 1; ++i)
		{
			int from = cities[i];
			int to = cities[i + 1];
			int cost = map[from][to];

			pathCost += cost;
		}

		if (pathCost > result.second)
		{
			result.second = pathCost;
		}
		if (pathCost < result.first)
		{
			result.first = pathCost;
		}

	} while (std::next_permutation(cities.begin(), cities.end()));
	return result;
}