/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include <utility>
#include "utils.h"

static std::pair<std::vector<int>, std::vector<int>> tests[] = {
	{{1}, {1, 1}},
	{{1, 1}, {2, 1}},
	{{2, 1}, {1, 2, 1, 1}},
	{{1, 2, 1, 1}, {1, 1, 1, 2, 2, 1}},
	{{1, 1, 1, 2, 2, 1}, {3, 1, 2, 2, 1, 1}}};

void d10_solve(const std::vector<int> &input, std::vector<int> &output)
{
	for (size_t i = 0; i < input.size();)
	{
		for (size_t j = i; j < input.size(); ++j)
		{
			if (input[i] != input[j])
			{
				// Insert the diff count..
				output.push_back(j - i);
				// .. then insert the 'number'.
				output.push_back(input[i]);
				// output.insert(output.end(), j - i, input[i]);
				i = j;
				break;
			}
			else if (j + 1 >= input.size())
			{
				++j;
				// Insert the diff count..
				output.push_back(j - i);
				// .. then insert the 'number'.
				output.push_back(input[i]);
				// output.insert(output.end(), j - i, input[i]);
				i = j;
				break;
			}
		}
	}
}

void d10()
{
	std::vector<int> output;
	for (int i = 0; i < ARRAY_COUNT(tests); ++i)
	{
		auto &input = tests[i].first;
		auto &solution = tests[i].second;
		output.clear();
		d10_solve(input, output);
		if (solution == output)
		{
			std::cout << "Tests passed." << std::endl;
		}
		else
		{
			std::cout << "Tests failed. Solution (" << solution << ") Output(" << output << ")." << std::endl;
			return;
		}
	}
	std::vector<int> input = {3, 1, 1, 3, 3, 2, 2, 1, 1, 3};
	for (int it = 0; it < 50; ++it)
	{
		output.clear();
		d10_solve(input, output);
		// std::cout << output << std::endl;
		input = output;
	}
	std::cout << "Final ans is: " << input.size(); //<< " Sequence: " << input << std::endl;
}