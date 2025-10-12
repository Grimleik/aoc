#if !defined(D5_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D5_H

#include "utils.h"
#include "aoc_day.h"

class d5 : public aoc_day
{
public:
	d5();
	bool run() override;

	constexpr int day() override { return 5; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::unique_ptr<file_contents> input_file;
	std::vector<std::string_view> input = {};
};

#endif