#if !defined(D22_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D22_H

#include "utils.h"
#include "aoc_day.h"

class d22 : public aoc_day
{
public:
	using ans_t = int;
	d22();
	bool run() override;

	constexpr int day() override { return 22; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};

#endif
