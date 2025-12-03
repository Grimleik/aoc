/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d2.h"
#include "utils.h"

// #define VERBOSE

d2::d2()
{
	// input_file = read_entire_file("d2_test.in");
	input_file = read_entire_file("d2.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(1227775554, 4174379265)));
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(23039913998, 35950619148)));
}
bool d2::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct range_t
{
	size_t min, l0;
	size_t max, l1;
};

std::pair<d2::ans_t, d2::ans_t> d2::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	std::vector<range_t> ranges;
	for (auto &s : string_view_split(sv, ',', true))
	{
		auto range = string_view_split(s, '-', true);
		ranges.push_back(range_t{
			string_view_to_int(range[0]), range[0].size(),
			string_view_to_int(range[1]), range[1].size()});
	}
	for (auto &r : ranges)
	{
		// std::cout << "Range: " << r.max << " " << r.l1 << " "
		// 		  << r.min << " " << r.l0 << " -> "
		// 		  << ((double)r.max / r.min) << std::endl;
		size_t start = r.min, stop = r.max;
		for (size_t s = start; s <= stop; ++s)
		{
			auto str = std::to_string(s);
			bool found = false;
			size_t length = str.length() * 0.5;
			for (int len = 1; len <= length && !found; ++len)
			{
				if ((str.length() % len))
					continue;
				auto substr1 = str.substr(0, len);
				std::string str1;
				for (int i = 0; i < (str.length() - len) / len; ++i)
					str1 += substr1;
				auto str2 = str.substr(len, str.size());
				found = str1 == str2;
				if (found)
				{
					if (str.substr(0, length) == str.substr(length, str.size()))
					{
#ifdef VERBOSE
						std::cout << "FOUND1: " << str << std::endl;
#endif
						result.first += s;
					}
#ifdef VERBOSE
					std::cout << "FOUND2: " << str << std::endl;
#endif
					assert(str1[0] != '0');
					assert(result.first + s > result.first);
					result.second += s;
				}
			}
		}
	}
	return result;
}