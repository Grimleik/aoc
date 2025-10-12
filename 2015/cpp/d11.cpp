/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "utils.h"
#include <string.h>
#include "d11.h"

static std::string solver(const std::string_view &sv)
{
	// Define a rule set;
	std::vector<std::function<bool(const std::string &)>> rules = {
		// 3 chain rule..
		[](const std::string &str)
		{
			for (size_t i = 0; i < str.size() - 2; ++i)
			{
				if (str[i] == str[i + 1] - 1 &&
					str[i + 1] == str[i + 2] - 1)
					return true;
			}
			return false;
		},

		// black list letter rule..
		[](const std::string &str)
		{
			return str.find('i') == std::string::npos &&
				   str.find('o') == std::string::npos &&
				   str.find('l') == std::string::npos;
		},

		// must contain non overlapping pairs rule..
		[](const std::string &str)
		{
			int count = 0;
			static std::string used;
			used = "";
			for (size_t i = 0; i < str.size(); ++i)
			{
				if (used.find(str[i]) == std::string::npos && str[i] == str[i + 1])
				{
					count++;
					used += str[i];
					if (count > 1)
						break;
				}
			}
			return count > 1;
		},
	};

	std::string result(sv);
	bool search = true;
	while (search)
	{
		// increment last linearly..
		result[7]++;
		for (int i = 7; i >= 0; --i)
		{
			// .. propogate on wrap.
			if (result[i] > 'z')
			{
				result[i] = 'a';
				result[i - 1]++;
			}
			else
			{
				break;
			}
		}
		search = false;
		// .. then check rules for each letter from the begining.
		for (auto &rule : rules)
		{
			if (!rule(result))
			{
				search = true;
				break;
			}
		}
		// std::cout << result << std::endl;
	}

	return result;
}

d11::d11()
{
	input_file = read_entire_file("../../../../2015/input/d11.in");
	input.emplace_back(std::string_view(input_file->mem, input_file->sz), std::make_pair("cqjxxyzz", "cqkaabcc"));
}

bool d11::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d11::ans_t, d11::ans_t> d11::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;
	result.first = solver(sv);
	result.second = solver(result.first);
	return result;
}
