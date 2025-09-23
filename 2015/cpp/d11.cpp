/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "utils.h"
#include <string.h>

static std::string d11_solver(const std::string input)
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
	std::string result = input;
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

static std::pair<std::string, std::string> tests_d11[] = {
	{"abcdefgh", "abcdffaa"},
	{"ghijklmn", "ghjaabcc"}};

void d11()
{
	for (int i = 0; i < ARRAY_COUNT(tests_d11); ++i)
	{
		auto &input = tests_d11[i].first;
		auto &solution = tests_d11[i].second;
		std::string answer = d11_solver(input);
		if (solution == answer)
		{
			std::cout << "Tests passed." << std::endl;
		}
		else
		{
			std::cout << "Tests failed. Solution (" << solution << ") Ans(" << answer << ")." << std::endl;
			return;
		}
	}
	std::cout << d11_solver(d11_solver("cqjxjnds")) << std::endl;
}