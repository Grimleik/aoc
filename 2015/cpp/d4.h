#if !defined(D4_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D4_H

#include "utils.h"
#include "aoc_day.h"

class d4 : public aoc_day
{
public:
	bool run() override;

	constexpr int day() override { return 4; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::vector<std::pair<std::string_view, std::pair<int, int>>> d4_data = {
		std::make_pair("abcdef", std::make_pair(609043, 0)),
		std::make_pair("pqrstuv", std::make_pair(1048970, 0)),
		std::make_pair("iwrupvqb", std::make_pair(346386, 9958218))};
};

#endif
