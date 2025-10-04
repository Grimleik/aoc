#if !defined(AOC_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define AOC_H
#include <vector>
#include <memory>
#include "aoc_day.h"

class aoc
{
public:
	aoc(std::initializer_list<int> days);

	bool check();
	void benchmark(int iterations = 100);

private:
	std::vector<std::unique_ptr<aoc_day>> days;
};

#endif
