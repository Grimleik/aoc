#if !defined(UTILS_H)
/*========================================================================
	Creator: Grimleik $
========================================================================*/
#define UTILS_H
#include "pch.h"
// #define VERBOSE

typedef uint8_t u8;
typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

#define ARRAY_COUNT(x) ((sizeof(x)) / (sizeof(x[0])))

#define CHECK_VALUE(x, y)                                                      \
	do                                                                         \
	{                                                                          \
		if (x != y)                                                            \
		{                                                                      \
			std::cout << "Value is: " << x << " expected: " << y << std::endl; \
			return false;                                                      \
		}                                                                      \
	} while (false);

#ifdef VERBOSE
#define CHECK_TEST(func, input, output)                                                                       \
	{                                                                                                         \
		auto check_output = func(input);                                                                      \
		if (check_output != output)                                                                           \
		{                                                                                                     \
			std::cout << std::format("\tFAILED. Input({}) != Output({})", check_output, output) << std::endl; \
			return false;                                                                                     \
		}                                                                                                     \
		else                                                                                                  \
			std::cout << std::format("\tPASSED. Input({}) == Output({})", check_output, output) << std::endl; \
	}
#else
#define CHECK_TEST(func, input, output)                                                                       \
	{                                                                                                         \
		auto check_output = func(input);                                                                      \
		if (check_output != output)                                                                           \
		{                                                                                                     \
			std::cout << std::format("\tFAILED. Input({}) != Output({})", check_output, output) << std::endl; \
			return false;                                                                                     \
		}                                                                                                     \
	}
#endif

struct file_contents
{
	char *mem;
	size_t sz;
};

inline file_contents read_entire_file(const char *filename)
{
	file_contents result = {0};
	std::ifstream file(filename, std::ios::in | std::ios::ate);
	if (file.is_open())
	{
		result.sz = file.tellg();
		// *output = (const char*)malloc(*length);
		file.seekg(0, std::ios::beg);
		result.mem = new char[result.sz + 1];
		file.read(result.mem, result.sz);
		result.mem[result.sz] = '\0';
	}
	file.close();
	return result;
}

inline bool is_hexadecimal(const char *in)
{
	return in[0] != '\0' && in[0] == '\\' && in[1] == 'x' && in[2] != '\0' &&
		   in[3] != '\0';
}

inline void save_bmp(const char *filename, int width, int height, u32 *buffer)
{
	int filesize = 54 + width * 4 * height;
	u8 bmpheader[14] = {'B',
						'M',
						(u8)filesize,
						(u8)(filesize >> 8),
						(u8)(filesize >> 16),
						(u8)(filesize >> 24),
						0,
						0,
						0,
						0,
						54,
						0,
						0,
						0};

	u8 bmpinfoheader[40] = {40,
							0,
							0,
							0,
							(u8)(width),
							(u8)(width >> 8),
							(u8)(width >> 16),
							(u8)(width >> 24),
							(u8)(height),
							(u8)(height >> 8),
							(u8)(height >> 16),
							(u8)(height >> 24),
							1,
							0,
							32,
							0};

	std::ofstream out(filename, std::ios::binary);
	out.write((char *)bmpheader, ARRAY_COUNT(bmpheader));
	out.write((char *)bmpinfoheader, ARRAY_COUNT(bmpinfoheader));

	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			u32 color = buffer[(y * width + x)];
			char A = /*color >> 24*/ 127, R = (color >> 16) & 255,
				 G = (color >> 8) & 255, B = (color) & 255;
			out.write(&B, 1);
			out.write(&G, 1);
			out.write(&R, 1);
			out.write(&A, 1);
		}
	}
}

inline bool is_whitespace(const char c) { return c == ' ' || c == '\n' || c == '\t'; }

inline bool is_numeric(const char c)
{
	int result = (c - '0');
	return result >= 0 && result <= 9;
}

inline int get_number(const char **c)
{
	int result = 0;
	while (!is_numeric(**c))
		(*c)++;

	while (**c >= '0' && **c <= '9')
	{
		result = result * 10 + (int)(**c - '0');
		++*c;
	}
	return result;
}

inline char get_symbol(const char **c)
{
	while (is_whitespace(**c) || is_numeric(**c))
		(*c)++;
	return **c;
}

inline char is_alpha(const char c)
{
	return (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'));
}

inline std::string get_variable(const char **c)
{
	std::string result;
	while (is_whitespace(**c) || is_numeric(**c) || !is_alpha((**c)))
		(*c)++;
	while (is_alpha(**c))
	{
		result += **c;
		(*c)++;
	}
	return result;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
	os << "[";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		os << vec[i];
		if (i != vec.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

#endif
