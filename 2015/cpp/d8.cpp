/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "utils.h"

struct filter_output
{
	int readCharacters;
	int validCharacters;
	int extraCharacters;
	// int totalCharacters;
};

filter_output d8_filter(const char *in)
{
	filter_output result = {0};
	filter_output dbg = {0};
	result.extraCharacters = 4;
	int dbgIdx = 0;
	while (*in != '\0')
	{
		// NOTE: Handle escaped characters!
		if (*in == '\\')
		{
			if (is_hexadecimal(in))
			{
				result.extraCharacters++;
				in += 4;
				result.readCharacters += 4;
				result.validCharacters++;
				continue;
			}
			else if (*in == '\"' || *in == '\\')
			{
				result.extraCharacters += 2;
				result.readCharacters += 2;
				in += 2;
				result.validCharacters++;
				continue;
			}
			else
			{
				assert(false && "Unhandled token.");
			}
		}
		else if (*in == '\"')
		{
			in++;
			result.readCharacters++;
			continue;
		}
		else if (*in == '\n')
		{
			result.extraCharacters += 4;
			in++;
#if _DBG
			int _1 = result.readCharacters - dbg.readCharacters;
			int _2 = result.validCharacters - dbg.validCharacters;
			std::cout << "Dbg: " << _1 << ", " << _2 << std::endl;
			if (_countof(dbgCheck) > dbgIdx)
			{
				assert(dbgCheck[dbgIdx].first == _1);
				assert(dbgCheck[dbgIdx].second == _2);
			}
			else
			{
				assert(false && "MOAR!");
			}
			dbg = result;
			dbgIdx++;
#endif
			continue;
		}
		result.validCharacters++;
		in++;
		result.readCharacters++;
	}

	return result;
}

void d8()
{
	file_contents in = read_entire_file("../../2015/d8_input.in");
	file_contents test = read_entire_file("../../2015/d8_input_test.in");
	if (in.mem && test.mem)
	{
		auto filter = d8_filter(test.mem);
		assert(filter.validCharacters == 11);
		assert(filter.readCharacters - filter.validCharacters == 12);
		assert(filter.extraCharacters == 19);
		filter = d8_filter(in.mem);
		// filter.readCharacters = (int)length;
		std::cout << "Ans: " << filter.readCharacters - filter.validCharacters << std::endl;
		std::cout << "Ans p2: " << filter.extraCharacters << std::endl;
	}
	else
	{
		std::cout << "Unable to open file." << std::endl;
	}
}