/*========================================================================
	Creator: Grimleik $
========================================================================*/

#include "d6.h"
#include <bitset>
#include <charconv>

void d6::parse(const std::string_view &input, std::vector<d6_instruction> &out)
{
	std::vector<std::string_view> splits = split_string_view(input, '\n');
	out.resize(splits.size());
	for (int i = 0; i < splits.size(); ++i)
	{
		const char *str = splits[i].data();
		d6_instruction &instruction = out[i];
		int idx = 0;
		if (splits[i].starts_with("turn on"))
		{
			instruction.type = TURN_ON;
			idx = 8;
		}
		else if (splits[i].starts_with("turn off"))
		{
			instruction.type = TURN_OFF;
			idx = 9;
		}
		else if (splits[i].starts_with("toggle"))
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
}

int d6::solution(const std::string_view &sv, const std::function<int(const std::vector<d6_instruction> &)> &func)
{
	std::vector<d6_instruction> instructions;
	parse(sv, instructions);
	return func(instructions);
}

d6::d6()
{
	input_file = read_entire_file("../../../../2015/input/d6.in");
	input.push_back(std::make_pair(std::string_view(input_file->mem), std::make_pair(400410, 15343601)));
}

bool d6::run()
{
	auto p1 = [](const std::vector<d6_instruction> &instructions)
	{
		constexpr size_t totalBits = 1000 * 1000;
		std::vector<int> lights(totalBits, 0);
		for (auto &inst : instructions)
		{
			switch (inst.type)
			{
			case TURN_ON:
			{
				for (int y = inst.y0; y <= inst.y1; ++y)
				{
					std::fill(lights.begin() + y * 1000 + inst.x0, lights.begin() + y * 1000 + inst.x1 + 1, 1);
				}
			}
			break;
			case TURN_OFF:
			{
				for (int y = inst.y0; y <= inst.y1; ++y)
				{
					std::fill(lights.begin() + y * 1000 + inst.x0, lights.begin() + y * 1000 + inst.x1 + 1, 0);
				}
			}
			break;
			case TOGGLE:
			{
				for (int y = inst.y0; y <= inst.y1; ++y)
				{
					// TODO: Better way of doing this?
					for (int x = inst.x0; x <= inst.x1; ++x)
					{
						lights[y * 1000 + x] = !lights[y * 1000 + x];
					}
				}
			}
			break;
			default:
				break;
			}
		}

		long long brightness = 0; // std::accumulate(lights.begin(), lights.end(), 0);
		for (auto &b : lights)
		{
			brightness += b;
		}
#ifdef DUMP_PIXELS
		u32 *pixels = new u32[totalBits];
		for (int i = 0; i < totalBits; ++i)
		{
			int brightness = lights[i];
			u32 value = (brightness << 16) | (brightness << 8) | brightness;
			pixels[i] = value * 255;
		}

		save_bmp("out_1.bmp", 1000, 1000, pixels);
		delete[] pixels;
#endif
		return (int)brightness;
	};

	auto p2 = [](const std::vector<d6_instruction> &instructions)
	{
		constexpr size_t totalBits = 1000 * 1000;
		std::vector<int> lights(totalBits, 0);
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
		}

		long long brightness = 0;
		for (auto &b : lights)
		{
			brightness += b;
		}
#ifdef DUMP_PIXELS
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

		save_bmp("out_2.bmp", 1000, 1000, pixels);
		delete[] pixels;
#endif
		return (int)brightness;
	};

	for (auto &t : input)
		CHECK_TEST(solution, t.first, t.second.first, p1);

	for (auto &t : input)
		CHECK_TEST(solution, t.first, t.second.second, p2);

	return true;
}
