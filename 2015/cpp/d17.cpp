/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d17.h"

d17::d17()
{
	input_file = read_entire_file("../../../../2015/input/d17.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(1638, 17)));
}

bool d17::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d17::ans_t, d17::ans_t> d17::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	std::vector<int> containers;
	containers.reserve(sv.size());
	for (auto &line : string_view_split(sv))
	{
		containers.emplace_back(string_view_to_int(line));
	}
	// Sort so we can exit early!
	std::sort(containers.begin(), containers.end());
	int minimum_active_containers = INT_MAX;
	const int N = (int)containers.size();
	std::function<void(int, int, int)> dfs =
		[&](int idx, int rem, int ac)
	{
		if (rem == 0)
		{
			result.first++;
			if (minimum_active_containers >= ac)
			{
				if (minimum_active_containers > ac)
				{
					result.second = 0;
				}
				result.second++;
				minimum_active_containers = ac;
			}
			return;
		}

		if (rem < 0 || idx >= N)
			return;
		for (int i = idx; i < N; ++i)
		{
			if (containers[i] > rem)
				break;
			dfs(i + 1, rem - containers[i], ac + 1);
		}
	};

	dfs(0, 150, 0);
	return result;
}
