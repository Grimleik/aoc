/*========================================================================
	Creator: Grimleik $

	STUDY: Revisit this for a threaded approach, this is pure bruteforce
	for a 0.05s timer, can def. be improved and threaded.

	This was initially a fixed set of loops for the problem. Upon other
	days requiring similar combinatorical solving I went back and tried
	to learn how to swap fixed loops with recursion.
=======================================================================*/

#include "d15.h"
d15::d15()
{
	input_file = read_entire_file("d15.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(13882464, 11171160)));

	// input_file = read_entire_file(d15_test.in");
	// input.emplace_back(std::make_pair(std::string_view(input_file->mem),
	// 								  std::make_pair(0, 0)));
}

bool d15::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d15::ans_t, d15::ans_t> d15::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result{0, 0};

	std::vector<ingredient_t> ingredients;
	for (auto &line : string_view_split(sv))
	{
		auto parse = string_view_split(line, ' ', true);
		ingredients.emplace_back(ingredient_t{
			.capacity = string_view_to_int(parse[2]),
			.durability = string_view_to_int(parse[4]),
			.flavour = string_view_to_int(parse[6]),
			.texture = string_view_to_int(parse[8]),
			.calories = string_view_to_int(parse[10]),
		});
	}

	const int selection_size = 100;
	const int N = (int)ingredients.size();
	if (N == 0)
		return result;

	// DFS that sets last ingredient deterministically and accumulates property sums
	std::function<void(int, int, int, int, int, int, int)> dfs =
		[&](int idx, int rem,
			int cap_sum, int dur_sum, int fla_sum, int tex_sum, int cal_sum)
	{
		if (idx == N - 1)
		{
			int a = rem;
			cap_sum += ingredients[idx].capacity * a;
			dur_sum += ingredients[idx].durability * a;
			fla_sum += ingredients[idx].flavour * a;
			tex_sum += ingredients[idx].texture * a;
			cal_sum += ingredients[idx].calories * a;

			int c0 = std::max(cap_sum, 0);
			int c1 = std::max(dur_sum, 0);
			int c2 = std::max(fla_sum, 0);
			int c3 = std::max(tex_sum, 0);
			int score = c0 * c1 * c2 * c3;

			if (score > result.first)
				result.first = score;
			if (cal_sum == 500 && score > result.second)
				result.second = score;
			return;
		}

		for (int v = 0; v <= rem; ++v)
		{
			dfs(idx + 1, rem - v,
				cap_sum + ingredients[idx].capacity * v,
				dur_sum + ingredients[idx].durability * v,
				fla_sum + ingredients[idx].flavour * v,
				tex_sum + ingredients[idx].texture * v,
				cal_sum + ingredients[idx].calories * v);
		}
	};

	dfs(0, selection_size, 0, 0, 0, 0, 0);
	return result;
}
