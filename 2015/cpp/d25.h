#if !defined(D25_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D25_H
#include "utils.h"
#include "aoc_day.h"

class d25 : public aoc_day
{
public:
	d25();
	bool run() override;

	constexpr int day() override { return 25; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	using ans_t = uint64_t;
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};
#endif
