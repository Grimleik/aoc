/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d24.h"

d24::d24()
{
	input_file = read_entire_file("../../../../2015/input/d24.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(0, 0)));
}

bool d24::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d24::ans_t, d24::ans_t> d24::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;

	return result;
}
