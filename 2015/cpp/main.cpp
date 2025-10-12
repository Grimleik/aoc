#include "aoc.h"
#include <windows.h>
#include <psapi.h>

// #define MEMORY_BENCHMARK

size_t getCurrentRSS()
{
	PROCESS_MEMORY_COUNTERS info;
	GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
	return (size_t)info.WorkingSetSize; // in bytes
}

int main(int argc, char **argv)
{
	// Memory benchmark, best to only use one day at a time
#ifdef MEMORY_BENCHMARK
	size_t mem_before = getCurrentRSS();
#endif
	aoc y2015({
		// 1,
		// 2,
		// 3,
		// 4,
		// 5,
		// 6,
		// 7,
		8,
		// 9,
		// 10,
		// 11,
		12,
		//
	});
	y2015.check();
#ifdef MEMORY_BENCHMARK
	size_t mem_after = getCurrentRSS();
	std::cout << "Memory used " << (mem_after - mem_before) / 1024 << " KB" << std::endl;
#endif
	// y2015.benchmark(100);

	return 0;
}
