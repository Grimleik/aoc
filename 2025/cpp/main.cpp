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
	aoc y2025({
		1,
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
		//
	});

#ifdef BENCHMARK
	y2025.benchmark(100);
#else
	y2025.check();
#endif

	return 0;
}
