/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d23.h"

d23::d23()
{
	input_file = read_entire_file("../../../../2015/input/d23.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(0, 0)));
}

bool d23::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d23::ans_t, d23::ans_t> d23::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;

	return result;
}
