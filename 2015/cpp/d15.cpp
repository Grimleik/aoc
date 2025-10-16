/*========================================================================
	Creator: Grimleik $

	STUDY: Revisit this for a threaded approach, this is pure bruteforce
	for a 0.05s timer, can def. be improved and threaded.
=======================================================================*/

#include "d15.h"
d15::d15()
{
	input_file = read_entire_file("../../../../2015/input/d15.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(13882464, 11171160)));

	// input_file = read_entire_file("../../../../2015/input/d15_test.in");
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
	std::pair<ans_t, ans_t> result;

	// parse input:
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
			//
		});
	}
	// p1
	int selection_size = 100;
	for (int i = 1; i < selection_size; ++i)
	{
		for (int j = 1; j < selection_size; ++j)
		{
			for (int k = 1; k < selection_size; ++k)
			{
				for (int l = 1; l < selection_size; ++l)
				{
					if ((l + k + j + i) != selection_size)
						continue;

					int score =
						std::max(ingredients[0].capacity * i + ingredients[1].capacity * j + ingredients[2].capacity * k + ingredients[3].capacity * l, 0) *
						std::max(ingredients[0].durability * i + ingredients[1].durability * j + ingredients[2].durability * k + ingredients[3].durability * l, 0) *
						std::max(ingredients[0].flavour * i + ingredients[1].flavour * j + ingredients[2].flavour * k + ingredients[3].flavour * l, 0) *
						std::max(ingredients[0].texture * i + ingredients[1].texture * j + ingredients[2].texture * k + ingredients[3].texture * l, 0);
					if (score > result.first)
						result.first = score;
					int calories = ingredients[0].calories * i + ingredients[1].calories * j + ingredients[2].calories * k + ingredients[3].calories * l;
					if (calories != 500)
						continue;

					if (score > result.second)
						result.second = score;
				}
			}
		}
	}
	return result;
}
