
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
	using ans_t = size_t;

	struct range_t
	{
		d5::ans_t min, max;
	};
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};