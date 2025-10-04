
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d2.h"

struct box
{
	size_t w, h, l;
};

size_t total_area_rectangular_prism(const box &b)
{
	size_t result;
	size_t x = b.w * b.h;
	size_t y = b.w * b.l;
	size_t z = b.h * b.l;
	result = 2 * (x + y + z) + std::min(std::min(x, y), z);
	return result;
}

size_t total_bow_rectangular_prism(const box &box)
{
	size_t result;
	size_t x, y;
	// NOTE/STUDY: This can be written more concisley with:
	/* AI Suggestion:
	std::array<size_t, 3> dims = {w, h, l};
	std::sort(dims.begin(), dims.end());
	result = 2 * dims[0] + 2 * dims[1] + w * h * l;
	*/
	if (box.w > box.h)
	{
		if (box.w > box.l)
		{
			x = box.h;
			y = box.l;
		}
		else
		{
			x = box.h;
			y = box.w;
		}
	}
	else
	{
		if (box.h > box.l)
		{
			x = box.w;
			y = box.l;
		}
		else
		{
			x = box.w;
			y = box.h;
		}
	}
	result = x + x + y + y;
	result += box.w * box.h * box.l;
	return result;
}

size_t solution(const std::vector<const char *> &input, std::function<size_t(box &)> calc)
{
	box b;
	size_t result = 0;
	for (auto &c : input)
	{
		size_t offset = 0, len;
		b.w = std::stoi(c, &len);
		offset += len + 1;
		b.h = std::stoi(c + offset, &len);
		offset += len + 1;
		b.l = std::stoi(c + offset, &len);
		result += calc(b);
	}
	return result;
}

bool d2::run()
{
	for (auto &el : input)
		CHECK_TEST(solution, el.first, el.second.first, total_area_rectangular_prism);

	for (auto &el : input)
		CHECK_TEST(solution, el.first, el.second.second, total_bow_rectangular_prism);

	return true;
}