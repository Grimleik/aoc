/*========================================================================
	Creator: Grimleik $
	This can be optimized by removing generality.
========================================================================*/
#include "d22.h"
// #define VERBOSE

using spell_id = int;
using entity_id = int;

namespace spell_properties
{
	enum TRIGGER
	{
		ON_APPLICATION = 1 << 0,
		ON_EACH_TURN = 1 << 1,
		ON_REMOVAL = 1 << 2,
	};
	static std::unordered_map<spell_id, std::string> name;
	static std::unordered_map<spell_id, int> cost;
	static std::unordered_map<spell_id, int> dmg;
	static std::unordered_map<spell_id, int> direct_dmg;
	static std::unordered_map<spell_id, int> health_modifier;
	static std::unordered_map<spell_id, int> mana_modifier;
	static std::unordered_map<spell_id, int> armor;
	static std::unordered_map<spell_id, int> duration;
	static std::unordered_map<spell_id, TRIGGER> when_to_apply;
	static int next_id;
};

struct effect_t
{
	spell_id id;
	int duration;
};

struct entity_t
{
	int hp;
	int mana;
	int armor;
	int dmg;
	int direct_dmg;
	int spent;
	std::vector<effect_t> active_effects;
#ifdef VERBOSE
	std::vector<spell_id> casts;
#endif

	void print()
	{
		std::cout << "\tHP: " << hp
				  << " MANA: " << mana
				  << " SPENT: " << spent
				  << " ARMOR: " << armor
				  << " DMG: " << dmg
				  << " DD: " << direct_dmg << std::endl;
	}
};

inline int calculate_entity_dmg(const entity_t &a, const entity_t &b)
{
	int result = a.dmg - b.armor;
	if (result <= 0)
		return 1;
	return result;
}

d22::d22()
{
	input_file = read_entire_file("../../../../2015/input/d22.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(953, 1289)));

	// TODO: Read from file.
	int id = spell_properties::next_id++;
	spell_properties::name[id] = "magic_missile";
	spell_properties::cost[id] = 53;
	spell_properties::direct_dmg[id] = 4;
	spell_properties::when_to_apply[id] = spell_properties::ON_APPLICATION;

	id = spell_properties::next_id++;
	spell_properties::name[id] = "drain";
	spell_properties::cost[id] = 73;
	spell_properties::direct_dmg[id] = 2;
	spell_properties::health_modifier[id] = 2;
	spell_properties::when_to_apply[id] = spell_properties::ON_APPLICATION;

	id = spell_properties::next_id++;
	spell_properties::name[id] = "shield";
	spell_properties::cost[id] = 113;
	spell_properties::duration[id] = 6;
	spell_properties::armor[id] = 7;
	spell_properties::when_to_apply[id] = spell_properties::ON_APPLICATION;

	id = spell_properties::next_id++;
	spell_properties::name[id] = "poison";
	spell_properties::cost[id] = 173;
	spell_properties::direct_dmg[id] = 3;
	spell_properties::duration[id] = 6;
	spell_properties::when_to_apply[id] = spell_properties::ON_EACH_TURN;

	id = spell_properties::next_id++;
	spell_properties::name[id] = "recharge";
	spell_properties::cost[id] = 229;
	spell_properties::mana_modifier[id] = 101;
	spell_properties::duration[id] = 5;
	spell_properties::when_to_apply[id] = spell_properties::ON_EACH_TURN;
}

bool d22::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d22::ans_t, d22::ans_t> d22::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result = {INT_MAX, INT_MAX};
	entity_t p = {0}, b = {0};
	p.hp = 50;
	p.mana = 500;
	p.active_effects.resize(spell_properties::next_id);
	for (int i = 0; i < spell_properties::next_id; ++i)
		p.active_effects[i].id = i;
	auto splits = string_view_split(sv);
	b.hp = string_view_to_int(string_view_split(splits[0], ' ', true)[2]);
	b.dmg = string_view_to_int(string_view_split(splits[1], ' ', true)[1]);
	std::function<void(int, entity_t, entity_t)> dfs = [&](int turn_counter, entity_t player, entity_t boss)
	{
		bool second_valid = player.hp > turn_counter;
		if (player.spent >= result.first && (!second_valid || player.spent >= result.second))
			return;

		entity_t old_p = player;
		entity_t old_b = boss;
		for (int spell = 0; spell < spell_properties::next_id; ++spell)
		{
			if (player.active_effects[spell].duration > 1)
				continue;
			// player turn
			for (auto &e : player.active_effects)
			{
				if (e.duration > 0)
				{
					if (spell_properties::when_to_apply[e.id] == spell_properties::ON_EACH_TURN)
					{
						player.armor += spell_properties::armor[e.id];
						player.dmg += spell_properties::dmg[e.id];
						player.direct_dmg += spell_properties::direct_dmg[e.id];
						player.mana += spell_properties::mana_modifier[e.id];
						player.hp += spell_properties::health_modifier[e.id];
					}
					e.duration--;
					if (e.duration == 0 && spell_properties::when_to_apply[e.id] == spell_properties::ON_APPLICATION)
					{
						player.armor -= spell_properties::armor[e.id];
						player.dmg -= spell_properties::dmg[e.id];
						player.direct_dmg -= spell_properties::direct_dmg[e.id];
						player.mana -= spell_properties::mana_modifier[e.id];
						player.hp -= spell_properties::health_modifier[e.id];
					}
				}
			}
#ifdef VERBOSE
			std::cout << "PLAYER TURN: " << turn_counter << std::endl;
			player.print();
			boss.print();
			std::cout << std::endl;
			std::cout << "\tPlayer tries to casts : " << spell_properties::name[spell] << std::endl;
			player.casts.push_back(spell);
#endif
			// "cast" spell.
			if (spell_properties::when_to_apply[spell] == spell_properties::ON_APPLICATION)
			{
				player.armor += spell_properties::armor[spell];
				player.dmg += spell_properties::dmg[spell];
				player.direct_dmg += spell_properties::direct_dmg[spell];
				player.mana += spell_properties::mana_modifier[spell];
				player.hp += spell_properties::health_modifier[spell];
			}

			player.mana -= spell_properties::cost[spell];
			player.spent += spell_properties::cost[spell];
			if (player.mana <= 0)
			{
#ifdef VERBOSE
				std::cout << "\tPlayer failed. To little mana" << std::endl;
				player.print();
#endif
				player = old_p;
				boss = old_b;
				continue;
			}
			player.active_effects[spell].duration = spell_properties::duration[spell];
			boss.hp -= player.direct_dmg;
			if (boss.hp <= 0)
			{
				if (result.first > player.spent)
				{
#ifdef VERBOSE
					std::cout << "\tPlayer killed the boss. New record! " << player.spent << std::endl;
					std::cout << "\t Spell sequence is: ";
					for (auto &id : player.casts)
					{
						std::cout << id << " ";
					}
					std::cout << std::endl;
					for (int i = 0; i < player.casts.size(); ++i)
					{
						for (int j = i + 1; j < player.casts.size(); ++j)
						{
							if (player.casts[i] == player.casts[j] && spell_properties::duration[player.casts[i]])
							{
								assert((j - i) * 2 >= spell_properties::duration[player.casts[i]]);
							}
						}
					}
#endif
					result.first = player.spent;
				}
				if (result.second > player.spent && second_valid)
				{
					result.second = player.spent;
				}
#ifdef VERBOSE
				std::cout << "\tPlayer killed the boss." << spell_properties::name[spell] << std::endl;
				player.print();
#endif
				player = old_p;
				boss = old_b;
				continue;
			}
#ifdef VERBOSE
			std::cout << "\tPlayer succeded." << std::endl;
#endif
			player.direct_dmg = 0;

#ifdef VERBOSE
			std::cout << "BOSS TURN." << std::endl;
#endif
			// boss turn, update player effects..
			for (auto &e : player.active_effects)
			{
				if (e.duration > 0)
				{
					if (spell_properties::when_to_apply[e.id] == spell_properties::ON_EACH_TURN)
					{
						player.armor += spell_properties::armor[e.id];
						player.dmg += spell_properties::dmg[e.id];
						player.direct_dmg += spell_properties::direct_dmg[e.id];
						player.mana += spell_properties::mana_modifier[e.id];
						player.hp += spell_properties::health_modifier[e.id];
					}
					e.duration--;
					if (e.duration == 0 && spell_properties::when_to_apply[e.id] == spell_properties::ON_APPLICATION)
					{
						player.armor -= spell_properties::armor[e.id];
						player.dmg -= spell_properties::dmg[e.id];
						player.direct_dmg -= spell_properties::direct_dmg[e.id];
						player.mana -= spell_properties::mana_modifier[e.id];
						player.hp -= spell_properties::health_modifier[e.id];
					}
				}
			}
			// .. which can kill the boss!
			boss.hp -= player.direct_dmg;
			if (boss.hp <= 0)
			{
				if (result.first > player.spent)
				{
#ifdef VERBOSE
					std::cout << "\tPlayer killed the boss. New record! " << player.spent << std::endl;
					std::cout << "\t Spell sequence is: ";
					for (auto &id : player.casts)
					{
						std::cout << id << " ";
					}
					std::cout << std::endl;
					for (int i = 0; i < player.casts.size(); ++i)
					{
						for (int j = i + 1; j < player.casts.size(); ++j)
						{
							if (player.casts[i] == player.casts[j] && spell_properties::duration[player.casts[i]])
							{
								assert((j - i) * 2 >= spell_properties::duration[player.casts[i]]);
							}
						}
					}
#endif
					result.first = player.spent;
				}

				if (result.second > player.spent && second_valid)
				{
					result.second = player.spent;
				}
#ifdef VERBOSE
				std::cout << "\tPlayer killed the boss." << std::endl;
				player.print();
#endif
				player = old_p;
				boss = old_b;
				continue;
			}
			player.direct_dmg = 0;
			player.hp -= calculate_entity_dmg(boss, player);
			if (player.hp <= 0 || player.mana <= 0)
			{
#ifdef VERBOSE
				std::cout << "\tPlayer died." << std::endl;
				player.print();
#endif
				player = old_p;
				boss = old_b;
				continue;
			}

#ifdef VERBOSE
			player.print();
			boss.print();
			std::cout << "==============================================================" << std::endl;
			static int turn = 0;
			if (turn < turn_counter)
			{
				std::cout << "Longest turn!" << std::endl;
				turn = turn_counter;
			}
#endif
			dfs(turn_counter + 1, player, boss);
			player = old_p;
			boss = old_b;
		}
	};
#ifdef VERBOSE
	p.print();
	b.print();
#endif
	dfs(1, p, b);
	return result;
}
