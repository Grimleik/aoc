#include <algorithm>
#include <assert.h>
#include <chrono>
#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
#include <openssl/md5.h>
#include <ratio>
#include <set>
#include <utility>
#include <vector>

#define ARRAY_COUNT(x) ((sizeof(x)) / (sizeof(x[0])))

#define CHECK_VALUE(x, y)                                                      \
	do                                                                         \
	{                                                                          \
		if (x != y)                                                            \
		{                                                                      \
			std::cout << "Value is: " << x << " expected: " << y << std::endl; \
			assert(false);                                                     \
		}                                                                      \
	} while (false);

const char *d3_paths[] = {
	">", "^>v<", "^v^v^v^v^v",
	">^^v^<>v<<<v<v^>>v^^^<v<>^^><^<<^vv>>>^<<^>><vv<<v^<^^><>>><>v<><>^^<^^^<>"
	"<>>vv>vv>v<<^>v<>^>v<v^<>v>><>^v<<<<v^vv^><v>v^>>>vv>v^^^<^^<>>v<^^v<>^<"
	"vv^^<^><<>^>><^<>>><><vv><>v<<<><><>v><<>^^^^v>>^>^<v<<vv^^<v<^<^>^^v^^^^^"
	"v<><^v><<><^v^>v<<>^<>^^v^<>v<v^>v>^^<vv^v><^<>^v<><^><v^><><><<<<>^vv^>^"
	"vvvvv><><^<vv^v^v>v<<^<^^v^<>^<vv><v<v^v<<v<<^^>>^^^v^>v<><^vv<<^<>v<v><><"
	"v^^><v<>^^>^^>v^>^<<<<v><v<<>v><^v>^>><v^^<^>v<vvvv<>>>>>^v^^>v<v<^<vv>^>^"
	"vv^>vv^^v<<^<^^<>v>vv^v>><>>>v^>^>^^v<>^<v<<>^vv>v^<<v>v<<><v>^vvv<v<vvv^"
	"v<vv<v^^^>v><<^<>><v^^>^v^>>^v<^<><v<>>v^<>>v<>>v^^^><^>>vvvv>^v<^><<>>^<>"
	"^>vv><v<<>>^^>v^^^><^<<^^v>v<^<<>v>^^vvv^v^>v^<>^^<>v^v>v>v<v^>vv>^^v<>v>>"
	"^<>><>v>v^<<vvvv<vvv><v^<^>^v<>>^><v>><>^<v>v<v>vv^>>vvv<>v>v<v^>>^>>v<<>^"
	"<>^<>>>^v<<<^<^v>vv^>><<><v^>^v^^^v<>^^vv><>><>>^>v^<v<>v<>>^<<^v>^^^<>^v^"
	"><>v<<v>vv^>vv<<>>><<^v^<>v<vv>>>^^<>^><<^>vv>>^<<v^^vv<>>><v>v><^<v<<>>>^"
	"^<>>^<^v><>vv^^^v>vvv>^><<>^^>^<<v^<v<^v<<>vvv<^<<>^>^v<vv<^>vvv>v>vv^<v^>"
	"<>>^vv<^^^vv><^vv<v^<><v^vvv><<^>^^><v<<vv^>v<vv<v>^<>^v<<>v<v^v^>^>^>v<<^"
	"vvv<<<v>^^>^<<<<>vv>>^<>^>>>v<v>^^<v^<v<>>>vv>^^v<<>>>^^v><<<v<v<^v<>^^><"
	"v<^v<<v^><><^<><v<^^v>>><v^^v<<v^><^<><<v^>><^<>v>v^<><^<v>^v^>^>^vv^>^^<<"
	"vv^>vv<^vvv<>>^^<^>v^>^>^<v^><v<v>>>v<<<><^v<<><^<vv^v^^^>v<^^<v^vvv<v<><"
	"v<vv<^vv<>vv<v^<>>vvvvv<<>^v^v>vv>>>vvv^^<^<^<><>v<v>><^v><^<<<>><<<v>^>v<"
	">^>^v>>^<>v^<^>><<>^<v>^>^^^>^^<v>>>><>^v^v><<<<vv^<vv<>vv>v<>v^<v^>v><>>>"
	"v^<><^vvv>vv^<^<<^<^^v>^>>>v<^<^v^^<^<^>>><v>vv>^<<><>^>>v>^<<>><^<>v<>vv^"
	"^>^>vvv^v<<^<^^<vv<>^vvv<^^v^vv^>>v<^>^^<v^<>v<^<^vv>v<<vv>vv>^>vvv>>>^^>"
	"v<>^v>v^<^>>v>^^v>>>>v^<v>v<^>v<v<<>>^v<^^<v><^<>>^<<vv^>>v<<v>^v<>><^>vv<"
	"v<^>>^^<vvvvvvvvv>>>v<v<>v^<>>^vv<v^^v<<^vvv^<<^><>vv<><<>>v>vv^><>>^^v^>>"
	"v^v^><<<>>^^<^v<<^<>>>>^<^>v^><<^>v<^v<^>>^^<<<<><^<^v^v<>>^v<^<<vv^<><^^"
	"vv><v^v^v>^>>^>^vv^>^v<v^v<<vvv^><>>^v^^><>v>vv><^>>vv<vvv<<<<^<>vvv^v<v>^"
	"<v<^>^<^<v<><>v^^^^<<vv<^^vv<v>><<v^><>>><v^>^v><^>^><vv^<><^<v>><<^vv<>>"
	"v^<<v<>v><v<><><vv>^>>v^<^<v>^><>>><^><v^v<>>>^^<^>v<v>vvv<>^<<><v^^>^>>v<"
	"^v>^>v>>>vv>v>>v^^^<^<vvv^<>^>^<v^<v^v>v>^>vv>vvv<>v<^>v>^^>>^<vv^^v>v^^^^"
	"^v^vv><^<><>^>vv<^>>^vvvv^^^>^<vv>^v<<^><^^>^<>^^>^<<v<^>>>^><<^^>v^v>>^>"
	"vvvv>^^v><v>>vv><<<vv<^>v>^^^<v>v^vvv<^><<^>^<>^><<<<<v^<<vv^v>^<>v<v>^>^>"
	"><>v^v<^vv^^>vv<<v^v>vv^vvv<<<<>^v<v^^v^v>v<<v>^^<>^vv^^>^>^v^vv^>>v^vv^^<"
	"vv><<v^v^^v><vv<^vvv<vv^^<<v>v^v^^^^v<^<^>v>^>v>^vv^v^^<v<^vvvv<<<>^<^^^<^"
	"^<>^<><vv<^^<<^>>><v^vvvv>^<>>^^>v^^v^<<v^^^<<<><^<v^v^^v<v^<>v><<v<>^v>v<"
	"^><^>vv^^<vvv<^v>>v>^<><v^><^^^<v^>>vv<<<<<^<>^v^v>^vv^<>v>v<^>vv<<^vv>vv<"
	"v<><>>v>><v<^<^^>><<v^v<<^><v<^<vv<v<<vv^>^<<><^^>^<^>>^<vv>><v<<vvv<^^v^>"
	"^^<^v>^v<v<>v><v^v^<<^<><<v<<^v>v<<>>^>v>>v>>v<^<<^<^>>>v>^^^v><^>^^>>v<<>"
	"^v><v>vvv^vv<<<>vvv<<>^>>>v<v<v^<^<^>^<^>v^^v<^^<v<>v<>>^^>^v^>v<<<<^<>v^>"
	"<<<v>>>><<v^<^vv>v>><>>^<<<^<^^>v<>>v<>vv<<^<<><<^>v^^^vv^>vvvv>>v>v^><<v<"
	">vv^<<><<vvv>^>>>^<<<^<^<<v>^>v<>>v>>vv^^><<<<^^^v>><<^><v><v^^><v<<v^^v^^"
	"v>>v<><><<>^><v><^<vv>><^v<>v<vvv<>^>><v>>v<^><<v>^<>^v><^><^^<v>^><^^v^<<"
	"><>>^>v^<^v^vv<><^>vv^>v^vvv^<>>^><^<^<>^<<v^v<^v><>^v<v>>^>>^v^vv>><vv><"
	"v^^<<^v^<>^v<<>^><^>><v>>v<<<v^^vv<>^^v>>><><><<v^<<<v^<^^><v^>v^^vv<v^<>>"
	"vv^<^v<>^v>>v^v>v<^^vv><>^v<<>v^<>v^>>v>vvv<^><><^^>^vv^>>v^>^<^^<><>><<>^"
	"^^><^v^v><<<><<^v^vv>v>><^>>><v^>v<v><><v^v<>v^^>>v<<>v>v<v<v<^^<><>v^^<>>"
	"v<^v<v>v<><v<v>^<<>v>vv^^<>>^^^<>^^>^v>v>>>^v^v><v^^<><v>^^v^v<^<^^><<v<^<"
	"^<>^<>><<>^>>^>^^><v><>v<><>><<<>>>>vv>>>^>>^v<^>v^^^v<<vv>><<<^<<<>>>>>^>"
	"vv<^v^<>^<v^>^v><v>vvv<>>>^v^^^v<<<<>>^^<vv<^<^^>^<>v<^<<<>><>>v<^<>^<vvv<"
	"^<>><><<v>^^^>^^<<v<v^>^^v^>><<^vv><v>^v>>^<v>v>^^>^v>^vvv<>v^v^^<><vv>vv^"
	">>><>v<^><v<v^<><<<>^v>^v<<<^>^>^>v^v<<><vvv<<v^^<><v>^>>><vv>><v>>v^<vv>>"
	"vv<<^v^v<<><^v<vv>>>vv<>>>>^vv>v^<>vv>v^v<v^><v<^^^^^>vv<><<vvv^<v><^<vv><"
	"^^^vv^<>^^^^<^><^<>v^<v^v<<^v<<^^<>>^<v^^>>>vv<vvv<>v<<>><^vvv^<<^^<<>>>^<"
	">>>v^^><>><<>><v^v>>>>>><>>><v^<<vvv^>v<>>v^<>vv<><^^^^v^<<^<v^vv><<^^>v<^"
	"vvv^v>>v>^>>v>^^><<v^<>v<>vv<^v^vv><v><<vv^v>>v^>>v<^^^>^><<v<>^><>v>>>"
	"vvv<v<vv<^>>^v<v>^<^^^^^v><>v><>v^v^v<v^vv^v>vvvv<>vv<<<vv<v<<>^<^>^^v^<<>"
	"^<v><^><v<v<><<>v^<<^<><vv>v<<^v>>^v<><v>^>>^^><>v^<^<vvv^>^>^<<<<>vv>^v^"
	"v<^^^<vv>><>^^<<v<^<^^>>>v^v<<^^^<v<v<^<>^v<v><v^vv^^v^^v^^<vv<>^<><vv^<^"
	"v^<<^><<vvv>^^<^^^<^v>^>^vv><<<^v<v>vv>v<>v^v<v^>v^>>>v^v<>^v<<>^vv>v>v>v^"
	"<^>v^^<^>^^^^vv>^^><^>vv^>>^^v>><<<<^><>v<>^<v<vv^>^^><<^><v>v^>^^<^>>><>>"
	"<v^v<v^<v<vv^v^<<^<vvv>>><vv<^^>>^>^><<v^<>>v>v^v^^><<>vv^v>v^<v><^<>^^<^>"
	"v>^<><<<v>^<^<^>^>^>^^v^<<^^v^^<^<>><^>v>>^^<>^^^<<<<v^>^v<^vv>^<<<v<><<v<"
	">vv>>>v><>>><>>v<<<vv><>^v>v<^>><^><><v<>^v^>^v>^v<<><<^<>>v>^><>^>><>><^<"
	"v^><v^^<><v><^^>^v^^<>v^<v^<^v<v^^^^^v^<<^>^^^<^v><>^^<<<><<<<<^^>v^vvvv>"
	"v<>>vv<^>^v^>v<^vv^v<<><<v>v^v>^^><><^<v^>v><vv><>>><<>^vv<>v>>v<^v>>>v<v>"
	"v>v>^vv<<>^^vv<v<^v^<v<v>vv<>^<^<vv<v^<^v^^><<>^>><^v>vv^^v<<^^><<>v^^<><>"
	"<v^^<v^v>^>^>^>v<^<v>^v^^>v<>vvv<^v<v^v><<v^><<^^><^<<v^v^>v<>^>v><><v>^<"
	"v<v>^<^^^>^v<<><<><>vv>v^<>v^><v^v<v><><<v>v<vv><<v>>v>^<<<>vv>>vvv>^^vv^"
	"v^^<^^<>v^^<>v>>^^>^>^>v>><^>><>>^<<>><^>v<<<<<<<^v^v<v^<v^^>^<><<v<^>v^>"
	"v^vv<<^^vv^>>>>^<>v<^v<>v<vv<^>>v^vv>vv><vv<<^>v>><vv>>>vv^<<<<vv^>v<<<<^^"
	">^^v^><<^<v^>v^>^^<v<>vvv^>^<>vvv<v<^^>v^<<v>><>v<v<>^^<vvv>^>vv><><<<^^"
	"vv<v^<v<>v<>><<v><^vv^>^<^>^^^<<<v>vv^<^<<>^>^<vv>v><v<<^><^>^^<vv^v^^>>>>"
	"vv^><^^vv><>^<v^v>v<vv>v><<<v>v<v>^><v^^><v>v<^v^>>^^<v^>^^>vv>>vv^><^vv^"
	"vv<<^>vv>^v<v><vv><v<vvvvv>^^v^v><v>>>^vv<>v>^^^^<^>><>^v^^^>v<^^<<^^v<vv<"
	">vvv<^>><><^>>^><^<>v<v<<><<v><v^v<>><^>v><<v^<v>v<^<vv^v^v^>vvv^^>v>^<vv^"
	">v^v^<>v>^>>vv>><^^<v<<>^vv<><><<^v<v>v<<vv><>><^v<v>>v^>vvv^v^<<^><v<>^"
	"vv^>v^<v<^>>v<v><v><v>>^<<<v^<><<>v>^>^^<v<>>^<>^>^><<<^<<^<<^>^v>>><vvv>>"
	"<<<<v>>>>>>>^<^v<^>v<>vv<><>v>>^>>^>vv^^><<^<v<v>>^^<<^>v<^>>vv>^<>v><^>v<"
	"vv>>>>>>^v<^<<<v^><vv<<>>vv<<><v<><<<v<^<v<>>v<^^^^v^^<^^^<^<vv><<^>><>v<<"
	">v<v<>>>><>v^vv>^>^>>vv^v<v<<><^v>vv^><v<<>v^v<^>vv<<^^v><^>>^^vv<^<>>v^^>"
	"><v>^v>>>^>>v>v<>v<^vv><>^<<^>vv>>><><>v^><>v^>v>v><^v<><v<v>^v<<^vv^><^^>"
	"><^^^<<<^>v>^v>>><^>><^>>>^^^<^>vv<><<<v^>^<^^>>^^^v^v^v>v<v>>>><^>>>v>^"
	"vv<<^^^<^^vv>v<<><v<<^^>v>><<v^^><^>^<^>^v^>v><^<^vv>v>><>^<<vv<<v>v<vv<v>"
	"^>^>><^^<v>^v^v<><<>vvv<^<v>^><>^>vvv>>>^><<>><v^^<^<<^v>>^v<v<vv>vv^v^>v<"
	"<vvv<^^v^v>^<^>>^>v<^>^v<<><<<^>^<^^^>vv<^^^^vv<v<^^v<<<<v<^v^<><v<<^><<>"
	"vv>>><^<^<>>>^>^>>^<<<<<^^v>^>^<>vvv^^<^><^>^^v>^vv^><v^<^<<v^<vvv<<^v<><^"
	"><^>>>v>^v>^>^v<vv^v>><v><^><v^^>v^>^<><<><>v<v^>vvv^>^>>v<>^><^>^><vvv>^^"
	"v^v>v<>^v^><^>>v>v^><<<^>>^<>^<>>v><>>v^>^>^^<>>v^>^<vvvv<^vvvv^>>vv^<v^v>"
	"^vv<>v<>^<v<v>v>^^><^>vv^<^v^<<^<^<><vv<^v<^v><>>>^v^<<^><^>vv<v>v<^>vv^>"
	"v<<<>^<><v<^^^>v><^^<>^<^<v^vv^<<^>><<v^v<^vvv<<<>>vvvv^v^^^>v<>>><<>vvv<<"
	"^^^>v>v>>v<<v<v^v^>^^v>^><^<><<v^<v<v^^^><>v^^^<v>vv<>^>^^vv>^<<^v<^v><v>>"
	">^>>><^<<>^v>>^>vv<<<v<>^<v><v^<^<>v>v^^v^>><<^v<<<<>v>v>v^^<^><>^^<<<v>"
	"vv<>>>^>>v<><v^>^<><vv>v>v^v<v^<^>>^>><<^^<^^v<vv<>><<<v<^<<^^^>vvv^<vvv<^"
	">vv><>><<<^<v^v^^<<^vvv^^<^<><<>^<^<>>vvv<>^<>v^v<><>>v^v><<>>>vvv>v<>^>>^"
	"><^>vv<<>>v<<^><>v>>^^<v>^>^<<>><^<<vv<^<vv^vv><>>>><^<v>^>vv<v><>^<>"
	"vvvvv^vv<<v<>>>^<<><>^^vvv>>>vv<<^^><^v^^v<>^^>^><^>v^^^^v<^<<vv<vv<>vv^^>"
	"v^vv>v><>>vv>^<^<v^v^>>v^v^^v>^>vv^>v<vvvv<^v<^v>^v>^^v<<^>^^<<>^><^v>>>"
	"vv^>^^>vvvv>>v<^<v>^>>>v^<><^<^^<v>vv^^><v>v^<>^^^>>><^^v>v>^<<>^<v^>vvv^>"
	"^^^><v<^>>v<v>>^v><<><<>v<^<<>^><>^>vv>^<v>^^v<<^v^vvv^^>^vv^<^>^>^^v>v^>^"
	"<<><<^>v>>vv^vv><v>>^<<^<v^^<^<v^^vv^><^^<^^><v^^>v^^^<^<>^<>>^v<^vvv^^v^<"
	"><^>>>>>v><><<<>vv<^v>><<>vvv<><<vv<<<^>v^^>>^>^v>><><^^v<>><>>v^>^<vv><<<"
	">><><<v>^^<>>v<><^<vv>vv<^v>^<<<<v<^<<^^>>^<><^>><<>^>v>^^^v>>^<^^v><v^v>^"
	"><<><>>^>>^<<v<>^v<>^>^<v>>vv>^vvv<<v<<^>^>^<<^^<>^^^^vvv<>^vv<vvvvv^^>^^<"
	"^>>><>v^<><^<<^>v^^v<>>^vv<>v^^<>>v^vvvvv<<v^<v^^>>><vvvvv>><^>vv>v^v^<v<^"
	">^^><^>^^^^v<><^v<<>v^>v>>vv<<>^<v^^>vvv>^^<v^<>vv^><>><v^^v<>^>>^>v><>>^^"
	"v>^>^>>>^>v<^v>v>^<^^^^^>>v<v<>>v<<^>^<v<<>^^>><<^><>v<>^^^vv<>^^>><<^^>v>"
	"vv>vv>v^>^v>v^^<>>><<v><v<<>>v><>vvv^^v>^^>^vvvv^>^<>^vvvv><v><v<>>><>^<^"
	"vv<>^v<^v<>^vvv<<>><vvv^>>^><<vv^<v^>^<v<<^^>^^<^^v^>v<>v^v><>><v^^>>^vvv>"
	"<^vv>v^<^<^v>>v^^>^vvv^<v^^v^^>v<^<>>^<>>>^^<><^^vv<>^vv^<>>>>^^<<^^<>vv^^"
	"><>^^<v<<v>^<v^^>^v<><><>vvv>^v^>>vv<<^v<<>><v>^><^>>>^<^<^^>vv^<<^<>>^^><"
	"><<v>^^<v>>v<<vvvv>^v^vv>><^^<<^>>v>v<^^^<^><^^vv>^vv<^<vv<>v><^<><v><^^^>"
	">^<><^<v>>>>v^<v>>>>>v<><^^>v<^<^>><v<>^>vv>^^v^v^<<v<><<<^v^><<^<><<<<v<^"
	">><<<>v>>vv><vv<><<^<^<><vv>^^^^<>v<<<<v>vv<>vv^^^>><>vv^><>>^vv<<><^^vv<>"
	"v^>>^<<>^<v^<^>v<",
	"^v"};

const int d3_ans[2][3] = {{2, 4, 2}, {3, 3, 11}};

int d3p1_house_delivery(const char *path, const int nrActors)
{
	assert(nrActors < 32);
	int actorId = 0;
	std::vector<std::pair<int, int>> actorLocations(nrActors);
	std::map<std::pair<int, int>, int> visit; // location = visited.
	//   for (int i = 0; i < nrActors; ++i) {
	//     visit[std::make_pair(0, 0)] |= 1 << i;
	//   }
	visit[std::make_pair(0, 0)] = 1;

	while (*path)
	{
		int &x = actorLocations[actorId].first;
		int &y = actorLocations[actorId].second;

		if (*path == '^')
		{
			++y;
		}
		else if (*path == '>')
		{
			++x;
		}
		else if (*path == 'v')
		{
			--y;
		}
		else if (*path == '<')
		{
			--x;
		}
		else
		{
			std::cout << "Failure reading path instruction: " << *path << std::endl;
		}
		// visit[std::make_pair(x, y)] |= 1 << actorId;
		visit[std::make_pair(x, y)] = 1;
		++path;
		actorId = (actorId + 1) % (nrActors);
	}
	// STUDY: It doesn't matter who visists a location, it is all about actually
	// visiting.
	//   int result = 0;
	//   for (auto kvp : visit) {
	//     result += (kvp.second & 0x10) + (kvp.second & 0x1);
	//   }
	return visit.size();
}

// TODO: Implement MD5 instead ?
//
// STUDY: I think there is a part of the
// algorithm which inserts the padding of 0's that we can exploit.
const unsigned int s[64] = {
	7,
	12,
	17,
	22,
	7,
	12,
	17,
	22,
	7,
	12,
	17,
	22,
	7,
	12,
	17,
	22,
	5,
	9,
	14,
	20,
	5,
	9,
	14,
	20,
	5,
	9,
	14,
	20,
	5,
	9,
	14,
	20,
	4,
	11,
	16,
	23,
	4,
	11,
	16,
	23,
	4,
	11,
	16,
	23,
	4,
	11,
	16,
	23,
	6,
	10,
	15,
	21,
	6,
	10,
	15,
	21,
	6,
	10,
	15,
	21,
	6,
	10,
	15,
	21,
};
const unsigned int K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
const char *d4_words[] = {"abcdef", "pqrstuv", "iwrupvqb"};
const int d4_ans[] = {609043, 1048970};

int md5_zeros_hash(const char *msg)
{
	//   int a0 = 0x67452301;
	//   int b0 = 0xefcdab89;
	//   int c0 = 0x98badcfe;
	//   int d0 = 0x10325476;
	int nbr = 0;
	std::string input(msg);
	// auto start = std::chrono::high_resolution_clock::now();
	unsigned char md[MD5_DIGEST_LENGTH];
	while (nbr < INT_MAX)
	{
		input = msg + std::to_string(nbr);
		MD5((const unsigned char *)(input.c_str()), input.size(), md);
		if ((int)md[0] == 0 && (int)md[1] == 0 && (int)md[2] == 0)
			break;
		// if(!(nbr % 10000)) {
		// 	auto end = std::chrono::high_resolution_clock::now();
		// 	std::cout << nbr << " Done, time elapsed: " <<
		// std::chrono::duration_cast<std::chrono::milliseconds>(end -
		// start).count() << "." << std::endl; 	start = end;
		// }
		// std::cout << "MD5(" << msg << ") = ";
		// for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
		//   std::cout << std::hex << std::setw(2) << std::setfill('0') <<
		//   (int)md[i];
		// }
		// std::cout << std::endl;
		++nbr;
	}
	return nbr;
}

const char *d5_words[] = {"aeixx",
						  "aeixxab",
						  "ugknbfddgicrmopn",
						  "aaa",
						  "jchzalrnumimnmhp",
						  "haegwjzuvuyypxyu",
						  "dvszwmarrgswjxmb"};

const bool d5_ans[] = {
	true,
	false,
	true,
	true,
	false,
	false,
	false,
};

const char *d5_words_p2[] = {
	"aaaa",
	"xyxy",
	"aaa",
	"aaabab",
	"xxyxx",
	"uurcxstgmygtbstg",
	"ieodomkazucvgmuy",
};

const bool d5_ans_p2[] = {
	true,
	true,
	false,
	true,
	true,
	false,
	false,
};

const char *d5_input[] = {
	"zgsnvdmlfuplrubt", "vlhagaovgqjmgvwq", "ffumlmqwfcsyqpss",
	"zztdcqzqddaazdjp", "eavfzjajkjesnlsb", "urrvucyrzzzooxhx",
	"xdwduffwgcptfwad", "orbryxwrmvkrsxsr", "jzfeybjlgqikjcow",
	"mayoqiswqqryvqdi", "iiyrkoujhgpgkcvx", "egcgupjkqwfiwsjl",
	"zbgtglaqqolttgng", "eytquncjituzzhsx", "dtfkgggvqadhqbwb",
	"zettygjpcoedwyio", "rwgwbwzebsnjmtln", "esbplxhvzzgawctn",
	"vnvshqgmbotvoine", "wflxwmvbhflkqxvo", "twdjikcgtpvlctte",
	"minfkyocskvgubvm", "sfxhhdhaopajbzof", "sofkjdtalvhgwpql",
	"uqfpeauqzumccnrc", "tdflsbtiiepijanf", "dhfespzrhecigzqb",
	"xobfthcuuzhvhzpn", "olgjglxaotocvrhw", "jhkzpfcskutwlwge",
	"zurkakkkpchzxjhq", "hekxiofhalvmmkdl", "azvxuwwfmjdpjskj",
	"arsvmfznblsqngvb", "ldhkzhejofreaucc", "adrphwlkehqkrdmo",
	"wmveqrezfkaivvaw", "iyphmphgntinfezg", "blomkvgslfnvspem",
	"cgpaqjvzhbumckwo", "ydhqjcuotkeyurpx", "sbtzboxypnmdaefr",
	"vxrkhvglynljgqrg", "ttgrkjjrxnxherxd", "hinyfrjdiwytetkw",
	"sufltffwqbugmozk", "tohmqlzxxqzinwxr", "jbqkhxfokaljgrlg",
	"fvjeprbxyjemyvuq", "gmlondgqmlselwah", "ubpwixgxdloqnvjp",
	"lxjfhihcsajxtomj", "qouairhvrgpjorgh", "nloszcwcxgullvxb",
	"myhsndsttanohnjn", "zjvivcgtjwenyilz", "qaqlyoyouotsmamm",
	"tadsdceadifqthag", "mafgrbmdhpnlbnks", "aohjxahenxaermrq",
	"ovvqestjhbuhrwlr", "lnakerdnvequfnqb", "agwpwsgjrtcjjikz",
	"lhlysrshsmzryzes", "xopwzoaqtlukwwdu", "xsmfrfteyddrqufn",
	"ohnxbykuvvlbbxpf", "bbdlivmchvzfuhoc", "vtacidimfcfyobhf",
	"tinyzzddgcnmiabd", "tcjzxftqcqrivqhn", "vgnduqyfpokbmzim",
	"revkvaxnsxospyow", "ydpgwxxoxlywxcgi", "wzuxupbzlpzmikel",
	"nscghlafavnsycjh", "xorwbquzmgmcapon", "asmtiycegeobfxrn",
	"eqjzvgkxgtlyuxok", "mmjrskloposgjoqu", "gceqosugbkvytfto",
	"khivvoxkvhrgwzjl", "qtmejuxbafroifjt", "ttmukbmpoagthtfl",
	"bxqkvuzdbehtduwv", "gvblrpzjylanoggj", "cltewhyjxdbmbtqj",
	"fbkgedqvomdipklj", "uxvuplhenqawfcjt", "fkdjmayiawdkycva",
	"gnloqfgbnibzyidh", "kyzorvtopjiyyyqg", "drckpekhpgrioblt",
	"tvhrkmbnpmkkrtki", "khaldwntissbijiz", "aoojqakosnaxosom",
	"xfptccznbgnpfyqw", "moqdwobwhjxhtrow", "chfwivedutskovri",
	"gprkyalfnpljcrmi", "pwyshpwjndasykst", "xuejivogihttzimd",
	"bugepxgpgahtsttl", "zufmkmuujavcskpq", "urybkdyvsrosrfro",
	"isjxqmlxwtqmulbg", "pxctldxgqjqhulgz", "hclsekryiwhqqhir",
	"hbuihpalwuidjpcq", "ejyqcxmfczqfhbxa", "xljdvbucuxnnaysv",
	"irqceqtqwemostbb", "anfziqtpqzqdttnz", "cgfklbljeneeqfub",
	"zudyqkuqqtdcpmuo", "iuvhylvznmhbkbgg", "mpgppmgfdzihulnd",
	"argwmgcvqqkxkrdi", "pdhrfvdldkfihlou", "cbvqnjrvrsnqzfob",
	"lkvovtsqanohzcmm", "vxoxjdyoylqcnyzt", "kurdpaqiaagiwjle",
	"gwklwnazaxfkuekn", "rbaamufphjsjhbdl", "tzbrvaqvizhsisbd",
	"pbcqlbfjvlideiub", "hiwoetbfywaeddtx", "fjirczxtuupfywyf",
	"omeoegeyyospreem", "ozbbpupqpsskvrjh", "pzvcxkvjdiyeyhxa",
	"odclumkenabcsfzr", "npdyqezqdjqaszvm", "yodkwzmrhtexfrqa",
	"rjcmmggjtactfrxz", "mioxfingsfoimual", "aqskaxjjborspfaa",
	"wientdsttkevjtkf", "tdaswkzckmxnfnct", "voucjhzvkkhuwoqk",
	"boaaruhalgaamqmh", "iufzxutxymorltvb", "pfbyvbayvnrpijpo",
	"obztirulgyfthgcg", "ntrenvhwxypgtjwy", "ephlkipjfnjfjrns",
	"pkjhurzbmobhszpx", "gqbnjvienzqfbzvj", "wjelolsrbginwnno",
	"votanpqpccxqricj", "bxyuyiglnmbtvehi", "qyophcjfknbcbjrb",
	"anoqkkbcdropskhj", "tcnyqaczcfffkrtl", "rsvqimuqbuddozrf",
	"meppxdrenexxksdt", "tyfhfiynzwadcord", "wayrnykevdmywycf",
	"mhowloqnppswyzbu", "tserychksuwrgkxz", "xycjvvsuaxsbrqal",
	"fkrdsgaoqdcqwlpn", "vrabcmlhuktigecp", "xgxtdsvpaymzhurx",
	"ciabcqymnchhsxkc", "eqxadalcxzocsgtr", "tsligrgsjtrnzrex",
	"qeqgmwipbspkbbfq", "vzkzsjujltnqwliw", "ldrohvodgbxokjxz",
	"jkoricsxhipcibrq", "qzquxawqmupeujrr", "mizpuwqyzkdbahvk",
	"suupfxbtoojqvdca", "ywfmuogvicpywpwm", "uevmznxmsxozhobl",
	"vjbyhsemwfwdxfxk", "iyouatgejvecmtin", "tcchwpuouypllcxe",
	"lgnacnphdiobdsef", "uoxjfzmdrmpojgbf", "lqbxsxbqqhpjhfxj",
	"knpwpcnnimyjlsyz", "fezotpoicsrshfnh", "dkiwkgpmhudghyhk",
	"yzptxekgldksridv", "pckmzqzyiyzdbcts", "oqshafncvftvwvsi",
	"yynihvdywxupqmbt", "iwmbeunfiuhjaaic", "pkpkrqjvgocvaxjs",
	"ieqspassuvquvlyz", "xshhahjaxjoqsjtl", "fxrrnaxlqezdcdvd",
	"pksrohfwlaqzpkdd", "ravytrdnbxvnnoyy", "atkwaifeobgztbgo",
	"inkcabgfdobyeeom", "ywpfwectajohqizp", "amcgorhxjcybbisv",
	"mbbwmnznhafsofvr", "wofcubucymnhuhrv", "mrsamnwvftzqcgta",
	"tlfyqoxmsiyzyvgv", "ydceguvgotylwtea", "btyvcjqhsygunvle",
	"usquiquspcdppqeq", "kifnymikhhehgote", "ybvkayvtdpgxfpyn",
	"oulxagvbavzmewnx", "tvvpekhnbhjskzpj", "azzxtstaevxurboa",
	"nfmwtfgrggmqyhdf", "ynyzypdmysfwyxgr", "iaobtgubrcyqrgmk",
	"uyxcauvpyzabbzgv", "fbasfnwiguasoedc", "mgmjoalkbvtljilq",
	"szgkxiqkufdvtksb", "xgfzborpavdmhiuj", "hmuiwnsonvfgcrva",
	"zolcffdtobfntifb", "mvzgcsortkugvqjr", "pbbpgraaldqvzwhs",
	"zvsxegchksgnhpuv", "kdpdboaxsuxfswhx", "jdfggigejfupabth",
	"tpeddioybqemyvqz", "mxsntwuesonybjby", "tzltdsiojfvocige",
	"ubtdrneozoejiqrv", "fusyucnhncoxqzql", "nlifgomoftdvkpby",
	"pyikzbxoapffbqjw", "hzballplvzcsgjug", "ymjyigsfehmdsvgz",
	"vpqgyxknniunksko", "ffkmaqsjxgzclsnq", "jcuxthbedplxhslk",
	"ymlevgofmharicfs", "nyhbejkndhqcoisy", "rjntxasfjhnlizgm",
	"oqlnuxtzhyiwzeto", "tntthdowhewszitu", "rmxyoceuwhsvfcua",
	"qpgsjzwenzbxyfgw", "sumguxpdkocyagpu", "ymfrbxwrawejkduu",
	"hetgrtmojolbmsuf", "qzqizpiyfasgttex", "qnmoemcpuckzsshx",
	"ddyqiihagcmnxccu", "oirwxyfxxyktgheo", "phpaoozbdogbushy",
	"uctjdavsimsrnvjn", "aurbbphvjtzipnuh", "hpbtrubopljmltep",
	"pyyvkthqfsxqhrxg", "jdxaiqzkepxbfejk", "ukgnwbnysrzvqzlw",
	"lfkatkvcssnlpthd", "ucsyecgshklhqmsc", "rwdcbdchuahkvmga",
	"rxkgqakawgpwokum", "hbuyxeylddfgorgu", "tbllspqozaqzglkz",
	"rqfwizjlbwngdvvi", "xuxduyzscovachew", "kouiuxckkvmetvdy",
	"ycyejrpwxyrweppd", "trctlytzwiisjamx", "vtvpjceydunjdbez",
	"gmtlejdsrbfofgqy", "jgfbgtkzavcjlffj", "tyudxlpgraxzchdk",
	"gyecxacqitgozzgd", "rxaocylfabmmjcvt", "tornfzkzhjyofzqa",
	"kocjcrqcsvagmfqv", "zfrswnskuupivzxb", "cunkuvhbepztpdug",
	"pmpfnmklqhcmrtmf", "tfebzovjwxzumxap", "xpsxgaswavnzkzye",
	"lmwijdothmxclqbr", "upqxhmctbltxkarl", "axspehytmyicthmq",
	"xdwrhwtuooikehbk", "tpggalqsytvmwerj", "jodysbwnymloeqjf",
	"rxbazvwuvudqlydn", "ibizqysweiezhlqa", "uexgmotsqjfauhzp",
	"ldymyvumyhyamopg", "vbxvlvthgzgnkxnf", "pyvbrwlnatxigbrp",
	"azxynqididtrwokb", "lwafybyhpfvoawto", "ogqoivurfcgspytw",
	"cinrzzradwymqcgu", "sgruxdvrewgpmypu", "snfnsbywuczrshtd",
	"xfzbyqtyxuxdutpw", "fmpvjwbulmncykbo", "ljnwoslktrrnffwo",
	"ceaouqquvvienszn", "yjomrunrxjyljyge", "xpmjsapbnsdnbkdi",
	"uetoytptktkmewre", "eixsvzegkadkfbua", "afaefrwhcosurprw",
	"bwzmmvkuaxiymzwc", "gejyqhhzqgsrybni", "gjriqsfrhyguoiiw",
	"gtfyomppzsruhuac", "ogemfvmsdqqkfymr", "jgzbipsygirsnydh",
	"zghvlhpjnvqmocgr", "ngvssuwrbtoxtrka", "ietahyupkbuisekn",
	"gqxqwjizescbufvl", "eiprekzrygkncxzl", "igxfnxtwpyaamkxf",
	"soqjdkxcupevbren", "fspypobyzdwstxak", "qstcgawvqwtyyidf",
	"gsccjacboqvezxvd", "bfsblokjvrqzphmc", "srezeptvjmncqkec",
	"opmopgyabjjjoygt", "msvbufqexfrtecbf", "uiaqweyjiulplelu",
	"pbkwhjsibtwjvswi", "xwwzstmozqarurrq", "nytptwddwivtbgyq",
	"ejxvsufbzwhzpabr", "jouozvzuwlfqzdgh", "gfgugjihbklbenrk",
	"lwmnnhiuxqsfvthv", "bzvwbknfmaeahzhi", "cgyqswikclozyvnu",
	"udmkpvrljsjiagzi", "zzuhqokgmisguyna", "ekwcdnjzuctsdoua",
	"eueqkdrnzqcaecyd", "lnibwxmokbxhlris", "fdrbftgjljpzwhea",
	"iabvuhhjsxmqfwld", "qgogzkynrgejakta", "mfcqftytemgnpupp",
	"klvhlhuqhosvjuqk", "gdokmxcgoqvzvaup", "juududyojcazzgvr",
	"fyszciheodgmnotg", "yfpngnofceqfvtfs", "cahndkfehjumwavc",
	"dxsvscqukljxcqyi", "cqukcjtucxwrusji", "vevmmqlehvgebmid",
	"ahswsogfrumzdofy", "ftasbklvdquaxhxb", "tsdeumygukferuif",
	"ybfgbwxaaitpwryg", "djyaoycbymezglio", "trzrgxdjqnmlnzpn",
	"rumwchfihhihpqui", "ffrvnsgrnzemksif", "oizlksxineqknwzd",
	"cirqcprftpjzrxhk", "zrhemeqegmzrpufd", "kqgatudhxgzlgkey",
	"syjugymeajlzffhq", "nlildhmgnwlopohp", "flcszztfbesqhnyz",
	"ohzicmqsajyqptrw", "ebyszucgozsjbelq", "enxbgvvcuqeloxud",
	"ubwnvecbsmhkxwuk", "noifliyxvlkqphbo", "hazlqpetgugxxsiz",
	"ihdzoerqwqhgajzb", "ivrdwdquxzhdrzar", "synwycdvrupablib",
	"mqkdjkntblnmtvxj", "qmmvoylxymyovrnq", "pjtuxskkowutltlq",
	"gchrqtloggkrjciz", "namzqovvsdipazae", "yfokqhkmakyjzmys",
	"iapxlbuoiwqfnozm", "fbcmlcekgfdurqxe", "ednzgtczbplwxjlq",
	"gdvsltzpywffelsp", "oaitrrmpqdvduqej", "gseupzwowmuuibjo",
	"dfzsffsqpaqoixhh", "tclhzqpcvbshxmgx", "cfqkptjrulxiabgo",
	"iraiysmwcpmtklhf", "znwjlzodhktjqwlm", "lcietjndlbgxzjht",
	"gdkcluwjhtaaprfo", "vbksxrfznjzwvmmt", "vpfftxjfkeltcojl",
	"thrmzmeplpdespnh", "yafopikiqswafsit", "xxbqgeblfruklnhs",
	"qiufjijzbcpfdgig", "ikksmllfyvhyydmi", "sknufchjdvccccta",
	"wpdcrramajdoisxr", "grnqkjfxofpwjmji", "lkffhxonjskyccoh",
	"npnzshnoaqayhpmb", "fqpvaamqbrnatjia", "oljkoldhfggkfnfc",
	"ihpralzpqfrijynm", "gvaxadkuyzgbjpod", "onchdguuhrhhspen",
	"uefjmufwlioenaus", "thifdypigyihgnzo", "ugqblsonqaxycvkg",
	"yevmbiyrqdqrmlbw", "bvpvwrhoyneorcmm", "gbyjqzcsheaxnyib",
	"knhsmdjssycvuoqf", "nizjxiwdakpfttyh", "nwrkbhorhfqqoliz",
	"ynsqwvwuwzqpzzwp", "yitscrgexjfclwwh", "dhajwxqdbtrfltzz",
	"bmrfylxhthiaozpv", "frvatcvgknjhcndw", "xlvtdmpvkpcnmhya",
	"pxpemuzuqzjlmtoc", "dijdacfteteypkoq", "knrcdkrvywagglnf",
	"fviuajtspnvnptia", "xvlqzukmwbcjgwho", "bazlsjdsjoeuvgoz",
	"nslzmlhosrjarndj", "menvuwiuymknunwm", "uavfnvyrjeiwqmuu",
	"yrfowuvasupngckz", "taevqhlrcohlnwye", "skcudnogbncusorn",
	"omtnmkqnqedsajfv", "yqmgsqdgsuysqcts", "odsnbtyimikkbmdd",
	"vuryaohxdvjllieb", "dhaxldeywwsfamlo", "opobvtchezqnxpak",
	"pzfnegouvsrfgvro", "rzkcgpxdslzrdktu", "ksztdtqzxvhuryam",
	"ctnqnhkcooqipgkh", "pyqbbvrzdittqbgm", "koennvmolejeftij",
	"rvzlreqikqlgyczj", "xrnujfoyhonzkdgd", "mmsmhkxaiqupfjil",
	"ypjwoemqizddvyfd", "qgugcxnbhvgahykj", "cviodlsrtimbkgmy",
	"xbfbbechhmrjxhnw", "psuipaoucfczfxkp", "hdhwcpeuptgqqvim",
	"gsxlruhjeaareilr", "vgyqonnljuznyrhk", "eewezahlumervpyu",
	"iiolebrxfadtnigy", "tdadlrodykrdfscn", "ocvdtzjxrhtjurpo",
	"gidljbuvuovkhhrf", "qwfcpilbjwzboohd", "xzohxonlezuiupbg",
	"vslpbkkqgvgbcbix", "pivzqrzfxosbstzn", "fyqcfboevcqmbhhs",
	"yqsrneacnlxswojx", "heicqpxxyrwcbsjz", "yzynmnnoumkmlbeh",
	"bncadbjdvvmczylw", "hlnjskgfzbgmigfn", "fphpszymugpcykka",
	"zbifcktanxpmufvy", "saklpkhoyfeqbguy", "nqtqfcfxmpivnjyo",
	"locygrwerxlsvzqm", "qqflecydqvlogjme", "njklmixvgkzpgppf",
	"ugzkpjwjflaswyma", "lriousvkbeftslcy", "nsvsauxzfbbotgmh",
	"tblcpuhjyybrlica", "hqwshxcilwtmxrsf", "xojwroydfeoqupup",
	"tikuzsrogpnohpib", "layenyqgxdfggloc", "nqsvjvbrpuxkqvmq",
	"ivchgxkdlfjdzxmk", "uoghiuosiiwiwdws", "twsgsfzyszsfinlc",
	"waixcmadmhtqvcmd", "zkgitozgrqehtjkw", "xbkmyxkzqyktmpfi",
	"qlyapfmlybmatwxn", "ntawlvcpuaebuypf", "clhebxqdkcyndyof",
	"nrcxuceywiklpemc", "lmurgiminxpapzmq", "obalwqlkykzflxou",
	"huvcudpiryefbcye", "zlxbddpnyuyapach", "gqfwzfislmwzyegy",
	"jhynkjtxedmemlob", "hmrnvjodnsfiukex", "pstmikjykzyavfef",
	"wuwpnscrwzsyalyt", "hksvadripgdgwynm", "tvpfthzjleqfxwkh",
	"xpmrxxepkrosnrco", "qjkqecsnevlhqsly", "jjnrfsxzzwkhnwdm",
	"pehmzrzsjngccale", "bsnansnfxduritrr", "ejzxkefwmzmbxhlb",
	"pceatehnizeujfrs", "jtidrtgxopyeslzl", "sytaoidnamfwtqcr",
	"iabjnikomkgmyirr", "eitavndozoezojsi", "wtsbhaftgrbqfsmm",
	"vvusvrivsmhtfild", "qifbtzszfyzsjzyx", "ifhhjpaqatpbxzau",
	"etjqdimpyjxiuhty", "fvllmbdbsjozxrip", "tjtgkadqkdtdlkpi",
	"xnydmjleowezrecn", "vhcbhxqalroaryfn", "scgvfqsangfbhtay",
	"lbufpduxwvdkwhmb", "tshipehzspkhmdoi", "gtszsebsulyajcfl",
	"dlrzswhxajcivlgg", "kgjruggcikrfrkrw", "xxupctxtmryersbn",
	"hljjqfjrubzozxts", "giaxjhcwazrenjzs", "tyffxtpufpxylpye",
	"jfugdxxyfwkzqmgv", "kbgufbosjghahacw", "xpbhhssgegmthwxb",
	"npefofiharjypyzk", "velxsseyxuhrpycy", "sglslryxsiwwqzfw",
	"susohnlpelojhklv", "lfnpqfvptqhogdmk", "vtcrzetlekguqyle",
	"jlyggqdtamcjiuxn", "olxxqfgizjmvigvl", "cyypypveppxxxfuq",
	"hewmxtlzfqoqznwd", "jzgxxybfeqfyzsmp", "xzvvndrhuejnzesx",
	"esiripjpvtqqwjkv", "xnhrwhjtactofwrd", "knuzpuogbzplofqx",
	"tihycsdwqggxntqk", "xkfywvvugkdalehs", "cztwdivxagtqjjel",
	"dsaslcagopsbfioy", "gmowqtkgrlqjimbl", "ctcomvdbiatdvbsd",
	"gujyrnpsssxmqjhz", "nygeovliqjfauhjf", "mmgmcvnuppkbnonz",
	"bhipnkoxhzcotwel", "wkwpgedgxvpltqid", "mliajvpdocyzcbot",
	"kqjhsipuibyjuref", "zqdczykothbgxwsy", "koirtljkuqzxioaz",
	"audpjvhmqzvhzqas", "cxyhxlhntyidldfx", "iasgocejboxjgtkx",
	"abehujmqotwcufxp", "fmlrzqmazajxeedl", "knswpkekbacuxfby",
	"yvyalnvrxgstqhxm", "sjnrljfrfuyqfwuw", "ssaqruwarlvxrqzm",
	"iaxbpeqqzlcwfqjz", "uwyxshjutkanvvsc", "uxwrlwbblcianvnb",
	"nodtifgrxdojhneh", "mloxjfusriktxrms", "lkfzrwulbctupggc",
	"gcrjljatfhitcgfj", "tkdfxeanwskaivqs", "ypyjxqtmitwubbgt",
	"ssxbygzbjsltedjj", "zdrsnoorwqfalnha", "xlgmissaiqmowppd",
	"azhbwhiopwpguiuo", "fydlahgxtekbweet", "qtaveuqpifprdoiy",
	"kpubqyepxqleucem", "wlqrgqmnupwiuory", "rwyocktuqkuhdwxz",
	"abzjfsdevoygctqv", "zsofhaqqghncmzuw", "lqbjwjqxqbfgdckc",
	"bkhyxjkrqbbunido", "yepxfjnnhldidsjb", "builayfduxbppafc",
	"wedllowzeuswkuez", "gverfowxwtnvgrmo", "tpxycfumxdqgntwf",
	"lqzokaoglwnfcolw", "yqsksyheyspmcdqt", "vufvchcjjcltwddl",
	"saeatqmuvnoacddt", "dxjngeydvsjbobjs", "ucrcxoakevhsgcep",
	"cajgwjsfxkasbayt", "hknzmteafsfemwuv", "xxwhxwiinchqqudr",
	"usfenmavvuevevgr", "kxcobcwhsgyizjok", "vhqnydeboeunnvyk",
	"bgxbwbxypnxvaacw", "bwjzdypacwgervgk", "rrioqjluawwwnjcr",
	"fiaeyggmgijnasot", "xizotjsoqmkvhbzm", "uzphtrpxwfnaiidz",
	"kihppzgvgyoncptg", "hfbkfrxwejdeuwbz", "zgqthtuaqyrxicdy",
	"zitqdjnnwhznftze", "jnzlplsrwovxlqsn", "bmwrobuhwnwivpca",
	"uuwsvcdnoyovxuhn", "nmfvoqgoppoyosaj", "hxjkcppaisezygpe",
	"icvnysgixapvtoos", "vbvzajjgrmjygkhu", "jinptbqkyqredaos",
	"dpmknzhkhleawfvz", "ouwwkfhcedsgqqxe", "owroouiyptrijzgv",
	"bewnckpmnbrmhfyu", "evdqxevdacsbfbjb", "catppmrovqavxstn",
	"dqsbjibugjkhgazg", "mkcldhjochtnvvne", "sblkmhtifwtfnmsx",
	"lynnaujghehmpfpt", "vrseaozoheawffoq", "ytysdzbpbazorqes",
	"sezawbudymfvziff", "vrlfhledogbgxbau", "bipdlplesdezbldn",
	"ermaenjunjtbekeo", "eyaedubkthdecxjq", "gbzurepoojlwucuy",
	"rsiaqiiipjlouecx", "beqjhvroixhiemtw", "buzlowghhqbcbdwv",
	"ldexambveeosaimo", "fpyjzachgrhxcvnx", "komgvqejojpnykol",
	"fxebehjoxdujwmfu", "jnfgvheocgtvmvkx", "qmcclxxgnclkuspx",
	"rsbelzrfdblatmzu", "vexzwqjqrsenlrhm", "tnfbkclwetommqmh",
	"lzoskleonvmprdri", "nnahplxqscvtgfwi", "ubqdsflhnmiayzrp",
	"xtiyqxhfyqonqzrn", "omdtmjeqhmlfojfr", "cnimgkdbxkkcnmkb",
	"tapyijgmxzbmqnks", "byacsxavjboovukk", "awugnhcrygaoppjq",
	"yxcnwrvhojpuxehg", "btjdudofhxmgqbao", "nzqlfygiysfuilou",
	"nubwfjdxavunrliq", "vqxmmhsbmhlewceh", "ygavmcybepzfevrp",
	"kgflmrqsvxprkqgq", "iaqyqmcaedscmakk", "cvbojnbfmrawxzkh",
	"jjjrprbnlijzatuw", "lcsudrrfnnggbrmk", "qzgxbiavunawfibc",
	"gnnalgfvefdfdwwg", "nokmiitzrigxavsc", "etzoxwzxqkkhvais",
	"urxxfacgjccieufi", "lqrioqhuvgcotuec", "dydbaeyoypsbftra",
	"hhrotenctylggzaf", "evctqvzjnozpdxzu", "tbpvithmorujxlcp",
	"pllbtcbrtkfpvxcw", "fzyxdqilyvqreowv", "xdleeddxwvqjfmmt",
	"fcldzthqqpbswoin", "sgomzrpjfmvgwlzi", "axjyskmtdjbxpwoz",
	"hcvaevqxsmabvswh", "lfdlsfcwkwicizfk", "isjbwpzdognhoxvm",
	"oqnexibqxlyxpluh", "zqfbgodsfzwgcwuf", "kvmnwruwsjllbldz",
	"kghazimdyiyhmokj", "uiktgpsxpoahofxn", "zkdwawxargcmidct",
	"ftbixlyiprshrjup", "nofhmbxififwroeg", "mcdaqrhplffxrcdt",
	"fbjxnwojcvlawmlb", "rizoftvwfdhiwyac", "eduogrtyhxfwyars",
	"zoikunqxgjwfqqwr", "zxwbbpmvctzezaqh", "nghujwyeabwdqnop",
	"vcxamijpoyyksogn", "jnckdbuteoqlsdae", "jurfqqawafmsiqwv",
	"inepmztrzehfafie", "tznzkyvzodbrtscf", "xewbavjeppflwscl",
	"ucndzsorexjlnplo", "jpxbctscngxgusvu", "mfmygcllauzuoaok",
	"oibkuxhjmhxhhzby", "zjkslwagmeoisunw", "avnnxmopdgvmukuu",
	"jmaargejcwboqhkt", "yacmpeosarsrfkrv", "iqhgupookcaovwgh",
	"ebjkdnxwtikqzufc", "imdhbarytcscbsvb", "ifyibukeffkbqvcr",
	"aloighmyvwybtxhx", "yszqwrutbkiwkxjg", "xyholyzlltjhsuhp",
	"gykhmrwucneoxcrf", "badkdgqrpjzbabet", "sunaucaucykwtkjj",
	"pumqkglgfdhneero", "usgtyuestahlydxq", "xmfhflphzeudjsjm",
	"knywgmclisgpootg", "mtojnyrnvxtweuzb", "uuxufbwfegysabww",
	"vobhwwocqttlbsik", "yuydfezeqgqxqmnd", "wbqgqkwbibiilhzc",
	"sfdmgxsbuzsawush", "ilhbxcfgordyxwvp", "ahqoavuysblnqaeg",
	"plwgtvpgotskmsey", "ewjcmzkcnautrrmp", "tyekgzbznlikcyqj",
	"bqzctiuaxpriuiga", "bimvbfjkiupyqiys", "mpqtbcxfhwymxncw",
	"htemlptvqhharjgb", "mqbsmsruwzzxgcxc", "zjyedjwhnvteuaid",
	"pzoelkoidwglpttc", "efydnsvlfimvwxhx", "gfyhgoeiyjcgfyze",
	"deqtomhwopmzvjlt", "casafubtkoopuaju", "yylsfarntbucfulg",
	"mgjwsormkjsrrxan", "lkkenpupgmjpnqqd", "tegweszyohsoluot",
	"lihsfdwxmxvwdxna", "rrefrjjxerphejwb", "guuazonjoebhymtm",
	"ysofqzmfmyneziki", "lmjgaliatcpduoal", "qzthcpjwtgahbebr",
	"wvakvephyukmpemm", "simxacxxzfoaeddw", "aetgqmiqzxbvbviz",
	"jxlmhdmqggevrxes", "mmuglnjmuddzgaik", "svopsqhtrslgycgc",
	"xnvcsiiqrcjkvecn", "kkvumxtvashxcops", "bduflsdyeectvcgl",
	"vfrxbwmmytjvqnsj", "eeqtdneiyiaiofxw", "crtbgknfacjtwkfl",
	"uuutuoxdsxolpbhd", "lcrztwzreaswovtn", "htorkvnvujmjdqzj",
	"wttzuzvrzlyhfzyf", "oraewznfwgdsnhuk", "rctlkqqvkwbgrcgk",
	"cfehrsrqhzyiwtmz", "kbvxwcumjkhvjpui", "xxlocexbmniiakfo",
	"gtknkkzvykmlqghl", "kcjuxvkuimhwqrtk", "vohekwkuyuoacuww",
	"vorctgughscysyfo", "zmjevqplngzswxyq", "qhswdrhrijnatkyo",
	"joakcwpfggtitizs", "juzlwjijcmtswdtq", "icbyaqohpkemhkip",
	"rpdxgpzxncedmvzh", "rozkmimbqhbhcddv", "wkkypomlvyglpfpf",
	"jcaqyaqvsefwtaya", "ghvmtecoxlebdwnf", "lqrcyiykkkpkxvqt",
	"eqlarfazchmzotev", "vqwndafvmpguggef", "dbfxzrdkkrusmdke",
	"cmjpjjgndozcmefj", "hbrdcwjuyxapyhlo", "mmforetykbosdwce",
	"zynfntqwblbnfqik", "sodwujfwlasznaiz", "yyvrivjiqnxzqkfp",
	"uldbskmmjbqllpnm", "fyhhrmrsukeptynl", "hpfjekktvdkgdkzl",
	"bozhkoekcxzeorob", "uvpptyfrzkvmtoky", "hkhfprmjdpjvfkcb",
	"igxzwktwsqhsivqu", "qceomwysgkcylipb", "cglateoynluyeqgc",
	"xcsdfkpeguxgvpfh", "owjhxlcncdgkqyia", "rpbmrpcesiakqpna",
	"lueszxiourxsmezb", "zelvsowimzkxliwc", "vzxbttoobtvdtkca",
	"pfxvzphzwscqkzsi", "edsjorainowytbzu", "ipsegdaluoiphmnz",
	"mkhueokfpemywvuw", "urxdnumhylpafdlc", "ggluurzavsxkvwkl",
	"ctclphidqgteakox", "tfobosynxsktajuk", "jzrmemhxqmzhllif",
	"eemwekimdfvqslsx", "yjkwpzrbanoaajgq", "rlxghzanuyeimfhx",
	"hozbgdoorhthlqpv", "obkbmflhyanxilnx", "xojrippyxjmpzmsz",
	"ukykmbfheixuviue", "qivlmdexwucqkres", "rmyxxipqkarpjmox",
	"fgaftctbvcvnrror", "raawxozucfqvasru", "dinpjbdfjfizexdh",
	"gybxubwnnbuyvjcr", "qrqitdvyoneqyxcg", "jqzcfggayzyoqteo",
	"cikqpvxizpdbmppm", "stfpldgyhfmucjjv", "slzbcuihmimpduri",
	"aufajwfrsorqqsnl", "iylmzraibygmgmqj", "lcdyfpcqlktudfmu",
	"pmomzzsdpvgkkliw", "zpplirgtscfhbrkj", "mvhyerxfiljlotjl",
	"ofkvrorwwhusyxjx", "xngzmvcgkqfltjpe", "yxfxaqipmysahqqq",
	"sdqafdzgfdjuabup", "qcqajmerahcdgxfv", "xqimrqtupbapawro",
	"qfvkqwidzzrehsbl", "himixxvueksiqfdf", "vgtfqpuzxxmhrvvd",
	"adiioqeiejguaost", "jnzxuycjxvxehbvm", "xedbpxdhphamoodk",
	"jsrioscmwlsfuxrg", "mtsynnfxunuohbnf", "enamqzfzjunnnkpe",
	"uwcvfecunobyhces", "ciygixtgbsccpftq", "ewjgcronizkcsfjy",
	"wztjkoipxsikoimv", "jrgalyvfelwxforw", "imylyalawbqwkrwb",
	"yflwqfnuuvgjsgcj", "wkysyzusldlojoue", "zopllxnidcffcuau",
	"bscgwxuprxaerskj", "zvnvprxxjkhnkkpq", "nejwxbhjxxdbenid",
	"chryiccsebdbcnkc", "guoeefaeafhlgvxh", "nzapxrfrrqhsingx",
	"mkzvquzvqvwsejqs", "kozmlmbchydtxeeo", "keylygnoqhmfzrfp",
	"srwzoxccndoxylxe", "uqjzalppoorosxxo", "potmkinyuqxsfdfw",
	"qkkwrhpbhypxhiun", "wgfvnogarjmdbxyh", "gkidtvepcvxopzuf",
	"atwhvmmdvmewhzty", "pybxizvuiwwngqej", "zfumwnazxwwxtiry",
	"keboraqttctosemx", "vtlzxaqdetbhclib", "wjiecykptzexuayl",
	"ejatfnyjjdawepyk", "mpcrobansyssvmju", "gqukndzganeueabm",
	"ukzscvomorucdnqd", "wfydhtbzehgwfazx", "mtwqdzlephqvxqmx",
	"dltmlfxbjopefibh", "atcfrowdflluqtbi", "vowawlophlxaqonw",
	"vblgdjzvwnocdipw", "uzerzksmkvnlvlhm", "ytjwhpaylohorvxd",
	"siprvfxvnxcdgofz", "cbhjupewcyjhvtgs", "apqtozaofusmfqli",
	"tmssrtlxfouowqnr", "ntutrvwnzzgmokes", "zrsgpwdzokztdpis",
	"nrobvmsxtfmrqdhv", "kadkaftffaziqdze", "yrovbgcyqtlsnoux",
	"modheiwuhntdecqs", "gzhjypwddizemnys", "gaputpwpcsvzxjho",
	"bgmouxwoajgaozau", "oxuapfrjcpyakiwt", "kntwbvhuaahdixzj",
	"epqjdjbnkxdnaccx", "dspltdvznhypykri", "tdrgqmbnagrxdwtt",
	"njfqawzjggmemtbg", "chpemsgwpzjpdnkk", "fpsrobmbqbmigmwk",
	"flxptsrqaazmprnl", "nzdunrxlcbfklshm", "miuwljvtkgzdlbnn",
	"xbhjakklmbhsdmdt", "xwxhsbnrwnegwcov", "pwosflhodjaiexwq",
	"fhgepuluczttfvqh", "tldxcacbvxyamvkt", "gffxatrjglkcehim",
	"tzotkdrpxkucsdps", "wxheftdepysvmzbe", "qfooyczdzoewrmku",
	"rvlwikuqdbpjuvoo", "bcbrnbtfrdgijtzt", "vaxqmvuogsxonlgq",
	"ibsolflngegravgo", "txntccjmqakcoorp", "vrrbmqaxfbarmlmc",
	"dzspqmttgsuhczto", "pikcscjunxlwqtiw", "lwzyogwxqitqfqlv",
	"gsgjsuaqejtzglym", "feyeqguxbgmcmgpp", "gmttebyebdwvprkn",
	"mzuuwbhzdjfdryxu", "fganrbnplymqbzjx", "cvsrbdcvhtxxdmro",
	"scmgkjlkqukoamyp", "fkgrqbyqpqcworqc", "hjsrvkdibdjarxxb",
	"sztzziuqroeidcus", "pxdfvcpvwaddrzwv", "phdqqxleqdjfgfbg",
	"cqfikbgxvjmnfncy"};

bool is_vowel(const char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool d5_strings(const char *str)
{
	int vowels = 0;
	int twiceInARow = 0;
	const char *filterOut[] = {"ab", "cd", "pq", "xy"};
	while (*(str + 1))
	{
		for (int i = 0; i < (int)ARRAY_COUNT(filterOut); ++i)
		{
			if (filterOut[i][0] == *str && filterOut[i][1] == *(str + 1))
				return false;
		}
		if (is_vowel(*str))
		{
			++vowels;
		}
		if (*str == *(str + 1))
		{
			++twiceInARow;
		}
		++str;
	}
	if (is_vowel(*str))
		++vowels;
	return vowels >= 3 && twiceInARow >= 1;
}

bool d5_strings_p2(const char *str)
{
	int rule1 = 0;
	int rule2 = 0;
	char poc = '\0';
	std::map<char, std::set<char>> ngrams;
	while (*(str + 1))
	{
		char c0 = *(str++);
		char c1 = *(str);
		// We only check the rules if the [c0][c1]['c2'] c2 is not out of bounds.
		if (c1 != '\0')
		{
			// Ngram of c0 is only valid if it doesnt overlap.
			if (c0 == c1 && c0 == poc)
			{
				poc = '\0';
				// } else if(std::find(ngrams[c0].begin(), ngrams[c0].end(), c1) !=
				// ngrams[c0].end()) {
			}
			else if (ngrams[c0].find(c1) != ngrams[c0].end())
			{
				++rule1;
			}
			else
			{
				ngrams[c0].insert(c1);
				poc = c0;
			}
			// Rule 2:
			if (c0 == *(str + 1))
			{
				++rule2;
			}
		}
	}
	return rule1 >= 1 && rule2 >= 1;
}

#include <bitset>
void d6_lights()
{
	constexpr size_t totalBits = 1000*1000;
	std::bitset<totalBits> lights;
	for(int i = 0; i < totalBits; ++i) {
		lights.set(i);
	}
	auto lightsOn = lights.count();
	auto lightsOff = totalBits - lightsOn;
}

int main(int, char **)
{
	int puzzleId = 6;
	switch (puzzleId)
	{
	case 3:
		CHECK_VALUE(d3p1_house_delivery(d3_paths[0], 1), d3_ans[0][0]);
		CHECK_VALUE(d3p1_house_delivery(d3_paths[1], 1), d3_ans[0][1]);
		CHECK_VALUE(d3p1_house_delivery(d3_paths[2], 1), d3_ans[0][2]);
		CHECK_VALUE(d3p1_house_delivery(d3_paths[4], 2), d3_ans[1][0]);
		CHECK_VALUE(d3p1_house_delivery(d3_paths[1], 2), d3_ans[1][1]);
		CHECK_VALUE(d3p1_house_delivery(d3_paths[2], 2), d3_ans[1][2]);
		std::cout << "P1 Ans: " << d3p1_house_delivery(d3_paths[3], 1) << std::endl;
		std::cout << "P2 Ans: " << d3p1_house_delivery(d3_paths[3], 2) << std::endl;
		break;
	case 4:
		// md5_zeros_hash("hello world");
		// CHECK_VALUE(md5_zeros_hash(d4_words[0]), d4_ans[0]);
		// CHECK_VALUE(md5_zeros_hash(d4_words[1]), d4_ans[1]);
		std::cout << "P1 Ans:" << md5_zeros_hash(d4_words[2]) << std::endl;
		break;
	case 5:
		for (int i = 0; i < (int)ARRAY_COUNT(d5_ans); ++i)
			CHECK_VALUE(d5_strings(d5_words[i]), d5_ans[i]);

		for (int i = 0; i < (int)ARRAY_COUNT(d5_ans_p2); ++i)
			CHECK_VALUE(d5_strings_p2(d5_words_p2[i]), d5_ans_p2[i]);
		{
			int result = 0;
			for (int i = 0; i < (int)ARRAY_COUNT(d5_input); ++i)
			{
				if (d5_strings(d5_input[i]))
				{
					++result;
				}
			}
			std::cout << "P1 Ans: " << result << std::endl;
		}
		{
			int result = 0;
			for (int i = 0; i < (int)ARRAY_COUNT(d5_input); ++i)
			{
				if (d5_strings_p2(d5_input[i]))
				{
					++result;
				}
			}
			std::cout << "P2 Ans: " << result << std::endl;
		}
		break;
	case 6:
	{
		d6_lights();
	}
	break;
	default:
		std::cout << "Failure in finding puzzleID: " << puzzleId << std::endl;
		break;
	}

	return 0;
}
