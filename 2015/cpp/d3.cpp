/*========================================================================
	Creator: Grimleik $

	STUDY: unordered hash is costant whilst the original ordered map was
	log n because the underlying structure of the map is a rb binary
	tree whilst the hash produces a 'unique' key. An improvement but
	also limitation was constructing a key with bit shifting.
========================================================================*/
#include "d3.h"

int d3::house_delivery(const std::string_view path)
{
	int actorId = 0;
	std::vector<std::pair<i32, i32>> actorLocations(nrActors);
	std::unordered_map<u64, i32> visit;
	visit[0] = 1;

	for (auto &c : path)
	{
		i32 &x = actorLocations[actorId].first;
		i32 &y = actorLocations[actorId].second;

		if (c == '^')
		{
			++y;
		}
		else if (c == '>')
		{
			++x;
		}
		else if (c == 'v')
		{
			--y;
		}
		else if (c == '<')
		{
			--x;
		}
		else
		{
			std::cout << "Failure reading path instruction: " << c << std::endl;
			continue;
		}

		u64 key = static_cast<u64>(x) << 32;
		key |= static_cast<u32>(y);
		visit[key] = 1;
		actorId = (actorId + 1) % (nrActors);
	}
	return (int)(visit.size());
}

d3::d3()
{
	input_file = std::move(read_entire_file("../../../../2015/input/d3.in"));
	input.emplace_back(std::string_view(input_file->mem, input_file->sz), std::make_pair(2592, 2360));
}

bool d3::run()
{
	nrActors = 1;
	for (auto &t : input)
		CHECK_TEST(house_delivery, t.first, t.second.first);

	nrActors = 2;
	for (auto &t : input)
		CHECK_TEST(house_delivery, t.first, t.second.second);

	return true;
}

void d3::pre_benchmark()
{
	constexpr int rand_size = 1'000'000;
	benchmark_string.reserve(rand_size);
	for (int i = 0; i < rand_size; ++i)
	{
		switch (rand() % 4)
		{
		case 0:
		{
			benchmark_string += "^";
		}
		break;

		case 1:
		{
			benchmark_string += ">";
		}
		break;

		case 2:
		{
			benchmark_string += "v";
		}
		break;

		case 3:
		{
			benchmark_string += "<";
		}
		break;
		default:
			break;
		}
	}
	// 100'000
	// d3_data.push_back(std::make_pair(std::string_view(benchmark_string), std::make_pair(23829, 26353)));
	// 1'000'000
	input.push_back(std::make_pair(std::string_view(benchmark_string), std::make_pair(59908, 60007)));
}

void d3::post_benchmark()
{
	benchmark_string.clear();
	input.pop_back();
}
