
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d1.h"
#include "utils.h"

d1::d1()
{
	input_file = read_entire_file("d1.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(1141, 0)));
}
bool d1::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d1::ans_t, d1::ans_t> d1::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	int track = 50;
	for (auto &s : string_view_split(sv))
	{
		char sign = s[0];
		s.remove_prefix(1);
		int val = string_view_to_int(s);
		int revs = val / 100;
		val -= revs * 100;
		result.second += abs(revs);
		if (sign == 'R')
		{
			if (track != 0 && (val + track) >= 100)
				result.second++;
		}
		else
		{
			val *= -1;
			if (track != 0 && (val + track) <= 0)
				result.second++;
		}
		track = (track + val + 100) % 100;
		if (track == 0)
		{
			result.first++;
		}
	}
	return result;
}