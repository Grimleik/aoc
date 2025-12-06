/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d6.h"
#include "utils.h"

// #define VERBOSE

d6::d6()
{
	// input_file = read_entire_file("d6_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(4277556, 0)));
	input_file = read_entire_file("d6.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(0, 0)));
}
bool d6::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct celaphod_number_t
{
	std::string_view sv;
	int pad;
};

std::pair<d6::ans_t, d6::ans_t> d6::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	size_t idx = 0;
	std::vector<std::string_view> splits;
	splits.reserve(256);
	while (idx < sv.size())
	{
		celaphod_number_t v;
		v.pad = 0;
		while (is_whitespace(sv[idx]))
		{
			v.pad++;
			++idx;
		}
		size_t begin = idx;
		while (!is_whitespace(sv[idx]))
			++idx;
		size_t end = idx;
		v.sv = sv.substr(begin, end - begin));
		splits.emplace_back(v);
	}
	splits.resize(splits.size() - 1); // drop last.
	size_t ridx = splits.size() - 1;
	while (!is_numeric(splits[ridx][0]))
		--ridx;
	size_t w = splits.size() - ridx - 1;
	double h = (splits.size() - w) / (double)w;
	assert(h == (size_t)(h));
	std::vector<int> numbers;
	numbers.reserve(splits.size() - w);
	for (int i = 0; i < splits.size() - w; ++i)
		numbers.emplace_back(string_view_to_int(splits[i]));

	for (size_t op = 0; op < w; ++op)
	{
		switch (splits[splits.size() - w + op][0])
		{
		case '+':
		{
			size_t part = 0;
			for (size_t i = 0; i < h; ++i)
			{
				part += numbers[op + i * w];
			}
			assert((result.first + part) > result.first);
			result.first += part;
		}
		break;

		case '*':
		{
			size_t part = 1;
			for (size_t i = 0; i < h; ++i)
			{
				part *= numbers[op + i * w];
			}
			assert((result.first + part) > result.first);
			result.first += part;
		}
		break;
		default:
			assert(false && "Not yet implemented.");
			break;
		}
	}
	return result;
}