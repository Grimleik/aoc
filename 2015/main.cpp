#include <algorithm>
#include <assert.h>
#include <chrono>
#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
// #include <openssl/md5.h>
#include <ratio>
#include <set>
#include <utility>
#include <vector>
#include <fstream>

typedef uint8_t u8;
typedef uint32_t u32;

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

inline void save_bmp(const char *filename, int width, int height, u32 *buffer)
{
	int filesize = 54 + width * 4 * height;
	u8 bmpheader[14] = {
		'B', 'M', filesize, filesize >> 8, filesize >> 16, filesize >> 24,
		0, 0, 0, 0, 54, 0, 0, 0};

	u8 bmpinfoheader[40] = {
		40, 0, 0, 0,
		width, width >> 8, width >> 16, width >> 24,
		height, height >> 8, height >> 16, height >> 24,
		1, 0, 32, 0};

	std::ofstream out(filename, std::ios::binary);
	out.write((char *)bmpheader, ARRAY_COUNT(bmpheader));
	out.write((char *)bmpinfoheader, ARRAY_COUNT(bmpinfoheader));

	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			u32 color = buffer[(y * width + x)];
			char A = /*color >> 24*/ 127, R = (color >> 16) & 255, G = (color >> 8) & 255, B = (color) & 255;
			out.write(&B, 1);
			out.write(&G, 1);
			out.write(&R, 1);
			out.write(&A, 1);
		}
	}
}

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

// int md5_zeros_hash(const char *msg)
// {
// 	//   int a0 = 0x67452301;
// 	//   int b0 = 0xefcdab89;
// 	//   int c0 = 0x98badcfe;
// 	//   int d0 = 0x10325476;
// 	int nbr = 0;
// 	std::string input(msg);
// 	// auto start = std::chrono::high_resolution_clock::now();
// 	unsigned char md[MD5_DIGEST_LENGTH];
// 	while (nbr < INT_MAX)
// 	{
// 		input = msg + std::to_string(nbr);
// 		MD5((const unsigned char *)(input.c_str()), input.size(), md);
// 		if ((int)md[0] == 0 && (int)md[1] == 0 && (int)md[2] == 0)
// 			break;
// 		// if(!(nbr % 10000)) {
// 		// 	auto end = std::chrono::high_resolution_clock::now();
// 		// 	std::cout << nbr << " Done, time elapsed: " <<
// 		// std::chrono::duration_cast<std::chrono::milliseconds>(end -
// 		// start).count() << "." << std::endl; 	start = end;
// 		// }
// 		// std::cout << "MD5(" << msg << ") = ";
// 		// for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
// 		//   std::cout << std::hex << std::setw(2) << std::setfill('0') <<
// 		//   (int)md[i];
// 		// }
// 		// std::cout << std::endl;
// 		++nbr;
// 	}
// 	return nbr;
// }

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

const char *d6_test[] = {
	"turn on 0,0 through 999,999",
	"toggle 0,0 through 999,0",
	"turn off 499,499 through 500,500",
};

const char *d6_input[] = {
	"turn off 660,55 through 986,197",
	"turn off 341,304 through 638,850",
	"turn off 199,133 through 461,193",
	"toggle 322,558 through 977,958",
	"toggle 537,781 through 687,941",
	"turn on 226,196 through 599,390",
	"turn on 240,129 through 703,297",
	"turn on 317,329 through 451,798",
	"turn on 957,736 through 977,890",
	"turn on 263,530 through 559,664",
	"turn on 158,270 through 243,802",
	"toggle 223,39 through 454,511",
	"toggle 544,218 through 979,872",
	"turn on 313,306 through 363,621",
	"toggle 173,401 through 496,407",
	"toggle 333,60 through 748,159",
	"turn off 87,577 through 484,608",
	"turn on 809,648 through 826,999",
	"toggle 352,432 through 628,550",
	"turn off 197,408 through 579,569",
	"turn off 1,629 through 802,633",
	"turn off 61,44 through 567,111",
	"toggle 880,25 through 903,973",
	"turn on 347,123 through 864,746",
	"toggle 728,877 through 996,975",
	"turn on 121,895 through 349,906",
	"turn on 888,547 through 931,628",
	"toggle 398,782 through 834,882",
	"turn on 966,850 through 989,953",
	"turn off 891,543 through 914,991",
	"toggle 908,77 through 916,117",
	"turn on 576,900 through 943,934",
	"turn off 580,170 through 963,206",
	"turn on 184,638 through 192,944",
	"toggle 940,147 through 978,730",
	"turn off 854,56 through 965,591",
	"toggle 717,172 through 947,995",
	"toggle 426,987 through 705,998",
	"turn on 987,157 through 992,278",
	"toggle 995,774 through 997,784",
	"turn off 796,96 through 845,182",
	"turn off 451,87 through 711,655",
	"turn off 380,93 through 968,676",
	"turn on 263,468 through 343,534",
	"turn on 917,936 through 928,959",
	"toggle 478,7 through 573,148",
	"turn off 428,339 through 603,624",
	"turn off 400,880 through 914,953",
	"toggle 679,428 through 752,779",
	"turn off 697,981 through 709,986",
	"toggle 482,566 through 505,725",
	"turn off 956,368 through 993,516",
	"toggle 735,823 through 783,883",
	"turn off 48,487 through 892,496",
	"turn off 116,680 through 564,819",
	"turn on 633,865 through 729,930",
	"turn off 314,618 through 571,922",
	"toggle 138,166 through 936,266",
	"turn on 444,732 through 664,960",
	"turn off 109,337 through 972,497",
	"turn off 51,432 through 77,996",
	"turn off 259,297 through 366,744",
	"toggle 801,130 through 917,544",
	"toggle 767,982 through 847,996",
	"turn on 216,507 through 863,885",
	"turn off 61,441 through 465,731",
	"turn on 849,970 through 944,987",
	"toggle 845,76 through 852,951",
	"toggle 732,615 through 851,936",
	"toggle 251,128 through 454,778",
	"turn on 324,429 through 352,539",
	"toggle 52,450 through 932,863",
	"turn off 449,379 through 789,490",
	"turn on 317,319 through 936,449",
	"toggle 887,670 through 957,838",
	"toggle 671,613 through 856,664",
	"turn off 186,648 through 985,991",
	"turn off 471,689 through 731,717",
	"toggle 91,331 through 750,758",
	"toggle 201,73 through 956,524",
	"toggle 82,614 through 520,686",
	"toggle 84,287 through 467,734",
	"turn off 132,367 through 208,838",
	"toggle 558,684 through 663,920",
	"turn on 237,952 through 265,997",
	"turn on 694,713 through 714,754",
	"turn on 632,523 through 862,827",
	"turn on 918,780 through 948,916",
	"turn on 349,586 through 663,976",
	"toggle 231,29 through 257,589",
	"toggle 886,428 through 902,993",
	"turn on 106,353 through 236,374",
	"turn on 734,577 through 759,684",
	"turn off 347,843 through 696,912",
	"turn on 286,699 through 964,883",
	"turn on 605,875 through 960,987",
	"turn off 328,286 through 869,461",
	"turn off 472,569 through 980,848",
	"toggle 673,573 through 702,884",
	"turn off 398,284 through 738,332",
	"turn on 158,50 through 284,411",
	"turn off 390,284 through 585,663",
	"turn on 156,579 through 646,581",
	"turn on 875,493 through 989,980",
	"toggle 486,391 through 924,539",
	"turn on 236,722 through 272,964",
	"toggle 228,282 through 470,581",
	"toggle 584,389 through 750,761",
	"turn off 899,516 through 900,925",
	"turn on 105,229 through 822,846",
	"turn off 253,77 through 371,877",
	"turn on 826,987 through 906,992",
	"turn off 13,152 through 615,931",
	"turn on 835,320 through 942,399",
	"turn on 463,504 through 536,720",
	"toggle 746,942 through 786,998",
	"turn off 867,333 through 965,403",
	"turn on 591,477 through 743,692",
	"turn off 403,437 through 508,908",
	"turn on 26,723 through 368,814",
	"turn on 409,485 through 799,809",
	"turn on 115,630 through 704,705",
	"turn off 228,183 through 317,220",
	"toggle 300,649 through 382,842",
	"turn off 495,365 through 745,562",
	"turn on 698,346 through 744,873",
	"turn on 822,932 through 951,934",
	"toggle 805,30 through 925,421",
	"toggle 441,152 through 653,274",
	"toggle 160,81 through 257,587",
	"turn off 350,781 through 532,917",
	"toggle 40,583 through 348,636",
	"turn on 280,306 through 483,395",
	"toggle 392,936 through 880,955",
	"toggle 496,591 through 851,934",
	"turn off 780,887 through 946,994",
	"turn off 205,735 through 281,863",
	"toggle 100,876 through 937,915",
	"turn on 392,393 through 702,878",
	"turn on 956,374 through 976,636",
	"toggle 478,262 through 894,775",
	"turn off 279,65 through 451,677",
	"turn on 397,541 through 809,847",
	"turn on 444,291 through 451,586",
	"toggle 721,408 through 861,598",
	"turn on 275,365 through 609,382",
	"turn on 736,24 through 839,72",
	"turn off 86,492 through 582,712",
	"turn on 676,676 through 709,703",
	"turn off 105,710 through 374,817",
	"toggle 328,748 through 845,757",
	"toggle 335,79 through 394,326",
	"toggle 193,157 through 633,885",
	"turn on 227,48 through 769,743",
	"toggle 148,333 through 614,568",
	"toggle 22,30 through 436,263",
	"toggle 547,447 through 688,969",
	"toggle 576,621 through 987,740",
	"turn on 711,334 through 799,515",
	"turn on 541,448 through 654,951",
	"toggle 792,199 through 798,990",
	"turn on 89,956 through 609,960",
	"toggle 724,433 through 929,630",
	"toggle 144,895 through 201,916",
	"toggle 226,730 through 632,871",
	"turn off 760,819 through 828,974",
	"toggle 887,180 through 940,310",
	"toggle 222,327 through 805,590",
	"turn off 630,824 through 885,963",
	"turn on 940,740 through 954,946",
	"turn on 193,373 through 779,515",
	"toggle 304,955 through 469,975",
	"turn off 405,480 through 546,960",
	"turn on 662,123 through 690,669",
	"turn off 615,238 through 750,714",
	"turn on 423,220 through 930,353",
	"turn on 329,769 through 358,970",
	"toggle 590,151 through 704,722",
	"turn off 884,539 through 894,671",
	"toggle 449,241 through 984,549",
	"toggle 449,260 through 496,464",
	"turn off 306,448 through 602,924",
	"turn on 286,805 through 555,901",
	"toggle 722,177 through 922,298",
	"toggle 491,554 through 723,753",
	"turn on 80,849 through 174,996",
	"turn off 296,561 through 530,856",
	"toggle 653,10 through 972,284",
	"toggle 529,236 through 672,614",
	"toggle 791,598 through 989,695",
	"turn on 19,45 through 575,757",
	"toggle 111,55 through 880,871",
	"turn off 197,897 through 943,982",
	"turn on 912,336 through 977,605",
	"toggle 101,221 through 537,450",
	"turn on 101,104 through 969,447",
	"toggle 71,527 through 587,717",
	"toggle 336,445 through 593,889",
	"toggle 214,179 through 575,699",
	"turn on 86,313 through 96,674",
	"toggle 566,427 through 906,888",
	"turn off 641,597 through 850,845",
	"turn on 606,524 through 883,704",
	"turn on 835,775 through 867,887",
	"toggle 547,301 through 897,515",
	"toggle 289,930 through 413,979",
	"turn on 361,122 through 457,226",
	"turn on 162,187 through 374,746",
	"turn on 348,461 through 454,675",
	"turn off 966,532 through 985,537",
	"turn on 172,354 through 630,606",
	"turn off 501,880 through 680,993",
	"turn off 8,70 through 566,592",
	"toggle 433,73 through 690,651",
	"toggle 840,798 through 902,971",
	"toggle 822,204 through 893,760",
	"turn off 453,496 through 649,795",
	"turn off 969,549 through 990,942",
	"turn off 789,28 through 930,267",
	"toggle 880,98 through 932,434",
	"toggle 568,674 through 669,753",
	"turn on 686,228 through 903,271",
	"turn on 263,995 through 478,999",
	"toggle 534,675 through 687,955",
	"turn off 342,434 through 592,986",
	"toggle 404,768 through 677,867",
	"toggle 126,723 through 978,987",
	"toggle 749,675 through 978,959",
	"turn off 445,330 through 446,885",
	"turn off 463,205 through 924,815",
	"turn off 417,430 through 915,472",
	"turn on 544,990 through 912,999",
	"turn off 201,255 through 834,789",
	"turn off 261,142 through 537,862",
	"turn off 562,934 through 832,984",
	"turn off 459,978 through 691,980",
	"turn off 73,911 through 971,972",
	"turn on 560,448 through 723,810",
	"turn on 204,630 through 217,854",
	"turn off 91,259 through 611,607",
	"turn on 877,32 through 978,815",
	"turn off 950,438 through 974,746",
	"toggle 426,30 through 609,917",
	"toggle 696,37 through 859,201",
	"toggle 242,417 through 682,572",
	"turn off 388,401 through 979,528",
	"turn off 79,345 through 848,685",
	"turn off 98,91 through 800,434",
	"toggle 650,700 through 972,843",
	"turn off 530,450 through 538,926",
	"turn on 428,559 through 962,909",
	"turn on 78,138 through 92,940",
	"toggle 194,117 through 867,157",
	"toggle 785,355 through 860,617",
	"turn off 379,441 through 935,708",
	"turn off 605,133 through 644,911",
	"toggle 10,963 through 484,975",
	"turn off 359,988 through 525,991",
	"turn off 509,138 through 787,411",
	"toggle 556,467 through 562,773",
	"turn on 119,486 through 246,900",
	"turn on 445,561 through 794,673",
	"turn off 598,681 through 978,921",
	"turn off 974,230 through 995,641",
	"turn off 760,75 through 800,275",
	"toggle 441,215 through 528,680",
	"turn off 701,636 through 928,877",
	"turn on 165,753 through 202,780",
	"toggle 501,412 through 998,516",
	"toggle 161,105 through 657,395",
	"turn on 113,340 through 472,972",
	"toggle 384,994 through 663,999",
	"turn on 969,994 through 983,997",
	"turn on 519,600 through 750,615",
	"turn off 363,899 through 948,935",
	"turn on 271,845 through 454,882",
	"turn off 376,528 through 779,640",
	"toggle 767,98 through 854,853",
	"toggle 107,322 through 378,688",
	"turn off 235,899 through 818,932",
	"turn on 445,611 through 532,705",
	"toggle 629,387 through 814,577",
	"toggle 112,414 through 387,421",
	"toggle 319,184 through 382,203",
	"turn on 627,796 through 973,940",
	"toggle 602,45 through 763,151",
	"turn off 441,375 through 974,545",
	"toggle 871,952 through 989,998",
	"turn on 717,272 through 850,817",
	"toggle 475,711 through 921,882",
	"toggle 66,191 through 757,481",
	"turn off 50,197 through 733,656",
	"toggle 83,575 through 915,728",
	"turn on 777,812 through 837,912",
	"turn on 20,984 through 571,994",
	"turn off 446,432 through 458,648",
	"turn on 715,871 through 722,890",
	"toggle 424,675 through 740,862",
	"toggle 580,592 through 671,900",
	"toggle 296,687 through 906,775"};

#include <bitset>

enum d6_instruction_type
{
	TURN_ON,
	TURN_OFF,
	TOGGLE,
};

struct d6_instruction
{
	d6_instruction_type type;
	int x0, y0, x1, y1;
};

#include <charconv>
#include <string_view>
void d6_lights(const char **input, const int len)
{
	constexpr size_t totalBits = 1000 * 1000;
	std::vector<int> lights(totalBits, 0);
	std::vector<d6_instruction> instructions(len);
	for (int i = 0; i < len; ++i)
	{
		const char *str = input[i];
		d6_instruction &instruction = instructions[i];
		int idx = 0;
		if (strstr(str, "turn on"))
		{
			instruction.type = TURN_ON;
			idx = 8;
		}
		else if (strstr(str, "turn off"))
		{
			instruction.type = TURN_OFF;
			idx = 9;
		}
		else if (strstr(str, "toggle"))
		{
			instruction.type = TOGGLE;
			idx = 7;
		}
		else
		{
			std::cout << "Unknown command: " << str << std::endl;
			continue;
		}

		const char *p = str + idx;
		while (*p != ',')
			++p;
		std::string_view sv0(str + idx, p - (str + idx));
		std::from_chars(sv0.data(), sv0.data() + sv0.size(), instruction.x0);

		str = p + 1;
		while (*p != ' ')
			++p;
		std::string_view sv1(str, p - str);
		std::from_chars(sv1.data(), sv1.data() + sv1.size(), instruction.y0);
		++p;
		str = p;
		while (*p != ' ')
			++p;

		str = p + 1;
		while (*p != ',')
			++p;
		std::string_view sv2(str, p - str);
		std::from_chars(sv2.data(), sv2.data() + sv2.size(), instruction.x1);
		str = p + 1;
		while (*p != '\0')
			++p;
		std::string_view sv3(str, p - str);
		std::from_chars(sv3.data(), sv3.data() + sv3.size(), instruction.y1);
	}

	for (auto &inst : instructions)
	{
		switch (inst.type)
		{
		case TURN_ON:
		{
			for (int y = inst.y0; y <= inst.y1; ++y)
			{
				for (int x = inst.x0; x <= inst.x1; ++x)
				{
					lights[y * 1000 + x]++;
				}
			}
		}
		break;
		case TURN_OFF:
		{
			for (int y = inst.y0; y <= inst.y1; ++y)
			{
				for (int x = inst.x0; x <= inst.x1; ++x)
				{
					lights[y * 1000 + x] = std::max(lights[y * 1000 + x] - 1, 0);
				}
			}
		}
		break;
		case TOGGLE:
		{
			for (int y = inst.y0; y <= inst.y1; ++y)
			{
				for (int x = inst.x0; x <= inst.x1; ++x)
				{
					lights[y * 1000 + x] += 2;
				}
			}
		}
		break;
		default:
			break;
		}
		long long brighntess = 0;
		for (auto &b : lights)
		{
			brighntess += b;
		}
		std::cout << "Lights brightness: " << brighntess << std::endl;
	}

	u32 *pixels = new u32[totalBits];
	for (int i = 0; i < totalBits; ++i)
	{
		int brightness = lights[i];
		u32 value = (brightness << 16) | (brightness << 8) | brightness;
		pixels[i] = value;
		assert(((pixels[i] >> 16) & 255) == brightness);
		assert(((pixels[i] >> 8) & 255) == brightness);
		assert(((pixels[i] >> 0) & 255) == brightness);
	}

	save_bmp("out.bmp", 1000, 1000, pixels);
	delete pixels;
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
		// std::cout << "P1 Ans:" << md5_zeros_hash(d4_words[2]) << std::endl;
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
		// d6_lights(d6_test, ARRAY_COUNT(d6_test));
		d6_lights(d6_input, ARRAY_COUNT(d6_input));
	}
	break;
	default:
		std::cout << "Failure in finding puzzleID: " << puzzleId << std::endl;
		break;
	}

	return 0;
}
