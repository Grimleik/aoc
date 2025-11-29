#include "aoc.h"
#include "utils.h"

// TODO: Better benchmarking options.
#define BENCHMARK

fs::path gDataPath;
int main(int argc, char **argv)
{
	gDataPath = fs::path(BUILD_DATA_DIR);
	if (!fs::exists(gDataPath))
	{
		std::cout << "Data path not present." << std::endl;
		return -1;
	}
	aoc y2015({
		// 1,
		// 2,
		// 3,
		// 4,
		// 5,
		// 6,
		// 7,
		// 8,
		// 9,
		// 10,
		// 11,
		// 12,
		// 13,
		// 14,
		// 15,
		// 16,
		// 17,
		// 18,
		// 19,
		// 20,
		// 21,
		// 22,
		// 23,
		24
		//
	});

#ifdef BENCHMARK
	y2015.benchmark(100);
#else
	y2015.check();
#endif

	return 0;
}
