#if !defined(D1_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D1_H
#include "utils.h"
#include "aoc_day.h"

class d1 : public aoc_day
{
public:
	d1();
	bool run() override;

	constexpr int day() override { return 1; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		// std::make_pair("()()()", std::make_pair(0, -1)),
		// std::make_pair("(((", std::make_pair(3, -1)),
		//
	};
};

#endif
