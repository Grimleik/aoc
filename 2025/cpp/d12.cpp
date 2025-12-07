
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d12.h"
#include "utils.h"

// #define VERBOSE

d12::d12()
{
	input_file = read_entire_file("d12_test.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(0, 0)));
	// input_file = read_entire_file("d12.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(23039913998, 35950619148)));
}
bool d12::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d12::ans_t, d12::ans_t> d12::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	for (auto &p : parse)
		std::cout << p << std::endl;
	return result;
}