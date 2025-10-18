#if !defined(D16_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D16_H
#include "utils.h"
#include "aoc_day.h"

class d16 : public aoc_day
{
public:
	d16();
	bool run() override;

	constexpr int day() override { return 16; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
	struct aunt_sue_t
	{
		int children = {-1};
		int cats = {-1};
		int samoyeds = {-1};
		int pomeranians = {-1};
		int akitas = {-1};
		int vizslas = {-1};
		int goldfish = {-1};
		int trees = {-1};
		int cars = {-1};
		int perfumes = {-1};
	};
	using ans_t = int;
	std::pair<ans_t, ans_t> solution(const std::string_view &sv);
	std::vector<aunt_sue_t> aunts;
	std::unique_ptr<file_contents> input_file;
	std::vector<std::pair<std::string_view, std::pair<ans_t, ans_t>>> input = {
		//
	};
};
#endif
