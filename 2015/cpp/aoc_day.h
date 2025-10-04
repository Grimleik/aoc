#if !defined(AOC_DAY_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define AOC_DAY_H
#include <map>
#include <functional>
#include <assert.h>

class aoc_day
{
public:
	virtual bool run() = 0;

	constexpr virtual int day() = 0;
	virtual void pre_benchmark() = 0;
	virtual void post_benchmark() = 0;

protected:
};

#endif
