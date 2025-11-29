/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d25.h"

d25::d25()
{
	input_file = read_entire_file("d25.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(0, 0)));
}

bool d25::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d25::ans_t, d25::ans_t> d25::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;

	return result;
}
