/*========================================================================
	Creator: Grimleik $

	STUDY: Be careful when using std::map here are some benchmarking
	results:

	- graph : map.. Day 13 Avg 0.14277678000000002, Min 0.1352052,
	  Max0.1555186

	- graph : unorderd_map Day 13 Avg 0.07430293200000004, Min
	  0.0703493, Max0.0930197.

	- graph : vector<vector.. Day 13 Avg 0.03650478299999999, Min
	  0.0350014, Max0.0406774.

	Also its a good reminder that the way N! works means that the
	sequence will rotate around for our N elements. If we don't want to
	distinguish between 0, 1, 2, .. N and N, 0, 1, ... etc we can fix
	one element, e.g. 0 and reduce the complexity of our solution
	drastically. The speed on my current setup is now: ~0.00065s
========================================================================*/
#include "utils.h"
#include "d13.h"

d13::d13()
{
	input_file = read_entire_file("../../../../2015/input/d13.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(664, 640)));
	// input_file = read_entire_file("../../../../2015/input/d13_test.in");
	// input.emplace_back(std::make_pair(std::string_view(input_file->mem),
	// 								  std::make_pair(330, 286)));
}

bool d13::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

void d13::parse_graph(const std::string_view &sv)
{
	// SRC,_,+/-,NR,_,_,_,_,_,_,DST ->
	std::map<std::string_view, int> name_ids;
	int name_id = 0;

	auto lines = split_string_view(sv, '\n');

	graph.clear();
	// Calculate M = N*N-1. where M is given and N is asked for.
	const double N_D = (1 + std::sqrt(1 + 4 * lines.size())) / 2.0;
	const int N = (int)N_D;
	assert(N == N_D);
	graph.resize(N + 1);
	for (auto &row : graph)
		row.resize(N + 1);
	for (auto &line : lines)
	{
		auto parts = split_string_view(line, ' ', true);
		assert(parts.size() == 11);
		std::string_view src = parts[0], gain = parts[2], value = parts[3], dst = parts[10];
		dst.remove_suffix(1);

		if (name_ids.find(src) == name_ids.end())
		{
			name_ids[src] = name_id++;
#ifdef VERBOSE
			dbgLUT[name_ids[src]] = src;
#endif
		}

		if (name_ids.find(dst) == name_ids.end())
		{
			name_ids[dst] = name_id++;
#ifdef VERBOSE
			dbgLUT[name_ids[dst]] = dst;
#endif
		}
		int happiness = 0;
		std::from_chars(value.data(), value.data() + value.size(), happiness);
		happiness = (gain == "gain" ? 1 : -1) * happiness;
		graph[name_ids[src]][name_ids[dst]] = happiness;
	}
}

#ifdef VERBOSE
void d13::print_seating_arrangment(const std::vector<int> seating_arrangement, const int seating_cost, const int part)
{
	std::cout << std::format("Part {}: New best {} with the following: \n", part, seating_cost);

	for (int i = 0; i < (int)seating_arrangement.size(); ++i)
	{
		int right = seating_arrangement[(i + 1) % seating_arrangement.size()];
		int right_value = graph[seating_arrangement[i]][right];
		int left = seating_arrangement[((i - 1) + seating_arrangement.size()) % seating_arrangement.size()];
		int left_value = graph[seating_arrangement[i]][left];
		std::cout << std::format("\t {} -> {} ({}) && {} -> {} ({})\n",
								 dbgLUT[i], dbgLUT[right], right_value,
								 dbgLUT[i], dbgLUT[left], left_value);
	}
	std::cout << std::endl;
}
#endif

std::pair<d13::ans_t, d13::ans_t> d13::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {-INT_MAX, -INT_MAX};
	parse_graph(sv);

#ifdef VERBOSE
	dbgLUT[(int)graph.size()] = "Self";
#endif

	std::vector<int> perm;
	for (int i = 0; i < graph.size(); ++i)
		perm.push_back(i);
	do
	{
		std::vector<int> seating_arrangement; //= {0};
		seating_arrangement.insert(seating_arrangement.end(), perm.begin(), perm.end());
		int seating_cost_p1 = 0, seating_cost_p2 = 0;
		for (int i = 0; i < (int)seating_arrangement.size(); ++i)
		{
			int right = seating_arrangement[(i + 1) % seating_arrangement.size()];
			int left = seating_arrangement[((i - 1) + seating_arrangement.size()) % seating_arrangement.size()];

			seating_cost_p2 += graph[seating_arrangement[i]][right];
			seating_cost_p2 += graph[seating_arrangement[i]][left];

			if (i < seating_arrangement.size() - 1)
			{
				auto p1_i = i % (seating_arrangement.size() - 1);
				int p1_right = seating_arrangement[(i + 1) % (seating_arrangement.size() - 1)];
				int p1_left = seating_arrangement[((i - 1) + (seating_arrangement.size() - 1)) % (seating_arrangement.size() - 1)];

				seating_cost_p1 += graph[seating_arrangement[p1_i]][p1_right];
				seating_cost_p1 += graph[seating_arrangement[p1_i]][p1_left];
			}
		}
		if (seating_cost_p1 > result.first)
		{
#ifdef VERBOSE
			auto tmp = seating_arrangement;
			tmp.pop_back();
			print_seating_arrangment(tmp, seating_cost_p1, 1);
#endif
			result.first = seating_cost_p1;
		}

		if (seating_cost_p2 > result.second)
		{
#ifdef VERBOSE
			print_seating_arrangment(seating_arrangement, seating_cost_p2, 2);
#endif
			result.second = seating_cost_p2;
		}
	} while (std::next_permutation(perm.begin(), perm.end()));

	return result;
}
