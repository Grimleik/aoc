/*========================================================================
	Creator: Grimleik $

	1: Partitioning Problem. Find all configs of smallest set, then out
	of those find the one with the lowest product. Can search for this
	at the same time as we are doing the paritioning.
========================================================================*/

#include "d24.h"

d24::d24()
{
	input_file = read_entire_file("d24.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(0, 0)));
}

bool d24::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

struct bucket_state_t
{
	int size = {0};
	int asum = {0};
	uint64_t gsum = {1};
#ifdef VERBOSE
	std::vector<int> idc;
#endif
};

std::pair<d24::ans_t, d24::ans_t> d24::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {-1, INT_MAX};
	std::vector<int> items;
#ifdef VERBOSE
	int sanity_value = 0;
#endif
	for (auto &v : string_view_split(sv))
	{
		items.push_back(string_view_to_int(v));
#ifdef VERBOSE
		sanity_value += items[items.size() - 1];
#endif
	}
	constexpr int K = 3;

	int lowest_set_size = INT_MAX;

	std::function<void(std::vector<int>, int, int)> dfs2 =
		[&](std::vector<int> placements, int idx, int size)
	{
		// size, asum, gsum.
		bucket_state_t bucket_sizes[K] = {};
		for (int pidx = 0; pidx < placements.size(); ++pidx)
		{
			bucket_sizes[placements[pidx]].size++;
			bucket_sizes[placements[pidx]].asum += items[pidx];
#ifdef VERBOSE
			bucket_sizes[placements[pidx]].idc.push_back(pidx);
#endif
		}
		for (int i = idx; i < size; ++i)
		{
			for (int k = 0; k < K; ++k)
			{
				bucket_sizes[placements[i]].size--;
				bucket_sizes[placements[i]].asum -= items[i];
#ifdef VERBOSE
				auto old_size = bucket_sizes[placements[i]].idc.size();
				bucket_sizes[placements[i]].idc.erase(std::remove(
														  bucket_sizes[placements[i]].idc.begin(),
														  bucket_sizes[placements[i]].idc.end(),
														  i),
													  bucket_sizes[placements[i]].idc.end());

				auto new_size = bucket_sizes[placements[i]].idc.size();
				assert(old_size - new_size == 1);
#endif
				placements[i] = k;
				bucket_sizes[placements[i]].size++;
				bucket_sizes[placements[i]].asum += items[i];
#ifdef VERBOSE
				bucket_sizes[placements[i]].idc.push_back(i);
				int sanity = 0;
				for (auto &b : bucket_sizes)
				{
					sanity += b.asum;
					int internal_san = 0;
					for (auto idx : b.idc)
					{
						internal_san += items[idx];
					}
					assert(internal_san == b.asum);
				}
				assert(sanity == sanity_value);
#endif
				bool check = true;
				for (int c = 1; c < K; ++c)
				{
					if (bucket_sizes[c].asum != bucket_sizes[c - 1].asum)
					{
						check = false;
						break;
					}
				}
				if (check)
				{
					for (int i2 = 0; i2 < size; ++i2)
					{
						bucket_sizes[placements[i2]].gsum *= items[i2];
					}
					auto bb = &bucket_sizes[0];
					for (auto &b : bucket_sizes)
					{
						if (b.size < lowest_set_size)
						{
							lowest_set_size = b.size;
							// #ifdef VERBOSE
							std::cout << "Updating " << result.first << " -> " << b.gsum << std::endl;
							// #endif
							result.first = b.gsum;
						}
						else if (result.first > b.gsum && b.size == lowest_set_size)
						{
							// #ifdef VERBOSE
							std::cout << "Updating " << result.first << " -> " << b.gsum << std::endl;
							// #endif
							result.first = std::min(result.first, b.gsum);
						}
					}
				}
				// TODO: Continue from here: It is something about stopping the downward descent.
				// bool go_deeper = true;
				// for (auto b : bucket_sizes)
				// {
				// 	if (b.size <= 2)
				// 	{
				// 		go_deeper = false;
				// 		break;
				// 	}
				// }
				// if (go_deeper)
				dfs2(placements, i + 1, size);
			}
		}
	};
	std::vector<int> placements(items.size());
	dfs2(placements, 0, (int)placements.size());

	return result;
}
