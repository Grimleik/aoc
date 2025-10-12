#if !defined(D9_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D9_H
#include "utils.h"
#include "aoc_day.h"

class d9 : public aoc_day
{
public:
	d9();
	bool run() override;

	constexpr int day() override { return 9; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	void parse_map(const std::string_view &sv);
	std::pair<int, int> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		//
	};
	int map[8][8];
};
#endif
