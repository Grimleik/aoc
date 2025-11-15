/*========================================================================
	Creator: Grimleik $
========================================================================*/
#include "d21.h"

struct entity_t
{
	int hp = {0};
	int dmg = {0};
	int armor = {0};
	int debt = {0};

	entity_t(int start_hp)
	{
		hp = start_hp;
	}

	inline int evaluate_dmg(entity_t &other)
	{
		int result = dmg - other.armor;
		if (result <= 0)
			return 1;
		return result;
	}
};

enum item_type
{
	WEAPON = 1 << 0,
	ARMOR = 1 << 1,
	RING = 1 << 2,
};

constexpr int ITEM_TYPE_COUNT = 3;

struct item_t
{
	std::string name;
	int cost;
	int dmg;
	int armor;
};

std::unordered_map<item_type, std::vector<item_t>> items;

d21::d21()
{
	auto armory = read_entire_file("../../../../2015/input/d21_armory.in");
	auto lines = string_view_split(std::string_view(armory->mem));
	int it = 0, idx = 0;
	for (int i = 1; i < lines.size(); ++i)
	{
		auto &l = lines[i];
		if (l.empty())
		{
			i += 1;
			it++;
			continue;
		}
		auto data = string_view_split(l, ' ', true, true);
		assert(data.size() == 4);
		items[(item_type)(1 << it)].push_back(item_t{std::string(data[0]),
													 string_view_to_int(data[1]),
													 string_view_to_int(data[2]),
													 string_view_to_int(data[3])});
	}

	for (auto &[k, v] : items)
	{
		std::sort(v.begin(), v.end(),
				  [](const item_t &lh, const item_t &rh)
				  {
					  return lh.cost < rh.cost;
				  });
	}

	input_file = read_entire_file("../../../../2015/input/d21.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(111, 188)));
}

bool d21::run()
{
	auto ans = solution(input[0].first);

	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);

	return true;
}

template <typename VisitFn>
void for_each_index_combintation(const std::vector<int> &sizes, VisitFn &&visit)
{
	if (sizes.size() <= 0)
		return;
	for (int s : sizes)
		if (s <= 0)
			return;

	std::vector<int> idx(sizes.size(), 0);
	const size_t n = sizes.size();
	bool run = true;
	while (run)
	{
		visit(idx);

		for (size_t pos = n; pos-- > 0;)
		{
			if (++idx[pos] < sizes[pos])
				break;
			idx[pos] = 0;
			if (pos == 0)
			{
				run = false;
				break;
			}
		}
	}
}

std::pair<d21::ans_t, d21::ans_t> d21::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {INT_MAX, INT_MIN};
	entity_t boss{0}, player{100};
	auto splits = string_view_split(sv);
	auto tmp = string_view_split(splits[0], ':', true)[1];
	tmp.remove_prefix(1);
	boss.hp = string_view_to_int(tmp);

	tmp = string_view_split(splits[1], ':', true)[1];
	tmp.remove_prefix(1);
	boss.dmg = string_view_to_int(tmp);

	tmp = string_view_split(splits[2], ':', true)[1];
	tmp.remove_prefix(1);
	boss.armor = string_view_to_int(tmp);

	std::vector<int> sizes = {
		(int)items[WEAPON].size(),
		(int)items[ARMOR].size() + 1,
		(int)items[RING].size() + 1,
		(int)items[RING].size() + 1};

	for_each_index_combintation(sizes, [&](const std::vector<int> &ids)
								{
									player.armor = 0;
									player.debt = 0;
									player.dmg = 0;
									if (ids[2] == ids[3] && ids[2] != items[RING].size())
										return; // same, but not 'unequipped' skip.

									for (int i = 0; i < ids.size(); ++i)
									{
										auto item_idx = (item_type)(1 << (std::min(i, 2)));
										// Not a weapon ? Is it marked as empty ? Skip.
										if (item_idx != WEAPON && ids[i] == items[item_idx].size())
											continue;
										player.armor += items[item_idx][ids[i]].armor;
										player.dmg += items[item_idx][ids[i]].dmg;
										player.debt += items[item_idx][ids[i]].cost;
									}
									bool player_win = false;
									int tot_boss_dmg = 0, tot_player_dmg = 0;
									while (true)
									{
										tot_player_dmg += player.evaluate_dmg(boss);
										if (tot_player_dmg >= boss.hp)
										{
											player_win = true;
											break;
										}
										tot_boss_dmg += boss.evaluate_dmg(player);
										if (tot_boss_dmg >= player.hp)
										{
											break;
										}
									}
									if (player_win && result.first > player.debt)
									{
										result.first = std::min(result.first, player.debt);
									}
									else if (!player_win && result.second < player.debt)
									{
										result.second = std::max(result.second, player.debt);
									} });

	return result;
}
