#if !defined(D7_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D7_H
#include "utils.h"
#include "aoc_day.h"

class d7 : public aoc_day
{
public:
	d7();
	bool run() override;

	constexpr int day() override { return 7; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	struct input_t
	{
		std::string_view sv;
		const char *reg_output;
		const char *reg_override;
	};

	std::unique_ptr<file_contents> input_file;
	std::pair<int, int> solution(const std::string_view &sv,
								 const char *reg_name, const char *override_name);
	std::vector<std::pair<input_t, std::pair<int, int>>> input = {
		// std::make_pair(input{"123 -> xy\n"
		// 					 "456 -> yx\n"
		// 					 "xy AND yx -> d\n"
		// 					 "xy OR yx -> e\n"
		// 					 "xy LSHIFT 2 -> fa\n"
		// 					 "yx RSHIFT 2 -> g\n"
		// 					 "NOT xy -> h\n"
		// 					 "NOT yx -> i\n",
		// 					 "fa", "xy"},
		// 			   std::make_pair(492, 1968))

	};
};
#endif