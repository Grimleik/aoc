#if !defined(D10_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D10_H
#include "utils.h"
#include "aoc_day.h"

class d10 : public aoc_day
{
public:
	d10();
	bool run() override;

	constexpr int day() override { return 10; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::pair<int, int> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		//
	};
};
#endif
