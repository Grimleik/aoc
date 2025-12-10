/*========================================================================
	Creator: Grimleik $
========================================================================*/

// #define VERBOSE
// #define _TIME

#include "d8.h"
#include "utils.h"

d8::d8()
{
	// input_file = read_entire_file("d8_test.in");
	// input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(40, 0)));
	input_file = read_entire_file("d8.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(52668, 1474050600)));
}

bool d8::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct junction_box_t
{
	unsigned long long x, y, z;
	std::string to_string()
	{
		return std::format("{}, {}, {}", x, y, z);
	}
	unsigned long long id()
	{
		assert(z < (1 << 17));
		return x << 36 | y << 18 | z;
	}
};

struct link_t
{
	double dist;
	junction_box_t *s, *d;
};

#define SQUARE(x) ((x) * (x))

double distance(const junction_box_t &b1, const junction_box_t &b2)
{
	auto a = SQUARE(b1.x - b2.x);
	auto b = SQUARE(b1.y - b2.y);
	auto c = SQUARE(b1.z - b2.z);
	// double result = sqrt(a + b + c); Micro optimization.
	double result = (a + b + c);
	return result;
}

std::pair<d8::ans_t, d8::ans_t> d8::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {0, 0};
	auto parse = string_view_split(sv);
	std::vector<junction_box_t> nodes;
	std::vector<link_t> links;
	// nodes.reserve(parse.size());
	// links.reserve(parse.size());
	std::unordered_map<ans_t, ans_t> circuit_map; // idx -> circuit
	// circuit_map.reserve(parse.size());
	std::map<ans_t, std::vector<ans_t>> circuit_nodes; // circuit_nbr -> nodes.
	// TODO: Test using sstream and point to input file as cin.
	TIME_BLOCK_NAMED("parse", {
		for (auto &p : parse)
		{
			auto splits = string_view_split(p, ',', true, true);
			assert(splits.size() == 3);
			nodes.emplace_back(junction_box_t{(unsigned long long)string_view_to_int(splits[0]), (unsigned long long)string_view_to_int(splits[1]), (unsigned long long)string_view_to_int(splits[2])});
			// circuit_nodes[nodes.back().id()].reserve(1000);
		}
	});
	TIME_BLOCK_NAMED("link creation", {
	for (int i = 0; i < nodes.size(); ++i)
	{
		for (int j = i + 1; j < nodes.size(); ++j)
		{
			links.emplace_back(link_t{distance(nodes[i], nodes[j]), &nodes[i], &nodes[j]});
		}
	} });

	TIME_BLOCK_NAMED("link sorting", {
		std::sort(links.begin(), links.end(), [](const link_t &l1, const link_t &l2)
				  { return l1.dist < l2.dist; });
	});
	int next_circuit = 0, iteration_count = links.size(), p1_search_criterium = 1000 - 1;
	TIME_BLOCK_NAMED("searching", {
		for (int i = 0; i < iteration_count; ++i)
		{
			if (circuit_map.contains(links[i].s->id()))
			{
				if (circuit_map.contains(links[i].d->id()))
				{
					auto map1 = circuit_map[links[i].s->id()];
					auto map2 = circuit_map[links[i].d->id()];
					// Transfer!
					if (map1 != map2)
					{
						for (auto i : circuit_nodes[map2])
						{
							circuit_map[i] = map1;
							circuit_nodes[map1].emplace_back(i);
						}
						circuit_nodes[map2].clear();
					}
				}
				else
				{
					circuit_map[links[i].d->id()] = circuit_map[links[i].s->id()];
					circuit_nodes[circuit_map[links[i].s->id()]].emplace_back(links[i].d->id());
				}
			}
			else if (circuit_map.contains(links[i].d->id()))
			{
				circuit_map[links[i].s->id()] = circuit_map[links[i].d->id()];
				circuit_nodes[circuit_map[links[i].d->id()]].emplace_back(links[i].s->id());
			}
			else
			{
				next_circuit++;
				circuit_map[links[i].s->id()] = next_circuit;
				circuit_map[links[i].d->id()] = next_circuit;
				circuit_nodes[circuit_map[links[i].s->id()]].emplace_back(links[i].s->id());
				circuit_nodes[circuit_map[links[i].d->id()]].emplace_back(links[i].d->id());
			}
			// P1:
			if (i == p1_search_criterium)
			{
				std::vector<int> max_sizes;
				for (auto &[k, v] : circuit_nodes)
				{
					max_sizes.push_back(v.size());
				}
				std::sort(max_sizes.rbegin(), max_sizes.rend());
				result.first = max_sizes[0] * max_sizes[1] * max_sizes[2];
			}
			// P2:
			if (circuit_nodes[circuit_map[links[i].s->id()]].size() == nodes.size() ||
				circuit_nodes[circuit_map[links[i].d->id()]].size() == nodes.size())
			{
				result.second = links[i].s->x * links[i].d->x;
				break;
			}
		}
	});

	return result;
}
