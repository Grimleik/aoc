/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d20.h"

d20::d20()
{
	input_file = read_entire_file("../../../../2015/input/d20.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(786240, 831600)));
}

bool d20::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d20::ans_t, d20::ans_t> d20::solution(const std::string_view &sv)
{
	constexpr int P1_PRESENT_COUNT = {10};
	constexpr int P2_PRESENT_COUNT = {11};
	constexpr int P2_MAX_HOUSES = {50};
	std::pair<ans_t, ans_t> result = {INT_MAX, INT_MAX};
	int target = string_view_to_int(sv);
	int house_number = 1;
	struct shared_data_t
	{
		int target;
		int *res1;
		int *res2;
		std::atomic<int> hn;
		std::mutex lock;
	} shared_data;
	shared_data.res1 = &result.first;
	shared_data.res2 = &result.second;
	shared_data.target = target;
	shared_data.hn = house_number;

	parallelize_function(std::thread::hardware_concurrency(), [](size_t thd_id, shared_data_t *sd)
						 {
	while (true)
	{
		int search1 = 0, search2=0;
		auto hn = sd->hn.fetch_add(1);
#if VERBOSE
		if ((hn % 1000) == 0)
			std::cout << std::format("{}: {} / {}.", thd_id, hn, sd->target) << std::endl;
#endif
		{
			std::lock_guard<std::mutex>lock (sd->lock);
			if(*sd->res1 != INT_MAX && *sd->res2 != INT_MAX)
				break;
		}

		for (int i = (int)std::floor(std::sqrt(hn)); i > 0; --i)
		{
			if ((hn % i) == 0)
			{
				search1 += i;
				if ((hn / i) <= P2_MAX_HOUSES)
					search2 += i;
				int j = hn / i;
				if(j != i) {
					search1 += j;

					if((hn / j) <= P2_MAX_HOUSES)
					search2 += j;
				}
			}

		}
		if (P1_PRESENT_COUNT * search1 >= sd->target) {

			std::lock_guard<std::mutex> lock(sd->lock);
			*sd->res1 = std::min(*sd->res1, hn);
		}

		if (P2_PRESENT_COUNT * search2 >= sd->target) {

			std::lock_guard<std::mutex> lock(sd->lock);
			*sd->res2 = std::min(*sd->res2, hn);
		}
	} }, &shared_data);
	return result;
}
