/*========================================================================
	Creator: Grimleik $

	NOTE: The memory benchmarking is not very precise, but gives a hint
	of the memory usage.
========================================================================*/
#include "aoc.h"
#include <float.h>
#include "d1.h"
// #include "d2.h"
// #include "d3.h"
// #include "d4.h"
// #include "d5.h"
// #include "d6.h"
// #include "d7.h"
// #include "d8.h"
// #include "d9.h"
// #include "d10.h"
// #include "d11.h"
// #include "d12.h"

// clang-format off
static std::unique_ptr<aoc_day> factory(int i) {
	switch (i)
	{
		case 1: return std::make_unique<d1>();
		// case 2: return std::make_unique<d2>();
		// case 3: return std::make_unique<d3>();
		// case 4: return std::make_unique<d4>();
		// case 5: return std::make_unique<d5>();
		// case 6: return std::make_unique<d6>();
		// case 7: return std::make_unique<d7>();
		// case 8: return std::make_unique<d8>();
		// case 9: return std::make_unique<d9>();
		// case 10: return std::make_unique<d10>();
		// case 11: return std::make_unique<d11>();
		// case 12: return std::make_unique<d12>();
		default: assert(false && "Day not implemented.");
	}
	return nullptr;
}
// clang-format on

aoc::aoc(std::initializer_list<int> day_list)
{
	for (auto d : day_list)
	{
		days.emplace_back(factory(d));
	}
}

// TODO: Better platform separation.

size_t getCurrentRSS();

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>

size_t getCurrentRSS()
{
	PROCESS_MEMORY_COUNTERS info;
	GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
	return (size_t)info.WorkingSetSize; // in bytes
}
#else
#include <unistd.h>
#include <cstdio>
size_t getCurrentRSS()
{
	long res_page = 0;
	FILE *f = std::fopen("/proc/self/statm", "r");
	if (f)
	{
		long size;
		if (std::fscanf(f, "%ld %ld", &size, &res_page) != 2)
		{
			res_page = 0;
		}
		std::fclose(f);
	}
	long page_size = sysconf(_SC_PAGESIZE);
	if (page_size < 0)
		page_size = 4096;
	return (size_t)res_page * (size_t)page_size;
}
#endif

bool aoc::check()
{
	double all_durations = 0.0;
	for (auto &day : days)
	{
#ifdef VERBOSE
		std::cout << "Day " << day->day() << std::endl;
#endif
		auto start = std::chrono::high_resolution_clock::now();
		if (!day->run())
		{
			std::cout << std::format("Failed day {}. Abort.", day->day()) << std::endl;
			return false;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration<double>(end - start).count();
		all_durations += duration;
	}
	std::cout << std::format("All tests passed! Duration: {}.", all_durations) << std::endl;
	return true;
}

void aoc::benchmark(int iterations)
{
	double all_durations = 0.0;
	std::cout << std::format("Benchmarking {}: days:{}\n", 2015, days.size());
	for (auto &day : days)
	{
		size_t mem_before = getCurrentRSS();
		day->pre_benchmark();
		day->run(); // discard first run...
		double total_duration = 0.0, max_duration = 0.0, min_duration = FLT_MAX;
		for (int i = 0; i < iterations; ++i)
		{
			auto start = std::chrono::steady_clock::now();
			day->run();
			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration<double>(end - start).count();
			max_duration = std::max(duration, max_duration);
			min_duration = std::min(duration, min_duration);
			total_duration += duration;
		}

		total_duration /= iterations;
		day->post_benchmark();

		size_t mem_after = getCurrentRSS();

		std::cout << std::format("\tDay {} Avg {}, Min {}, Max{}, Memory Used {} KB.\n",
								 day->day(), total_duration, min_duration, max_duration, (mem_after - mem_before) / 1024);
		all_durations += total_duration;
	}
	std::cout << std::format("Benchmarking {} done in time: {}\n", 2015, all_durations);
}