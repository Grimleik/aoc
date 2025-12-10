
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d10.h"
#include "utils.h"

// #define VERBOSE

d10::d10()
{
	input_file = read_entire_file("d10_test.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(0, 0)));
	// input_file = read_entire_file("d10.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(23039913998, 35950619148)));
}
bool d10::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}
struct machine_t
{
	std::vector<bool> lights;
	std::vector<std::vector<int>> buttons;
	std::vector<std::vector<int>> joltages;
};

std::pair<d10::ans_t, d10::ans_t> d10::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	std::vector<machine_t> machines(parse.size());
	int idx = 0;
	for (auto &p : parse)
	{
		auto splits = string_view_split(p, ' ', true, false);
		machine_t &m = machines[idx++];
		for (auto &s : splits)
		{
			if (s[0] == '[')
			{
				for (int i = 1; i < s.size() - 1; ++i)
					m.lights.push_back(s[i] == '#');
			}
			else if (s[0] == '(')
			{
				s.remove_suffix(1);
				s.remove_prefix(1);
				std::vector<int> bts;
				auto is = string_view_split(s, ',', true);
				for (auto &i : is)
				{
					auto v = string_view_to_int(i);
					bts.push_back(v);
				}
				m.buttons.push_back(bts);
			}
			else if (s[0] == '{')
			{
				s.remove_suffix(1);
				s.remove_prefix(1);
				std::vector<int> jlts;
				for (auto &i : string_view_split(s, ',', true))
					jlts.push_back(string_view_to_int(i));
				m.joltages.push_back(jlts);
			}
		}
	}
	return result;
}