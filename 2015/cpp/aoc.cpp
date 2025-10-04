/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "aoc.h"
#include "d1.h"
#include "d2.h"
#include "d3.h"
#include "d4.h"
#include "d5.h"

// clang-format off
static std::unique_ptr<aoc_day> factory(int i) {
	switch (i)
	{
		case 1: return std::make_unique<d1>();
		case 2: return std::make_unique<d2>();
		case 3: return std::make_unique<d3>();
		case 4: return std::make_unique<d4>();
		case 5: return std::make_unique<d5>();
		default: assert(false && "Day not implemented.");
	}
	return nullptr;
}
// clang-format on

aoc::aoc(std::initializer_list<int> day_list)
{
	for (int day : day_list)
	{
		days.push_back(factory(day));
	}
}

bool aoc::check()
{
	auto start = std::chrono::high_resolution_clock::now();
	for (auto &d : days)
	{
#ifdef VERBOSE
		std::cout << "Day " << d->day() << std::endl;
#endif
		if (!d->run())
		{
			std::cout << std::format("Failed day {}. Abort.", d->day()) << std::endl;
			return false;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double>(end - start).count();
	std::cout << std::format("All tests passed! Duration: {}.", duration) << std::endl;
	return true;
}

void aoc::benchmark(int iterations)
{
	double all_durations = 0.0;
	for (auto &d : days)
	{
		d->pre_benchmark();

		double total_duration = 0.0, max = 0.0, min = FLT_MAX;
		for (int i = 0; i < iterations; ++i)
		{
			auto start = std::chrono::high_resolution_clock::now();
			d->run();
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration<double>(end - start).count();
			max = std::max(duration, max);
			min = std::min(duration, min);
			total_duration += duration;
		}

		total_duration /= iterations;
		d->post_benchmark();
		std::cout << std::format("Day {} Avg {}, Min {}, Max{}.", d->day(), total_duration, min, max);
		all_durations += total_duration;
	}
}