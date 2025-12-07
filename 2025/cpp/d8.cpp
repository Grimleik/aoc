
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d8.h"
#include "utils.h"

// #define VERBOSE

d8::d8()
{
	input_file = read_entire_file("d8_test.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(0, 0)));
	// input_file = read_entire_file("d8.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(23039913998, 35950619148)));
}
bool d8::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d8::ans_t, d8::ans_t> d8::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	for (auto &p : parse)
		std::cout << p << std::endl;
	return result;
}