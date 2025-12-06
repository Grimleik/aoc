/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d3.h"
#include "utils.h"

// #define VERBOSE

d3::d3()
{
	input_file = read_entire_file("d3_test.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(357, 3121910778619)));
	// input_file = read_entire_file("d3.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(17432, 173065202451341)));
}
bool d3::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct joltage_t
{
	std::string_view &s;
	size_t total;
	size_t len;
	const char *values[12];
};

std::pair<d3::ans_t, d3::ans_t> d3::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	std::vector<joltage_t> joltages;
	auto splits = string_view_split(sv);
	for (auto &s : splits)
	{
		joltages.push_back({s, string_view_to_int(s), s.size() - 1});
	}

	constexpr int ss = 12;
	for (auto &j : joltages)
	{
		int search_space = ss;
		for (int i = j.len; i > j.len - search_space; --i)
			j.values[search_space - (j.len - i) - 1] = &j.s[i];

		for (int i = (j.len - search_space); i >= 0 && search_space > 0; --i)
		{
			int active = j.s[i];
			if (active >= *j.values[0])
			{
				const char *tmp = j.values[0];
				for (int k = 1; k < search_space; ++k)
				{
					if (*tmp >= *j.values[k])
					{
						std::swap(j.values[k], tmp);
					}
					else
						break;
				}
				j.values[0] = &j.s[i];
				bool breakout = true;
				for (auto c : j.values)
				{
					if (*c != '9')
					{
						breakout = false;
						break;
					}
				}
			}
		}
		size_t value = 0;
		// P1:
		int idx = ss - 2;
		for (int i = idx; i >= 0; --i)
		{
			if (*j.values[i] >= *j.values[idx])
			{
				idx = i;
			}
		}
		value = ((*j.values[idx]) - '0');
		int next = 0;
		for (int i = idx + 1; i < ss; ++i)
		{
			next = std::max(next, *j.values[i] - '0');
		}
		value = value * 10 + next;
		result.first += value;
		// P2:
		value = 0;
		for (int i = 0; i < ss; ++i)
		{
			value = value * 10 + ((*j.values[i]) - '0');
		}
		result.second += value;
	}
	return result;
}
