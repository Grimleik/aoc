
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d1.h"

int get_floor(const std::string_view floor)
{
	int result = 0;
	for (auto &c : floor)
	{
		if (c == '(')
			++result;
		else if (c == ')')
			--result;
	}

	return result;
}

int get_basement(const std::string_view floor)
{
	int result = 0, idx = 0, basement = -1;
	for (auto &c : floor)
	{
		if (c == '(')
			++result;
		else if (c == ')')
			--result;
		++idx;
		if (result < 0)
		{
			basement = idx;
			break;
		}
	}
	return basement;
}

bool d1::run()
{
	for (auto &el : input)
		CHECK_TEST(get_floor, el.first, el.second.first);

	for (auto &el : input)
		CHECK_TEST(get_basement, el.first, el.second.second);

	return true;
}
