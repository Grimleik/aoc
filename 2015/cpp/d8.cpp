/*========================================================================
		Creator: Grimleik $
========================================================================*/
#include "utils.h"
#include <limits.h>
#include "d8.h"

d8::d8()
{
	input_file = read_entire_file("../../../../2015/input/d8.in");
	input.emplace_back(std::string_view(input_file->mem, input_file->sz), std::make_pair(1350, 2085));
}

bool d8::run()
{
	for (auto &i : input)
	{
		auto ans = solution(i.first);
		CHECK_VALUE(ans.first, i.second.first);
		CHECK_VALUE(ans.second, i.second.second);
	}
	return true;
}

std::pair<int, int> d8::solution(const std::string_view &sv)
{
	int read_chars = 0;
	int valid_chars = 0;
	int encoding_chars = 0;
	for (size_t i = 0; i < sv.size(); ++i)
	{
		const char *in = &sv[i];
		if (*in == '\\')
		{
			if (is_hexadecimal(in))
			{
				encoding_chars += 1;
				read_chars += 4;
				valid_chars++;
				i += 3;
				continue;
			}
			else
			{
				encoding_chars += 2;
				read_chars += 2;
				valid_chars++;
				++i;
				continue;
			}
		}
		else if (*in == '\"')
		{
			read_chars++;
			encoding_chars += 2;
			continue;
		}
		else if (*in == '\n')
		{
			// encoding_chars += 4;
			continue;
		}
		valid_chars++;
		read_chars++;
	}
	return {read_chars - valid_chars, encoding_chars};
}
