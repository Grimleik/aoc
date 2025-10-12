#if !defined(D6_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D6_H
#include "utils.h"
#include "aoc_day.h"

#define DUMP_PIXELS

enum d6_instruction_type
{
	TURN_ON,
	TURN_OFF,
	TOGGLE,
};

struct d6_instruction
{
	d6_instruction_type type;
	int x0, y0, x1, y1;
};

class d6 : public aoc_day
{
public:
	d6();
	bool run() override;

	constexpr int day() override { return 6; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::unique_ptr<file_contents> input_file;

	void parse(const std::string_view &input, std::vector<d6_instruction> &out);
	int solution(const std::string_view &sv, const std::function<int(const std::vector<d6_instruction> &)> &func);
	// int solution(const std::string_view &input);
	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		// std::make_pair("turn on 0,0 through 999,999", std::make_pair(1'000'000, 0)),
		// std::make_pair("toggle 0,0 through 999,0", std::make_pair(1'000, 0)),
		// std::make_pair("turn off 499,499 through 500,500", std::make_pair(0, 0))
		//
	};
};
#endif
