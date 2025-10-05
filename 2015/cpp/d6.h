#if !defined(D6_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D6_H
#include "utils.h"
#include "aoc_day.h"

class d6 : public aoc_day
{
public:
	bool run() override;

	constexpr int day() override { return 6; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
};

#endif
