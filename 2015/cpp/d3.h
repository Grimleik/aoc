#if !defined(D3_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D3_H
#include "utils.h"
#include "aoc_day.h"

class d3 : public aoc_day
{
public:
	d3();
	bool run() override;

	constexpr int day() override { return 3; }

protected:
	void pre_benchmark() override;
	void post_benchmark() override;

private:
	std::unique_ptr<file_contents> input_file;
	int house_delivery(const std::string_view path, const int nrActors);
	std::string benchmark_string = "";

	std::vector<std::pair<std::string_view, std::pair<int, int>>> input = {
		// std::make_pair(">", std::make_pair(2, 2)),
		// std::make_pair("^>v<", std::make_pair(4, 3)),
		// std::make_pair("^v^v^v^v^v", std::make_pair(2, 11)),
	};
};

#endif
