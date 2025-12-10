#include "utils.h"
#include "aoc_day.h"

class d8 : public aoc_day
{
public:
	d8();
	bool run() override;

	constexpr int day() override { return 8; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	using ans_t = unsigned long long;
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};