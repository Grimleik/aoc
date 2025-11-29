
/*========================================================================
	Creator: Grimleik $

	TODO: Threading and general p2 solution.
========================================================================*/
#include "d18.h"

// #define DRAW
constexpr char off = '.', on = '#';

d18::d18()
{
	input_file = read_entire_file("d18.in");
	input.emplace_back(std::make_pair(std::string_view(input_file->mem),
									  std::make_pair(814, 924)));
}

bool d18::run()
{
	auto ans = solution(input[0].first);
	CHECK_VALUE(ans.first, input[0].second.first);
	CHECK_VALUE(ans.second, input[0].second.second);
	return true;
}

int conway_game_of_life_sim(int sim_count, d18::board_t board, bool p1)
{
	int frame = 0;
	for (; frame < sim_count; ++frame)
	{
		int curr_frame = frame % 2;
		int next_frame = (frame + 1) % 2;

#ifdef DRAW
		std::string out;
		out.reserve((board.width + 1) * board.height);
#endif
		for (int y = 0; y < board.height; ++y)
		{
			for (int x = 0; x < board.width; ++x)
			{
				// simulate.
				int sim_state = board.state[curr_frame][y][x] == on ? -1 : 0;
				for (int simy = std::max(y - 1, 0); simy < std::min(y + 2, board.height); ++simy)
					for (int simx = std::max(x - 1, 0); simx < std::min(x + 2, board.width); ++simx)
					{
						if (board.state[curr_frame][simy][simx] == on)
						{
							++sim_state;
							if (sim_state > 3)
								goto done;
						}
					}
			done:
				if (sim_state == 3)
					board.state[next_frame][y][x] = on;
				else if (board.state[curr_frame][y][x] == on && sim_state == 2)
				{
					board.state[next_frame][y][x] = on;
				}
				else
					board.state[next_frame][y][x] = off;
// draw.
#ifdef DRAW
				out.push_back(board.state[curr_frame][y][x]);
#endif
			}
#ifdef DRAW
			out.push_back('\n');
#endif
		}
#ifdef DRAW
		render(out);
		// sleep a bit
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		system("cls");
#endif

		if (!p1)
		{
			board.state[next_frame][0][0] = on;
			board.state[next_frame][0][board.width - 1] = on;
			board.state[next_frame][board.height - 1][0] = on;
			board.state[next_frame][board.height - 1][board.width - 1] = on;
		}
	}

	int result = 0;
	for (int y = 0; y < board.height; ++y)
		for (int x = 0; x < board.width; ++x)
			if (board.state[frame % 2][y][x] == on)
				result++;
	return result;
}

std::pair<d18::ans_t, d18::ans_t> d18::solution(const std::string_view &sv)
{
	std::pair<ans_t, ans_t> result;
	board_t board;
	auto raw_initial_state = string_view_split(sv);
	if (raw_initial_state.size() == 0)
		return result;
	int sim_count = 100;
	board.height = (int)raw_initial_state.size();
	board.width = (int)raw_initial_state[0].size();
	board.state[0].assign(board.height, std::vector<char>(board.width, off));
	for (int row = 0; row < board.height; ++row)
	{
		board.state[0][row].assign(raw_initial_state[row].begin(), raw_initial_state[row].end());
	}
	board.state[1].assign(board.height, std::vector<char>(board.width, off));
	result.first = conway_game_of_life_sim(sim_count, board, true);

	board.state[0][0][0] = on;
	board.state[0][0][board.width - 1] = on;
	board.state[0][board.height - 1][0] = on;
	board.state[0][board.height - 1][board.width - 1] = on;
	result.second = conway_game_of_life_sim(sim_count, board, false);
	return result;
}
