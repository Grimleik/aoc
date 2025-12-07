
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d7.h"
#include "utils.h"

// #define VERBOSE

d7::d7()
{
	// input_file = read_entire_file("d7_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(21, 40)));
	input_file = read_entire_file("d7.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(1678, 357525737893560)));
}
bool d7::run()
{
	auto ans = solution(input[0].first);
	// CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d7::ans_t, d7::ans_t> d7::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	int begin = parse[0].find('S');
	int end = begin;
	std::vector<bool> floods(parse[0].size(), false);
	std::vector<size_t> paths(parse[0].size(), 0);
	floods[begin] = true;
	paths[begin] = 1;
	size_t h = 2;
	for (; h < parse.size() - 1; h += 2)
	{
		size_t total_nodes_for_level = 0;
		std::string output(parse[h]);
		for (auto it = begin; it <= end; ++it)
		{
			if (parse[h][it] == '^' && floods[it])
			{
				begin = std::max(std::min(begin, it - 1), 0);
				end = std::min(std::max(end, it + 1), (int)floods.size() - 2);
				floods[it - 1] = true;
				paths[it - 1] += paths[it];
				floods[it + 0] = false;
				floods[it + 1] = true;
				paths[it + 1] += paths[it];
				result.first++;
				paths[it] = 0;
			}
		}
		assert(begin >= 0);
		assert(end < parse[0].size());
	}
	for (auto p : paths)
		result.second += p;
	return result;
}
