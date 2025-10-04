#if !defined(D4_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define D4_H

#include "utils.h"
#include "aoc_day.h"

class d4 : public aoc_day
{
public:
	bool run() override;

	constexpr int day() override { return 4; }

protected:
	void pre_benchmark() override {}
	void post_benchmark() override {}

private:
};

#endif
