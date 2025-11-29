/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d25.h"

d25::d25()
{
	input_file = read_entire_file("d25.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(8997277, 0)));
}

bool d25::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d25::ans_t, d25::ans_t> d25::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;
	int w, h;
	auto splits = string_view_split(sv);
	w = string_view_to_int(splits[0]);
	h = string_view_to_int(splits[1]);
	uint64_t n = (w - 1) + h;
	uint64_t m = n - w;
	if (h > w)
	{
		m = n - h;
	}

	n = ((n * n + n) / 2) - m;
	// Linear

	// result.first = 20151125;
	// for (auto i = 1; i < n; ++i)
	// {
	// 	result.first *= 252533;
	// 	result.first %= 33554393;
	// }

	// Mod. Exponent.

	// Instead of linearly applying our formula we can evaluate the
	// exponent of the base, since the base is being applied n times
	// linearly, but by doing it through exponent we get O(log N)
	// instead of O(N).

	uint64_t exponent = n - 1;
	uint64_t base = 252533;
	uint64_t mod = 33554393;
	uint64_t r = 1;
	base = base % mod;
	while (exponent > 0)
	{
		// odd ?
		if (exponent & 1)
		{
			r = ((__uint128_t)r * base) % mod;
		}
		base = ((__uint128_t)base * base) % mod;
		exponent >>= 1;
	}
	result.first = (__uint128_t)20151125 * r % mod;
	return result;
}
