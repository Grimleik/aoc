/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d5.h"
#include "utils.h"

d5::d5()
{
	// input_file = read_entire_file("d5_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(3, 14)));
	input_file = read_entire_file("d5.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(868, 354143734113772)));
}
bool d5::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d5::ans_t, d5::ans_t> d5::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto splits = string_view_split(sv);
	std::vector<range_t> ranges;
	ranges.reserve(splits.size());
	int idx = 0;
	while (!splits[idx].empty())
	{
		auto range = string_view_split(splits[idx], '-', true);
		ans_t min = string_view_to_int(range[0]);
		ans_t max = string_view_to_int(range[1]);
		ranges.emplace_back(range_t{min, max});
		++idx;
	}
	std::sort(ranges.begin(), ranges.end(), [](const range_t &l, const range_t &r)
			  { return l.min < r.min; });
	for (auto it = ranges.begin(); it != ranges.end();)
	{
		auto prev = it++;
		if (it == ranges.end())
			break;
		if (prev->max >= it->min)
		{
			prev->max = std::max(prev->max, it->max);
			ranges.erase(it);
			it = prev;
		}
	}
	for (auto r : ranges)
	{
		result.second += (r.max - r.min) + 1;
	}
	idx++;
	while (!splits[idx].empty())
	{
		ans_t id = string_view_to_int(splits[idx++]);
		for (auto r : ranges)
		{
			if (id >= r.min && id <= r.max)
			{
				result.first++;
				break;
			}
		}
	}
	return result;
}