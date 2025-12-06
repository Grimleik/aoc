/*========================================================================
	Creator: Grimleik $
	Idea:
		* Take full input, walk backwards until we find number
		* Then walk until we find first * or +. Then we have the
		complete full down bar of +...*..+.....+.. etc, this describes
		the dimensions of the operands, where the sign is the start of the
		column.
		* Then we start at 0 and walk for the 0th operands size.
========================================================================*/
#include "d6.h"
#include "utils.h"

// #define VERBOSE

d6::d6()
{
	// input_file = read_entire_file("d6_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(4277556, 3263827)));
	input_file = read_entire_file("d6.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(5316572080628, 11299263623062)));
}
bool d6::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

void d6::apply_op(const std::string_view &sv, d6::ans_t &s1, d6::ans_t &s2,
				  const int active_w, const int col, const int width, const int height,
				  std::function<void(d6::ans_t &, d6::ans_t &)> op)
{
	size_t p1 = 0;
	for (size_t h = 0; h < height; ++h)
	{
		size_t p1 = 0;
		for (size_t i = 0; i < active_w; ++i)
		{
			char c = sv[col + i + h * width];
			if (is_numeric(c))
				p1 = p1 * 10 + c - '0';
		}
		op(s1, p1);
	}
	for (size_t w = 0; w < active_w; ++w)
	{
		size_t p2 = 0;
		for (size_t i = 0; i < height; ++i)
		{
			char c = sv[col + w + i * width];
			if (is_numeric(c))
				p2 = p2 * 10 + c - '0';
		}
		op(s2, p2);
	}
}

std::pair<d6::ans_t, d6::ans_t> d6::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	size_t ridx = sv.size() - 1;
	// We first find the first backward occurence of a number...
	while (!is_numeric(sv[ridx]))
	{
		--ridx;
	}
	// .. then we find the first occurring * or +..
	while (sv[ridx] != '*' && sv[ridx] != '+')
		ridx++;
	size_t w = sv.size() - ridx;
	double h = (sv.size() - w) / (double)w;
	assert(h == (size_t)(h));
	size_t active_h = 0;
	while (ridx < sv.size())
	{
		char operation = sv[ridx];
		size_t begin = ridx;
		++ridx;
		while (sv[ridx] != '*' && sv[ridx] != '+' && ridx < sv.size())
			++ridx;
		// -1 for the column of pure spaces.
		size_t active_w = ridx - begin - 1;
		size_t s1 = operation == '*' ? 1 : 0;
		size_t s2 = s1;
		switch (operation)
		{
		case '+':
		{
			apply_op(sv, s1, s2,
					 active_w, active_h, w, h,
					 [&](d6::ans_t &sum, d6::ans_t &res)
					 { sum += res; });
		}
		break;

		case '*':
		{
			apply_op(sv, s1, s2,
					 active_w, active_h, w, h,
					 [&](d6::ans_t &sum, d6::ans_t &res)
					 { sum *= res; });
		}
		break;
		default:
			assert(false && "Not yet implemented.");
			break;
		}
#ifdef VERBOSE
		std::cout << "Add to 1: " << s1 << std::endl;
		std::cout << "Add to 2: " << s2 << std::endl;
#endif
		result.first += s1;
		result.second += s2;
		active_h += active_w + 1; // re-add the column
	}
	return result;
}