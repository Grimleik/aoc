#if !defined(D2_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D2_H
#include "utils.h"
#include "aoc_day.h"

class d2 : public aoc_day
{
public:
	d2();
	bool run() override;

	constexpr int day() override { return 2; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		// std::make_pair("2x3x4", std::make_pair(58, 34)),
		// std::make_pair("1x1x10", std::make_pair(43, 14)),
	};
};

#endif
