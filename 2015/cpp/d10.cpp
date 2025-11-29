/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include <utility>
#include "utils.h"
#include "d10.h"

d10::d10()
{
	input_file = read_entire_file("d10.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem, input_file->sz),
									  std::make_pair(329356, 4666278)));
}

bool d10::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

static void solver(const std::vector<int> &input, std::vector<int> &output)
{
	output.clear();
	output.reserve(input.size() * 2);
	for (size_t i = 0; i < input.size();)
	{
		size_t j = i + 1;
		while (j < input.size() && input[j] == input[i])
			++j;
		output.push_back(static_cast<int>(j - i));
		output.push_back(input[i]);
		i = j;
	}
}

void parse_input(const std::string_view &sv, std::vector<int> &out)
{
	for (char c : sv)
	{
		if (is_numeric(c))
			out.emplace_back((int)c - '0');
#ifdef VERBOSE
		else
			std::cout << "Input parsing error, non numeric value in input." << std::endl;
#endif
	}
}

std::pair<int, int> d10::solution(const std::string_view &sv)
{
	std::pair<int, int> result = {0, 0};
	std::vector<int> output;
	std::vector<int> input;
	parse_input(sv, input);

	for (int it = 0; it < 50; ++it)
	{
		solver(input, output);
		input.swap(output);
		if (it == 39)
		{
			result.first = (int)input.size();
		}
	}
	result.second = (int)input.size();
	return result;
}
