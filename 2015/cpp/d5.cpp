
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d5.h"

bool is_vowel(const char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool d5_strings(const std::string_view &sv)
{
	int vowels = 0;
	int twiceInARow = 0;
	const char *filterOut[] = {"ab", "cd", "pq", "xy"};
	int i = 0;
	for (; i < sv.size() - 1; ++i)
	{
		for (int j = 0; j < (int)ARRAY_COUNT(filterOut); ++j)
		{
			if (filterOut[j][0] == sv[i] && filterOut[j][1] == sv[i + 1])
				return false;
		}
		if (is_vowel(sv[i]))
		{
			++vowels;
		}
		if (sv[i] == sv[i + 1])
		{
			++twiceInARow;
		}
	}
	if (is_vowel(sv[i]))
		++vowels;
	return vowels >= 3 && twiceInARow >= 1;
}

bool d5_strings_p2(const std::string_view &sv)
{
	int rule1 = 0;
	int rule2 = 0;
	char poc = '\0';
	// std::map<char, std::set<char>> ngrams;
	std::unordered_map<char, u32> ngrams;
	for (int i = 0; i < sv.size() - 1; ++i)
	{
		// Ngram of c0 is only valid if it doesnt overlap.
		if (sv[i] == sv[i + 1] && sv[i] == poc)
		{
			poc = '\0';
		}
		// else if (ngrams[sv[i]].find(sv[i + 1]) != ngrams[sv[i]].end())
		else if (ngrams[sv[i]] & (1 << ((sv[i + 1]) - 'a')))
		{
			++rule1;
		}
		else
		{
			ngrams[sv[i]] |= (1 << (sv[i + 1] - 'a'));
			poc = sv[i];
		}
		// Rule 2:
		if (i > 0 && sv[i - 1] == sv[i + 1])
		{
			++rule2;
		}
	}
	return rule1 >= 1 && rule2 >= 1;
}

bool d5::run()
{
	for (auto &el : input_test_p1)
		CHECK_TEST(d5_strings, el.first, el.second);

	for (auto &el : input_test_p2)
		CHECK_TEST(d5_strings_p2, el.first, el.second);

	int result[2] = {0, 0}, ans[2] = {238, 69};
	for (int i = 0; i < input.size(); ++i)
	{
		if (d5_strings(input[i]))
		{
			++result[0];
		}

		if (d5_strings_p2(input[i]))
		{
			++result[1];
		}
	}
	CHECK_VALUE(result[0], ans[0]);
	CHECK_VALUE(result[1], ans[1]);
	return true;
}