#include "utils.h"
#include "aoc_day.h"

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
	using ans_t = size_t;

	void apply_op(const std::string_view &sv, d6::ans_t &s1, d6::ans_t &s2,
				  const int active_w, const int col, const int width, const int height,
				  std::function<void(d6::ans_t &, d6::ans_t &)> op);
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};