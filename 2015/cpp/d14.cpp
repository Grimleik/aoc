#include "d14.h"
/*========================================================================
	Creator: Grimleik $
========================================================================*/

d14::d14()
{
	input_file = read_entire_file("../../../../2015/input/d14.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(2660, 1256)));

	// input_file = read_entire_file("../../../../2015/input/d14_test.in");
	// input.emplace_back(std::make_pair(std::string_view(input_file->mem),
	// 								  std::make_pair(1120, 689)));
}

bool d14::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

std::pair<d14::ans_t, d14::ans_t> d14::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;
	// parse input.
	reindeers.clear();
	for (auto &line : string_view_split(sv, '\n'))
	{
		auto parse = string_view_split(line, ' ');
		assert(parse.size() >= 13);
		std::string_view speed_s = parse[3], move_duration_s = parse[6],
						 rest_duration_s = parse[13];

		int speed, move_duration, rest_duration;
		std::from_chars(speed_s.data(), speed_s.data() + speed_s.size(), speed);
		std::from_chars(move_duration_s.data(), move_duration_s.data() + move_duration_s.size(),
						move_duration);
		std::from_chars(rest_duration_s.data(), rest_duration_s.data() + rest_duration_s.size(),
						rest_duration);
		reindeers.push_back(reindeer_t{speed, move_duration, rest_duration, move_duration + rest_duration});
	}
	int total_duration = 2503, longest_distance = 0;
	// p1
	for (auto &r : reindeers)
	{
		r.score = 0;
		int full_lapse = (int)(total_duration / r.lapse_duration);
		int curr_distance = full_lapse * r.speed * r.move_duration;
		int last_lapse = std::min(total_duration - full_lapse * r.lapse_duration, r.move_duration);
		curr_distance += last_lapse * r.speed;
		if (curr_distance > longest_distance)
		{
			longest_distance = curr_distance;
		}
	}
	result.first = (int)longest_distance;
	// p2, simulate them ?
	std::vector<reindeer_t *> reindeers_to_award_score(reindeers.size());
	for (int i = 1; i <= total_duration; ++i)
	{
		// reindeers_to_award_score.clear(); // since we always find someone of a distance > 0. automatically cleared then.
		longest_distance = 0;
		for (auto &r : reindeers)
		{
			int full_lapse = (int)(i / r.lapse_duration);
			int curr_distance = full_lapse * r.speed * r.move_duration;
			int last_lapse = std::min(i - r.lapse_duration * full_lapse, r.move_duration);
			curr_distance += last_lapse * r.speed;
			if (curr_distance > longest_distance)
			{
				reindeers_to_award_score.clear();
				reindeers_to_award_score.emplace_back(&r);
				longest_distance = curr_distance;
			}
			else if (curr_distance == longest_distance)
			{
				reindeers_to_award_score.emplace_back(&r);
			}
		}
		for (auto r : reindeers_to_award_score)
			r->score++;
	}
	for (auto &r : reindeers)
	{
		if (result.second < r.score)
			result.second = r.score;
	}
	return result;
}
