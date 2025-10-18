
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d16.h"

d16::d16()
{
	input_file = read_entire_file("../../../../2015/input/d16.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(103, 405)));
}

bool d16::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d16::ans_t, d16::ans_t> d16::solution(const std::string_view &sv)
{
	aunts.clear();
	std::pair<ans_t, ans_t> result;
	std::unordered_map<std::string_view, int> struct_offsets = {
		{"children", 0},
		{"cats", 1},
		{"samoyeds", 2},
		{"pomeranians", 3},
		{"akitas", 4},
		{"vizslas", 5},
		{"goldfish", 6},
		{"trees", 7},
		{"cars", 8},
		{"perfumes", 9},
		//
	};
	// PART 0 + 1.
	for (auto &line : string_view_split(sv))
	{
		// SUE, NR, [name, nr]*
		auto parts = string_view_split(line, ' ', true);
		aunts.emplace_back(aunt_sue_t{});
		aunt_sue_t &active_aunt = aunts[aunts.size() - 1];
		for (int i = 2; i < parts.size(); i += 2)
		{
			int value = string_view_to_int(parts[i + 1]);
			parts[i].remove_suffix(1);
			*(((int *)&active_aunt) + struct_offsets[parts[i]]) =
				value;
		}

		// shared:
		if ((active_aunt.children == -1 || active_aunt.children == 3) &&
			(active_aunt.samoyeds == -1 || active_aunt.samoyeds == 2) &&
			(active_aunt.akitas == -1 || active_aunt.akitas == 0) &&
			(active_aunt.vizslas == -1 || active_aunt.vizslas == 0) &&
			(active_aunt.cars == -1 || active_aunt.cars == 2) &&
			(active_aunt.perfumes == -1 || active_aunt.perfumes == 1))
		{
			if ((active_aunt.goldfish == -1 || active_aunt.goldfish == 5) &&
				(active_aunt.pomeranians == -1 || active_aunt.pomeranians == 3) &&
				(active_aunt.trees == -1 || active_aunt.trees == 3) &&
				(active_aunt.cats == -1 || active_aunt.cats == 7))
			{
				result.first = (int)aunts.size();
			}
			else if ((active_aunt.goldfish == -1 || active_aunt.goldfish < 5) &&
					 (active_aunt.pomeranians == -1 || active_aunt.pomeranians < 3) &&
					 (active_aunt.trees == -1 || active_aunt.trees > 3) &&
					 (active_aunt.cats == -1 || active_aunt.cats > 7))
			{
				result.second = (int)aunts.size();
			}
		}
	}
	return result;
}
