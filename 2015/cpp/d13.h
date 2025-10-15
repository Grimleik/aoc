#if !defined(D13_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D13_H
#include "utils.h"
#include "aoc_day.h"

// #define VERBOSE

class d13 : public aoc_day
{
public:
	d13();
	bool run() override;

	constexpr int day() override { return 13; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	using ans_t = int;
	void parse_graph(const std::string_view &sv);
#ifdef VERBOSE
	std::map<int, std::string> dbgLUT;
	void print_seating_arrangment(const std::vector<int> seating_arrangement, const int seating_cost, const int part);
#endif
	std::vector<std::vector<int>> graph;
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};
#endif
