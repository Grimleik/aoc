
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d9.h"
#include "utils.h"
#include <optional>
#include <cmath>

// #define VERBOSE

d9::d9()
{
	input_file = read_entire_file("d9_test.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(50, 0)));
	// input_file = read_entire_file("d9.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(4776487744, 0)));
}
bool d9::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct point_t
{
	int x, y;
	point_t operator-(point_t &rh)
	{
		return {x - rh.x, y - rh.y};
	}
	std::string to_string()
	{
		return std::format("({}, {})", x, y);
	}
};

struct Vec2
{
	double x, y;

	Vec2 operator+(const Vec2 &v) const { return {x + v.x, y + v.y}; }
	Vec2 operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }
	Vec2 operator*(double s) const { return {x * s, y * s}; }
};

double cross(const Vec2 &a, const Vec2 &b)
{
	return a.x * b.y - a.y * b.x;
}

// Returns intersection point if the ray intersects the line segment AB
std::optional<Vec2> raySegmentIntersection(
	const Vec2 &rayOrigin,
	const Vec2 &rayDir,
	const Vec2 &A,
	const Vec2 &B)
{
	Vec2 v1 = rayOrigin - A;
	Vec2 v2 = B - A;
	double cross_r_v2 = cross(rayDir, v2);

	// If parallel (or almost)
	if (std::abs(cross_r_v2) < 1e-9)
		return std::nullopt;

	double t = cross(v2, v1) / cross_r_v2;	   // distance along the ray
	double u = cross(rayDir, v1) / cross_r_v2; // position on segment [0,1]

	if (t >= 0.0 && u >= 0.0 && u <= 1.0)
	{
		return rayOrigin + rayDir * t;
	}

	return std::nullopt;
}

d9::ans_t area(const point_t &a, const point_t &b)
{
	int64_t x = (abs(a.x - b.x) + 1);
	int64_t y = (abs(a.y - b.y) + 1);
	return x * y;
	// return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);
}

std::pair<d9::ans_t, d9::ans_t> d9::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	std::vector<point_t> points;
	for (auto &p : parse)
	{
		auto split = string_view_split(p, ',', true);
		points.push_back(point_t{(int)string_view_to_int(split[0]), (int)string_view_to_int(split[1])});
	}

	for (int i = 0; i < points.size(); ++i)
	{
		for (int j = 0; j < points.size(); ++j)
		{
			auto area_value = area(points[i], points[j]);
			if (result.first < area_value)
			{
				std::cout << "1: " << points[i].to_string() << " * " << points[j].to_string() << " -> " << area_value << std::endl;
				result.first = area_value;
			}
			// p2: check if extra points are inside:
			Vec2 p2 = {(double)points[i].x, (double)points[j].y};
			Vec2 p3 = {(double)points[j].x, (double)points[i].y};
			static Vec2 dir = {1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0)};

			auto sz = points.size();
			points.push_back(points[0]);
			int cuts1 = 0, cuts2 = 0;

			for (int k = 0; k < sz; ++k)
			{
				auto cut = raySegmentIntersection(p2, dir, Vec2{(double)points[k].x, (double)points[k].y}, Vec2{(double)points[k + 1].x, (double)points[k + 1].y});
				if (cut.has_value())
				{
					++cuts1;
				}
				cut = raySegmentIntersection(p3, dir, Vec2{(double)points[k].x, (double)points[k].y}, Vec2{(double)points[k + 1].x, (double)points[k + 1].y});
				if (cut.has_value())
				{
					++cuts2;
				}
			}
			if ((cuts1 % 2) && (cuts2 % 2))
			{
				if (result.second < area_value)
				{
					std::cout << "2: " << points[i].to_string() << " * " << points[j].to_string() << " -> " << area_value << std::endl;
					result.second = area_value;
				}
			}
			points.resize(sz);
		}
	}

	return result;
}