/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d24.h"
// #define VERBOSE

d24::d24()
{
	// input_file = read_entire_file("d24_test.in");
	input_file = read_entire_file("d24.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(10723906903, 74850409)));
}

bool d24::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d24::ans_t, d24::ans_t> d24::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {-1, INT_MAX};
	std::vector<int> items;

	int tot_sum = 0;
	for (auto &v : string_view_split(sv))
	{
		items.push_back(string_view_to_int(v));
		tot_sum += items.back();
	}

	std::reverse(items.begin(), items.end());
	int smallest_grouping = items.size();
	std::vector<int> buckets(items.size());
	std::function<bool(int, int, uint64_t, int, int, int, int, uint64_t &)> dfs2 =
		[&](int idx, int asum, uint64_t gsum, int bucket, int bucket_size, int K, int target_sum, uint64_t &result)
	{
		if (idx >= items.size() || asum > target_sum || bucket_size > smallest_grouping)
		{
			return true;
		}
		if (asum == target_sum)
		{
			if (bucket == K)
			{
				uint64_t grouping_size = 0;
#ifdef VERBOSE
				std::cout << "Found a division! Els:";
#endif
				for (int b = 0; b < buckets.size(); ++b)
				{
					if (buckets[b] == 1)
					{
						grouping_size++;
#ifdef VERBOSE
						std::cout << " " << items[b];
#endif
					}
					else
						buckets[b] = 0;
				}
#ifdef VERBOSE
				std::cout << ". QE: " << gsum << std::endl;
#endif
				if (grouping_size < smallest_grouping)
				{
#ifdef VERBOSE
					std::cout << "***OVERRIDE***: " << gsum << " gz: " << grouping_size << std::endl;
#endif
					smallest_grouping = grouping_size;
					result = gsum;
				}
				else if (grouping_size == smallest_grouping && result > gsum)
				{
					result = std::min(result, gsum);
				}
			}
			else
			{
				dfs2(0, 0, gsum, bucket + 1, bucket_size, K, target_sum, result);
			}
			return bucket == 1;
		}
		for (int i = idx; i < items.size(); ++i)
		{
			if (buckets[i] || bucket_size > smallest_grouping)
				continue;
			buckets[i] = bucket;
			if (!dfs2(idx + 1, asum + items[i], gsum, bucket, bucket_size, K, target_sum, result))
				return false;
			buckets[i] = 0;
		}
		return true;
	};
	std::function<void(int, int, uint64_t, int, int, int, int, uint64_t &)> dfs =
		[&](int idx, int asum, uint64_t gsum, int bucket, int bucket_size, int K, int target_sum, uint64_t &result)
	{
		if (idx > items.size() || asum > target_sum || bucket_size > smallest_grouping)
		{
			return;
		}
		if (asum == target_sum)
		{
			dfs2(0, 0, gsum, bucket + 1, bucket_size, K, target_sum, result);
			return;
		}
		for (int i = idx; i < items.size(); ++i)
		{
			if (buckets[i] || bucket_size > smallest_grouping)
				continue;
			buckets[i] = bucket;
			dfs(i + 1, asum + items[i], gsum * items[i], bucket, bucket_size + 1, K, target_sum, result);
			buckets[i] = 0;
		}
	};
	dfs(0, 0, 1, 1, 0, 3, tot_sum / 3, result.first);
	dfs(0, 0, 1, 1, 0, 4, tot_sum / 4, result.second);

	return result;
}
