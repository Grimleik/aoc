#if !defined(D14_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D14_H
#include "utils.h"
#include "aoc_day.h"

class d14 : public aoc_day
{
public:
	d14();
	bool run() override;

	constexpr int day() override { return 14; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	struct reindeer_t
	{
		int speed;
		int move_duration;
		int rest_duration;
		int lapse_duration;
		int score;
	};
	using ans_t = int;
	std::vector<reindeer_t> reindeers;
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};
#endif
