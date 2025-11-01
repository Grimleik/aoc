/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d19.h"

d19::d19()
{
	input_file = read_entire_file("../../../../2015/input/d19.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(518, 200)));
}

bool d19::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

static int minimal_steps_by_formula(std::string_view mol)
{
	int tokens = 0;
	int rn = 0, ar = 0, y = 0;
	for (size_t i = 0; i < mol.size();)
	{
		char c = mol[i];
		if ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')
		{
			++tokens;
			if (i + 1 < mol.size() && (unsigned char)mol[i + 1] >= 'a' && (unsigned char)mol[i + 1] <= 'z')
			{
				// two-letter token
				if (mol[i] == 'R' && mol[i + 1] == 'n')
					++rn;
				else if (mol[i] == 'A' && mol[i + 1] == 'r')
					++ar;
				i += 2;
				continue;
			}
			// single-letter token
			if (mol[i] == 'Y')
				++y;
			i += 1;
		}
		else
		{
			// defensive: skip unexpected chars
			++i;
		}
	}
	return tokens - rn - ar - 2 * y - 1;
}

std::pair<d19::ans_t, d19::ans_t> d19::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, INT_MAX};
	std::map<size_t, std::unordered_map<std::string_view, std::vector<std::string>>> rules_p1;
	std::map<size_t, std::unordered_map<std::string_view, std::vector<std::string>>> rules_p2;

	const std::string_view *transform_target = nullptr;
	auto splits = string_view_split(sv);
	for (int i = 0; i < splits.size(); ++i)
	{
		auto &split = splits[i];

		if (split.empty())
		{
			transform_target = &splits[i + 1];
			break;
		}
		auto slice = string_view_split(split, ' ', true);
		if (rules_p1.find(slice[0].size()) == rules_p1.end())
		{
			rules_p1.insert(std::make_pair(slice[0].size(), std::unordered_map<std::string_view, std::vector<std::string>>()));
		}

		if (rules_p2.find(slice[0].size()) == rules_p2.end())
		{
			rules_p2.insert(std::make_pair(slice[2].size(), std::unordered_map<std::string_view, std::vector<std::string>>()));
		}
		rules_p1[slice[0].size()][slice[0]].emplace_back(slice[2]);
		rules_p2[slice[2].size()][slice[2]].emplace_back(slice[0]);
	}

	const size_t N = transform_target->size();
	std::set<std::string> unique_names;
	for (auto i = 0; i < N; ++i)
	{
		std::string intermediary_transformation(*transform_target);
		for (auto &[rSize, rSet] : rules_p1)
		{
			std::string target(transform_target->substr(i, rSize));
			for (auto xform : rSet[target])
			{
				std::string transformation(intermediary_transformation);
				unique_names.insert(transformation.replace(i, rSize, xform));
			}
		}
	}
	result.first = (int)unique_names.size();

	// TODO: Go the other way try to reduce the string by inverted lookups from transform_target -> e. Same thing.
	std::function<bool(std::string_view, int)> dfs = [&](std::string_view str, int steps)
	{
		if (str == "e")
		{
			result.second = steps;
			return true;
		}

		for (i64 i = str.size() - 1; i >= 0; --i)
		{
			for (auto it = rules_p2.rbegin(); it != rules_p2.rend(); ++it)
			{
				auto &rSize = it->first;
				auto &rSet = it->second;
				std::string target(str.substr(i, rSize));
				if (rSet.find(target) != rSet.end())
				{
					// for (auto xform : rSet[target])
					for (auto it2 = rSet[target].rbegin(); it2 != rSet[target].rend(); ++it2)
					{
						std::string transformation(str);
						transformation.replace(i, rSize, *it2);
						if (transformation.size() > str.size())
							continue;
						if (dfs(transformation, steps + 1))
							return true;
					}
				}
			}
		}
		return false;
	};

	// STUDY THIS SOLUTION:
	auto ans = minimal_steps_by_formula(*transform_target);
	dfs(*transform_target, 0);

	return result;
}