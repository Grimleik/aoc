/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d4.h"
#include "utils.h"

// #define VERBOSE

d4::d4()
{
	// input_file = read_entire_file("d4_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(13, 43)));
	input_file = read_entire_file("d4.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(1424, 8727)));
}
bool d4::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d4::ans_t, d4::ans_t> d4::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	std::vector<std::string> map;
	std::vector<std::string> next_map;
	int w = 0, h = 0;
	for (auto &s : string_view_split(sv))
	{
		map.push_back(std::string(s));
		next_map.push_back(std::string(s));
	}
	w = map.back().size();
	h = map.size();

	// std::cout << w << ", " << h << std::endl;

	int removal = 0;
	do
	{
		removal = 0;
		for (size_t y = 0; y < h; ++y)
		{
			for (size_t x = 0; x < w; ++x)
			{
				if (map[y][x] != '@')
					continue;
				int roll_counter = 0;
				for (int j = std::max((int)y - 1, 0); j <= std::min((int)y + 1, h - 1); ++j)
				{
					for (int i = std::max((int)x - 1, 0); i <= std::min((int)x + 1, w - 1); ++i)
					{
						if ((i == x && j == y) || map[j][i] != '@')
							continue;
						++roll_counter;
						if (roll_counter > 3)
							break;
					}
				}
				if (roll_counter < 4)
				{
					next_map[y][x] = 'x';
					removal++;
				}
			}
		}
		if (result.first == 0)
			result.first = removal;
		result.second += removal;
		map = next_map;
	} while (removal > 0);

	// for (auto &s : next_map)
	// 	std::cout << s << std::endl;
	return result;
}